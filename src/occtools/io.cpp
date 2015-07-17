/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#include "io.h"

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
#include <XSControl_TransferWriter.hxx>
#include <XSControl_WorkSession.hxx>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>

#include "../cpptools/c_array_utils.h"
#include "../cpptools/memory_utils.h"

namespace {

template<typename _READER_>
TopoDS_Shape loadFile(
        occ::IO::FileNameLocal8Bit fileName,
        Handle_Message_ProgressIndicator indicator)
{
    TopoDS_Shape result;

    if (!indicator.IsNull())
        indicator->NewScope(30, "Loading file");
    _READER_ reader;
    const int status = reader.ReadFile(const_cast<Standard_CString>(fileName));
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
            reader.WS()->MapReader()->SetProgress(NULL);
        }
    }
    return result;
}

const char* skipWhiteSpaces(const char* str, std::size_t len)
{
    std::size_t pos = 0;
    while (std::isspace(str[pos]) && pos < len)
        ++pos;
    return str + pos;
}

//bool matchToken(const char* buffer, const char* token)
//{
//    const auto tokenLen = std::strlen(token);
//    return std::strncmp(buffer, token, tokenLen) == 0;
//}

template <std::size_t N>
bool matchToken(const char* buffer, const char (&token)[N])
{
    return std::strncmp(buffer, token, N - 1) == 0;
}

} // Anonymous namespace

