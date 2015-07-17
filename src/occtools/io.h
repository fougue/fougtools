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

#pragma once

#include "occtools.h"
#include <Handle_Message_ProgressIndicator.hxx>
#include <Handle_StlMesh_Mesh.hxx>
#include <TopoDS_Shape.hxx>

namespace occ {

class OCCTOOLS_EXPORT IO
{
public:
    typedef const char* FileNameLocal8Bit;

    enum Format
    {
        IgesFormat,
        StepFormat,
        OccBrepFormat,
        AsciiStlFormat,
        BinaryStlFormat,
        UnknownFormat
    };

    static Format partFormat(FileNameLocal8Bit fileName);
    static Format partFormatFromContents(
            const char* contentsBegin,
            std::size_t contentsBeginSize,
            std::size_t fullContentsSizeHint = 0);

    static TopoDS_Shape loadPartFile(
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);

    static Handle_StlMesh_Mesh loadStlFile(
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);

    static TopoDS_Shape loadBrepFile(
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);
    static TopoDS_Shape loadIgesFile(
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);
    static TopoDS_Shape loadStepFile(
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);

    static void writeBrepFile(
            const TopoDS_Shape& shape,
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);
    static void writeIgesFile(
            const TopoDS_Shape& shape,
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);
    static void writeStepFile(
            const TopoDS_Shape& shape,
            FileNameLocal8Bit fileName,
            Handle_Message_ProgressIndicator indicator = NULL);

    static void writeAsciiStlFile(
            const TopoDS_Shape& shape, FileNameLocal8Bit fileName);
    static void writeBinaryStlFile(
            const TopoDS_Shape& shape, FileNameLocal8Bit fileName);
};

} // namespace occ
