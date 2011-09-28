#ifndef OCC_AIS_TEXT_H
#define OCC_AIS_TEXT_H

#include "occtools/occtools.h"
#include <AIS_InteractiveObject.hxx>
#include <gp_Pnt.hxx>
#include <Handle_Graphic2d_GraphicObject.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Handle_Prs3d_Projector.hxx>
#include <Handle_PrsMgr_PresentationManager2d.hxx>
#include <Handle_PrsMgr_PresentationManager3d.hxx>
#include <Handle_SelectMgr_Selection.hxx>
#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <Standard_DefineHandle.hxx>
#include <Standard_Macro.hxx>

DEFINE_STANDARD_HANDLE(AIS_Text, AIS_InteractiveObject)

class OCCTOOLS_EXPORT AIS_Text : public AIS_InteractiveObject
{
public:
  enum TextDisplayMode
  {
    TextOnlyDisplay,
    BackgroundDisplay,
    Style3dDisplay,
    XorTextDisplay
  };

  enum TextStyle
  {
    NormalStyle,
    AnnotationStyle
  };

  AIS_Text();
  AIS_Text(const QString& text, const gp_Pnt& pos);
  virtual ~AIS_Text();

  DEFINE_STANDARD_RTTI(AIS_Text)

  QColor color(unsigned i = 0) const;
  void setColor(const QColor& c, unsigned i = 0);
  void setDefaultColor(const QColor& c);

  QFont font(unsigned i = 0) const;
  void setFont(const QFont& f, unsigned i = 0);
  void setDefaultFont(const QFont& f);

  const gp_Pnt& position(unsigned i = 0) const;
  void setPosition(const gp_Pnt& pos, unsigned i = 0);

  QString text(unsigned i = 0) const;
  void setText(const QString& v, unsigned i = 0);
  bool isValidTextIndex(unsigned i) const;

  void setTextBackgroundColor(const QColor& color, unsigned i = 0);
  void setDefaultTextBackgroundColor(const QColor& c);

  void setTextDisplayMode(TextDisplayMode mode, unsigned i = 0);
  void setDefaultTextDisplayMode(TextDisplayMode mode);

  void setTextStyle(TextStyle style, unsigned i = 0);
  void setDefaultTextStyle(TextStyle style);

  unsigned textsCount() const;
  void addText(const QString& text, const gp_Pnt& pos);

  // --- Implementation
protected:
  void Compute(const Handle_PrsMgr_PresentationManager3d& pm,
               const Handle_Prs3d_Presentation& pres,
               const Standard_Integer mode);
  void Compute(const Handle_Prs3d_Projector& proj,
               const Handle_Prs3d_Presentation& pres);
  void Compute(const Handle_PrsMgr_PresentationManager2d& pres,
               const Handle_Graphic2d_GraphicObject& grObj,
               const Standard_Integer mode);
  void ComputeSelection(const Handle_SelectMgr_Selection& sel,
                        const Standard_Integer mode);

private:
  class AIS_TextPrivate* _d;
};

#endif // AIS_TEXT_H