namespace occ {

/*! \class IO
 *
 *  \headerfile io.h <occtools/io.h>
 *  \ingroup occtools
 */

IO::Format IO::partFormat(FileNameLocal8Bit fileName)
{
    std::ifstream ifs(fileName, std::ios_base::in);
    if (ifs) {
        std::array<char, 2048> contentsBegin;
        contentsBegin.fill(0);
        ifs.read(contentsBegin.data(), contentsBegin.size());

        // Compute input file size
        ifs.seekg(0);
        const auto pos = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        const auto fileSize = ifs.tellg() - pos;

        return IO::partFormatFromContents(
                    contentsBegin.data(), contentsBegin.size(), fileSize);
    }
    return UnknownFormat;
}

IO::Format IO::partFormatFromContents(
        const char* contentsBegin,
        std::size_t contentsBeginSize,
        std::size_t fullContentsSizeHint)
{
    // Assume a binary-based format (little-endian format)
    // -- Binary STL ?
    const std::size_t binaryStlHeaderSize = 80 + sizeof(std::uint32_t);
    if (contentsBeginSize >= binaryStlHeaderSize) {
        const std::uint32_t offset = 80; // Skip header
        const std::uint32_t facetsCount =
                (static_cast<std::uint32_t>(contentsBegin[offset + 0]) << 24)
                | (static_cast<std::uint32_t>(contentsBegin[offset + 1]) << 16)
                | (static_cast<std::uint32_t>(contentsBegin[offset + 2]) << 8)
                | (static_cast<std::uint32_t>(contentsBegin[offset + 3]));
        const unsigned facetSize = (sizeof(float) * 12) + sizeof(std::uint16_t);

        if ((facetSize * facetsCount + binaryStlHeaderSize)
                == fullContentsSizeHint)
        {
            return BinaryStlFormat;
        }
    }

    // Assume a text-based format

    // -- IGES ?
    {
        // regex : ^.{72}S\s*[0-9]+\s*[\n\r\f]
        bool isIges = true;
        if (contentsBeginSize >= 80 && contentsBegin[72] == 'S') {
            for (int i = 73; i < 80 && isIges; ++i) {
                if (contentsBegin[i] != ' ' && !std::isdigit(contentsBegin[i]))
                    isIges = false;
            }
            if (isIges && (contentsBegin[80] == '\n'
                           || contentsBegin[80] == '\r'
                           || contentsBegin[80] == '\f'))
            {
                const int sVal = std::atoi(contentsBegin + 73);
                if (sVal == 1)
                    return IO::IgesFormat;
            }
        }
    } // IGES

    contentsBegin = skipWhiteSpaces(contentsBegin, contentsBeginSize);

    // -- STEP ?
    {
        // regex : ^\s*ISO-10303-21\s*;\s*HEADER
        const char stepIsoId[] = "ISO-10303-21";
        const auto stepIsoIdLen = cpp::cArraySize(stepIsoId) - 1;
        const char stepHeaderToken[] = "HEADER";
        const auto stepHeaderTokenLen = cpp::cArraySize(stepHeaderToken) - 1;
        if (std::strncmp(contentsBegin, stepIsoId, stepIsoIdLen) == 0) {
            auto charIt = skipWhiteSpaces(contentsBegin + stepIsoIdLen,
                                          contentsBeginSize - stepIsoIdLen);
            if (*charIt == ';'
                    && (charIt - contentsBegin) < contentsBeginSize)
            {
                charIt = skipWhiteSpaces(
                            charIt + 1,
                            contentsBeginSize - (charIt - contentsBegin));
                if (std::strncmp(charIt, stepHeaderToken, stepHeaderTokenLen)
                        == 0)
                {
                    return IO::StepFormat;
                }
            }
        }
    } // STEP

    // -- OpenCascade BREP ?
    {
        // regex : ^\s*DBRep_DrawableShape
        const char occBRepToken[] = "DBRep_DrawableShape";
        if (matchToken(contentsBegin, occBRepToken))
            return IO::OccBrepFormat;
    }

    // -- ASCII STL ?
    {
        // regex : ^\s*solid
        const char asciiStlToken[] = "solid";
        if (matchToken(contentsBegin, asciiStlToken))
            return IO::AsciiStlFormat;
    }

    // Fallback case
    return UnknownFormat;
}

TopoDS_Shape IO::loadPartFile(
        FileNameLocal8Bit fileName, Handle_Message_ProgressIndicator indicator)
{
    switch (partFormat(fileName)) {
    case StepFormat:
        return IO::loadStepFile(fileName, indicator);
    case IgesFormat:
        return IO::loadIgesFile(fileName, indicator);
    case OccBrepFormat:
        return IO::loadBrepFile(fileName, indicator);
    default:
        return TopoDS_Shape();
    }
}

Handle_StlMesh_Mesh IO::loadStlFile(
        FileNameLocal8Bit fileName, Handle_Message_ProgressIndicator indicator)
{
    return RWStl::ReadFile(OSD_Path(fileName), indicator);
}

/*! \brief Topologic shape read from a file (OCC's internal BREP format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadBrepFile(
        FileNameLocal8Bit fileName, Handle_Message_ProgressIndicator indicator)
{
    TopoDS_Shape result;
    BRep_Builder brepBuilder;
    BRepTools::Read(result, fileName, brepBuilder, indicator);
    return result;
}

/*! \brief Topologic shape read from a file (IGES format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadIgesFile(
        FileNameLocal8Bit fileName, Handle_Message_ProgressIndicator indicator)
{
    return ::loadFile<IGESControl_Reader>(fileName, indicator);
}

/*! \brief Topologic shape read from a file (STEP format)
 *  \param fileName Path to the file to read
 *  \param indicator Indicator to notify the loading progress
 *  \return The part as a whole topologic shape
 */
TopoDS_Shape IO::loadStepFile(
        FileNameLocal8Bit fileName, Handle_Message_ProgressIndicator indicator)
{
    return ::loadFile<STEPControl_Reader>(fileName, indicator);
}

/*! \brief Write a topologic shape to a file (OCC's internal BREP format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeBrepFile(
        const TopoDS_Shape& shape,
        FileNameLocal8Bit fileName,
        Handle_Message_ProgressIndicator indicator)
{
    BRepTools::Write(shape, fileName, indicator);
}

/*! \brief Write a topologic shape to a file (IGES format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeIgesFile(
        const TopoDS_Shape& shape,
        FileNameLocal8Bit fileName,
        Handle_Message_ProgressIndicator indicator)
{
    IGESControl_Controller::Init();
    IGESControl_Writer writer(
                Interface_Static::CVal("XSTEP.iges.unit"),
                Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
    if (!indicator.IsNull())
        writer.TransferProcess()->SetProgress(indicator);
    writer.AddShape(shape);
    writer.ComputeModel();
    writer.Write(fileName);
    writer.TransferProcess()->SetProgress(NULL);
}

/*! \brief Write a topologic shape to a file (STEP format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 *  \param indicator Indicator to notify the writing progress
 */
void IO::writeStepFile(
        const TopoDS_Shape& shape,
        FileNameLocal8Bit fileName,
        Handle_Message_ProgressIndicator indicator)
{
    IFSelect_ReturnStatus status;
    STEPControl_Writer writer;
    if (!indicator.IsNull())
        writer.WS()->TransferWriter()->FinderProcess()->SetProgress(indicator);
    status = writer.Transfer(shape, STEPControl_AsIs);
    status = writer.Write(fileName);
    writer.WS()->TransferWriter()->FinderProcess()->SetProgress(NULL);
}

/*! \brief Write a topologic shape to a file (ASCII STL format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 */
void IO::writeAsciiStlFile(
        const TopoDS_Shape& shape, FileNameLocal8Bit fileName)
{
    StlAPI_Writer writer;
    writer.ASCIIMode() = Standard_True;
    writer.Write(shape, fileName);
}

/*! \brief Write a topologic shape to a file (binary STL format)
 *  \param shape Topologic shape to write
 *  \param fileName Path to the file to write
 */
void IO::writeBinaryStlFile(
        const TopoDS_Shape& shape, FileNameLocal8Bit fileName)
{
    StlAPI_Writer writer;
    writer.ASCIIMode() = Standard_False;
    writer.Write(shape, fileName);
}

} // namespace occ
