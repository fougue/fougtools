#include "test_occtools.h"

#include "../src/occtools/io.h"

#include <QtCore/QtDebug>

static const char igesData1[] =
        "                                                                        S0000001\n"
        ",,31HOpen CASCADE IGES processor 6.5,13HFilename.iges,                  G0000001\n"
        "16HOpen CASCADE 6.5,31HOpen CASCADE IGES processor 6.5,32,308,15,308,15,G0000002";

static const char stepData1[] =
        "ISO-10303-21; HEADER;\n"
        "FILE_DESCRIPTION (( 'STEP AP214' ),\n"
        "    '1' );\n"
        "FILE_NAME ('IRB6660_205_190__BASE_01.STEP',\n"
        "    '2007-11-29T13:04:51',\n"
        "    ( 'ABB' ),\n"
        "    ( 'ABB' ),\n"
        "    'SwSTEP 2.0',\n"
        "    'SolidWorks 2006233',\n"
        "    '' );\n"
        "FILE_SCHEMA (( 'AUTOMOTIVE_DESIGN' ));\n"
        "ENDSEC;";

static const char brepData1[] =
        "DBRep_DrawableShape\n"
        "\n"
        "CASCADE Topology V1, (c) Matra-Datavision\n"
        "Locations 11\n"
        "1\n"
        "      1               0               0 -446.500000000001 \n"
        "      0               0              -1 -2.87747256577653e-13 \n"
        "      0               1               0 208.999999999999 ";

static const char asciiStlData1[] =
        "solid \n"
        "facet normal  -2.770869E-01  9.510962E-01  -1.365244E-01\n"
        " outer loop\n"
        "  vertex  -1.260802E+00  9.186266E+00  -5.253864E-02\n"
        "  vertex  -1.394144E+00  9.159117E+00  2.895348E-02\n"
        "  vertex  -1.332380E+00  9.193080E+00  1.402038E-01\n"
        " endloop\n"
        "endfacet";

template <std::size_t N>
occ::IO::Format partFormatFromTestData(const char (&contents)[N])
{
    return occ::IO::partFormatFromContents(contents, N, N);
}


void TestOccTools::IO_test()
{
    QCOMPARE(partFormatFromTestData(igesData1), occ::IO::IgesFormat);
    QCOMPARE(partFormatFromTestData(stepData1), occ::IO::StepFormat);
    QCOMPARE(partFormatFromTestData(brepData1), occ::IO::OccBrepFormat);
    QCOMPARE(partFormatFromTestData(asciiStlData1), occ::IO::AsciiStlFormat);

    // Binary STL

}
