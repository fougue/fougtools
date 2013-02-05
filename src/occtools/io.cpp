/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "io.h"

#include <QtCore/QBuffer>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QObject>
#include <QtCore/QRegExp>

#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <OSD_Path.hxx>
#include <RWStl.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx> // For IGES files reading
#include <IGESControl_Writer.hxx>
#include <STEPControl_Reader.hxx> // For STEP files reading
#include <STEPControl_Writer.hxx>
#include <StlMesh_Mesh.hxx>
#include <StlAPI_Writer.hxx>
#include <IFSelect_ReturnStatus.hxx> // For status reading
#include <Interface_Static.hxx>
#include <Message_ProgressIndicator.hxx>
#include <Transfer_FinderProcess.hxx>
#include <Transfer_TransientProcess.hxx>
#include <XSControl_WorkSession.hxx>

#include "../cpptools/memory_utils.h"

namespace {

float readLittleEndianReal32b(QFile* file)
{
  union Real32
  {
    qint32 asInteger;
    float asFloat;
  };

  char floatBytes[4];
  file->read(&floatBytes[0], 4);

  Real32 result;
  result.asInteger = floatBytes[0] & 0xff;
  result.asInteger |= (floatBytes[1] & 0xff) << 0x08;
  result.asInteger |= (floatBytes[2] & 0xff) << 0x10;
  result.asInteger |= (floatBytes[3] & 0xff) << 0x18;

  return result.asFloat;
}

template<typename _READER_>
TopoDS_Shape loadFile(const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  TopoDS_Shape result;

  if (!indicator.IsNull())
    indicator->NewScope(30, "Loading file");
  _READER_ reader;
  const int status = reader.ReadFile(const_cast<Standard_CString>(qPrintable(fileName)));
  if (!indicator.IsNull())
    indicator->EndScope();
  if (status == IFSelect_RetDone) {
    if (!indicator.IsNull()) {
      reader.WS()->MapReader()->SetProgress(indicator);
      indicator->NewScope(70, "Translating file");
    }
    reader.NbRootsForTransfer();
    reader.TransferRoots();
    result = reader.OneShape();
    if (!indicator.IsNull()) {
      indicator->EndScope();
      reader.WS()->MapReader()->SetProgress(0);
    }
  }
  return result;
}

} // Anonymous namespace

namespace occ {

IO::Format IO::partFormat(const QString& filename)
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly))
    return UnknownFormat;
  const QByteArray contentsBegin = file.read(2048);

  // Assume a binary-based format
  // -- Binary STL ?
  const int binaryStlHeaderSize = 80 + sizeof(quint32);
  if (contentsBegin.size() >= binaryStlHeaderSize) {
    QBuffer buffer;
    buffer.setData(contentsBegin);
    buffer.open(QIODevice::ReadOnly);
    buffer.seek(80); // Skip header
    quint32 facetsCount = 0;
    buffer.read(reinterpret_cast<char*>(&facetsCount), sizeof(quint32));
    const unsigned facetSize = (sizeof(float) * 12) + sizeof(quint16);
    if ((facetSize * facetsCount + binaryStlHeaderSize) == file.size())
      return BinaryStlFormat;
  }

  // Assume a text-based format
  const QString contentsBeginText(contentsBegin);
  if (contentsBeginText.contains(QRegExp("^.{72}S\\s*[0-9]+\\s*[\\n\\r\\f]")))
    return IgesFormat;
  if (contentsBeginText.contains(QRegExp("^\\s*ISO-10303-21\\s*;\\s*HEADER")))
    return StepFormat;
  if (contentsBeginText.contains(QRegExp("^\\s*DBRep_DrawableShape")))
    return OccBrepFormat;
  if (contentsBeginText.contains(QRegExp("^\\s*solid")))
    return AsciiStlFormat;

  // Fallback case
  return UnknownFormat;
}

TopoDS_Shape IO::loadPartFile(const QString& filename, Handle_Message_ProgressIndicator indicator)
{
  switch (partFormat(filename)) {
  case StepFormat:
    return IO::loadStepFile(filename, indicator);
  case IgesFormat:
    return IO::loadIgesFile(filename, indicator);
  case OccBrepFormat:
    return IO::loadBrepFile(filename, indicator);
  default:
    return TopoDS_Shape();
  }
  return TopoDS_Shape();
}

Handle_StlMesh_Mesh IO::loadStlFile(const QString& filename, Handle_Message_ProgressIndicator indicator)
{
  return RWStl::ReadFile(OSD_Path(filename.toAscii().constData()), indicator);
}

/*! \brief Topologic shape read from a file (OCC's internal BREP format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadBrepFile(const QString& fileName,
                              Handle_Message_ProgressIndicator indicator)
{
  TopoDS_Shape result;
  BRep_Builder brepBuilder;
  BRepTools::Read(result, fileName.toAscii().constData(), brepBuilder, indicator);
  return result;
}

/*! \brief Topologic shape read from a file (IGES format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadIgesFile(const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  return ::loadFile<IGESControl_Reader>(fileName, indicator);
}

/*! \brief Topologic shape read from a file (STEP format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadStepFile(const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  return ::loadFile<STEPControl_Reader>(fileName, indicator);
}

/*! \brief Write a topologic shape to a file (OCC's internal BREP format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeBrepFile(const TopoDS_Shape& shape,
                       const QString& fileName,
                       Handle_Message_ProgressIndicator indicator)
{
  BRepTools::Write(shape, fileName.toAscii().data(), indicator);
}

/*! \brief Write a topologic shape to a file (IGES format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeIgesFile(const TopoDS_Shape& shape,
                       const QString& fileName,
                       Handle_Message_ProgressIndicator indicator)
{
  IGESControl_Controller::Init();
  IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"),
                            Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
  if (!indicator.IsNull())
    writer.TransferProcess()->SetProgress(indicator);
  writer.AddShape(shape);
  writer.ComputeModel();
  writer.Write(fileName.toAscii().data());
  writer.TransferProcess()->SetProgress(0);
}

/*! \brief Write a topologic shape to a file (STEP format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeStepFile(const TopoDS_Shape& shape,
                       const QString& fileName,
                       Handle_Message_ProgressIndicator indicator)
{
  IFSelect_ReturnStatus status;
  STEPControl_Writer writer;
  if (!indicator.IsNull())
    writer.WS()->MapReader()->SetProgress(indicator);
  status = writer.Transfer(shape, STEPControl_AsIs);
  status = writer.Write(fileName.toAscii().data());
  writer.WS()->MapReader()->SetProgress(0);
}

/*! \brief Write a topologic shape to a file (ASCII STL format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 */
void IO::writeAsciiStlFile(const TopoDS_Shape& shape, const QString& fileName)
{
  StlAPI_Writer writer;
  writer.ASCIIMode() = Standard_True;
  writer.Write(shape, fileName.toAscii().data());
}

/*! \brief Write a topologic shape to a file (binary STL format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 */
void IO::writeBinaryStlFile(const TopoDS_Shape& shape, const QString& fileName)
{
  StlAPI_Writer writer;
  writer.ASCIIMode() = Standard_False;
  writer.Write(shape, fileName.toAscii().data());
}

} // namespace occ
