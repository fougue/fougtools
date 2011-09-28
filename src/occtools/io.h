#ifndef OCC_IO_H
#define OCC_IO_H

#include "occtools/occtools.h"
#include <Handle_Message_ProgressIndicator.hxx>
#include <Handle_StlMesh_Mesh.hxx>
#include <TopoDS_Shape.hxx>
class QString;

namespace occ {

class OCCTOOLS_EXPORT IO
{
public:
  enum Format
  {
    IgesFormat,
    StepFormat,
    OccBRepFormat,
    AsciiStlFormat,
    BinaryStlFormat,
    UnknownFormat
  };

  static Format partFormat(const QString& fileName);

  static const TopoDS_Shape loadPartFile(const QString& fileName);
  static const Handle_StlMesh_Mesh loadStlFile(const QString& fileName);

  static TopoDS_Shape loadBrepFile(const QString& fileName,
                                   Handle_Message_ProgressIndicator indicator = 0);
  static TopoDS_Shape loadIgesFile(const QString& fileName,
                                   Handle_Message_ProgressIndicator indicator = 0);
  static TopoDS_Shape loadStepFile(const QString& fileName,
                                   Handle_Message_ProgressIndicator indicator = 0);

  void writeBrepFile(const TopoDS_Shape& shape, const QString& fileName,
                     Handle_Message_ProgressIndicator indicator = 0);
  void writeIgesFile(const TopoDS_Shape& shape, const QString& fileName,
                     Handle_Message_ProgressIndicator indicator = 0);
  void writeStepFile(const TopoDS_Shape& shape, const QString& fileName,
                     Handle_Message_ProgressIndicator indicator = 0);
  void writeAsciiStlFile(const TopoDS_Shape& shape, const QString& fileName);
  void writeBinaryStlFile(const TopoDS_Shape& shape, const QString& fileName);
};

} // namespace occ

#endif // OCC_IO_H
