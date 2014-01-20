#include <QApplication>
#include <QtCore/QtDebug>
#include <QtCore/QObject>
#include <QtGui/QMouseEvent>

#include <Standard_Version.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TopoDS_Shape.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>

#include <occtools/qt_view.h>

#include "qt_view_controller.h"

namespace internal {

static Handle_V3d_Viewer createOccViewer()
{
  // Create the graphic driver
  Handle_Graphic3d_GraphicDriver gpxDriver;

  Handle_Aspect_DisplayConnection dispConnection;
#if !defined(Q_OS_WIN32) && (!defined(Q_OS_MAC) || defined(MACOSX_USE_GLX))
  dispConnection  = new Aspect_DisplayConnection(std::getenv("DISPLAY"));
#endif
  gpxDriver = Graphic3d::InitGraphicDriver(dispConnection);

  // Create the named OCC 3d viewer
  Handle_V3d_Viewer occViewer = new V3d_Viewer(gpxDriver, (short*)("Viewer3d"));

  // Configure the OCC 3d viewer
  occViewer->SetDefaultViewSize(1000.);
  occViewer->SetDefaultViewProj(V3d_XposYnegZpos);
  occViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);
  occViewer->SetDefaultVisualization(V3d_ZBUFFER);
  occViewer->SetDefaultShadingModel(V3d_GOURAUD);
  occViewer->SetUpdateMode(V3d_WAIT);
  occViewer->SetDefaultSurfaceDetail(V3d_TEX_NONE);

  // Initialize the OCC 3d viewer
#if OCC_VERSION_HEX < 0x60700
  occViewer->Init();
#endif
  occViewer->SetDefaultLights();
  occViewer->SetLightOn();

  return occViewer;
}

} // namespace internal

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Handle_V3d_Viewer occViewer = internal::createOccViewer();
  Handle_AIS_InteractiveContext occContext = new AIS_InteractiveContext(occViewer);

  // Load BRep files specified at command line
  for (int i = 1; i < argc; ++i) {
    TopoDS_Shape shape;
    BRep_Builder brepBuilder;
    BRepTools::Read(shape, argv[i], brepBuilder);

    Handle_AIS_Shape aisShape = new AIS_Shape(shape);
    aisShape->SetMaterial(Graphic3d_NOM_PLASTIC);
    aisShape->SetDisplayMode(AIS_Shaded);
    aisShape->SetColor(Quantity_NOC_GRAY50);
    aisShape->Attributes()->SetFaceBoundaryDraw(Standard_True);

    occContext->Display(aisShape, i == (argc - 1));
  }

  occ::QtView qtView(occContext);
  new QtViewController(&qtView);
  qtView.show();
  return app.exec();
}
