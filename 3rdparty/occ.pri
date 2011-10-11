INCLUDEPATH *= $$(CASROOT)/inc
win32-*:INCLUDEPATH *= $$(CASROOT)/include/oce
linux-*:DEFINES *= HAVE_CONFIG_H \
                   HAVE_FSTREAM \
                   HAVE_IOSTREAM \
                   HAVE_LIMITS_H
#                  HAVE_LIMITS
win32-*:DEFINES *= WNT
linux-*:DEFINES *= LIN LININTEL OCC_CONVERT_SIGNALS
*-64:DEFINES *= _OCC64

linux-*:LIBS *= -L$$(CASROOT)/lib -L$$(CASROOT)/lib/OCE
win32-*:LIBS *= -L$$(CASROOT)/win32/lib
LIBS *= \
#                 -lBinLPlugin \
#                 -lBinPlugin \
#                 -lBinXCAFPlugin \
#                 -lFWOSPlugin \
#                 -lmscmd \
#                 -lPTKernel \
#                 -lStdLPlugin \
#                 -lStdPlugin \
#                 -lTKAdvTools \
#                 -lTKBin \
#                 -lTKBinL \
#                 -lTKBinXCAF \
#                 -lTKBO \
#                 -lTKBool \
                 -lTKBRep \
#                 -lTKCAF \
#                 -lTKCDF \
#                 -lTKCDLFront \
#                 -lTKCPPClient \
#                 -lTKCPPExt \
#                 -lTKCPPIntExt \
#                 -lTKCPPJini \
#                 -lTKCSFDBSchema \
#                 -lTKDCAF \
#                 -lTKDraw \
                 -lTKernel \
#                 -lTKFeat \
#                 -lTKFillet \
                 -lTKG2d \
                 -lTKG3d \
                 -lTKGeomAlgo \
                 -lTKGeomBase \
#                 -lTKHLR \
#                 -lTKIDLFront \
                 -lTKIGES \
#                 -lTKjcas \
#                 -lTKLCAF \
                 -lTKMath \
                 -lTKMesh \
#                 -lTKMeshVS \
#                 -lTKOffset \
                 -lTKOpenGl \
#                 -lTKPCAF \
#                 -lTKPLCAF \
                 -lTKPrim \
#                 -lTKPShape \
                 -lTKService \
#                 -lTKShapeSchema \
                 -lTKShHealing \
#                 -lTKStdLSchema \
#                 -lTKStdSchema \
                 -lTKSTEP \
                 -lTKSTEPAttr \
                 -lTKSTEPBase \
                 -lTKSTL \
#                 -lTKTCPPExt \
                 -lTKTopAlgo \
#                 -lTKTopTest \
                 -lTKV2d \
                 -lTKV3d \
#                 -lTKViewerTest \
#                 -lTKVRML \
#                 -lTKWOK \
#                 -lTKWOKTcl \
#                 -lTKXCAF \
#                 -lTKXCAFSchema \
#                 -lTKXDEDRAW \
#                 -lTKXDEIGES \
#                 -lTKXDESTEP \
#                 -lTKXml \
#                 -lTKXmlL \
#                 -lTKXmlXCAF \
                 -lTKXSBase \
#                 -lTKXSDRAW \
#                 -lwokcmd \
#                 -lwokdeliverysteps \
#                 -lwokdfltsteps \
#                 -lwokobjssteps \
#                 -lwokorbixsteps \
#                 -lwoksteps \
#                 -lwoktoolscmd \
#                 -lwokutilscmd \
#                 -lXCAFPlugin \
#                 -lXmlLPlugin \
#                 -lXmlPlugin \
#                 -lXmlXCAFPlugin

# There is a weird bug with qmake on windows : it fails to correctly link with
# TKSTEP209 due to the name of library mixing characters and digits.
# Or maybe nmake is the problem ?
# Note : you have to rename TKSTEP209 to TKSTEP_tzn in $CASROOT/win32/lib
win32-msvc* {
  LIBS *= -lTKSTEP_tzn
}
else {
 LIBS *= -lTKSTEP209
}
