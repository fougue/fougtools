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

#include "occtools/ais_text.h"

#include <Aspect_TypeOfText.hxx>
#include <cassert>
#include <Graphic3d_NameOfFont.hxx>
#include "occtools/utils.h"
#include <QtCore/QList>
#include <Quantity_Factor.hxx>
#include <Quantity_PlaneAngle.hxx>
#include <SelectMgr_SelectableObject.hxx>
#include <Standard_CString.hxx>
#include <Standard_Integer.hxx>
#include <Standard_IStream.hxx>
#include <Standard_OStream.hxx>
#include <Standard_Real.hxx>
#include <Standard_Transient.hxx>
#include <TCollection_AsciiString.hxx>

IMPLEMENT_STANDARD_HANDLE(AIS_Text, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTI(AIS_Text)
//
// Foreach ancestors, we add a IMPLEMENT_STANDARD_SUPERTYPE&&
// a IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY macro.
// We must respect the order: from the direct ancestor class
// to the base class.
//
IMPLEMENT_STANDARD_TYPE(AIS_Text);
IMPLEMENT_STANDARD_SUPERTYPE(AIS_InteractiveObject);
IMPLEMENT_STANDARD_SUPERTYPE(SelectMgr_SelectableObject);
IMPLEMENT_STANDARD_SUPERTYPE(PrsMgr_PresentableObject);
IMPLEMENT_STANDARD_SUPERTYPE(MMgt_TShared);
//IMPLEMENT_STANDARD_SUPERTYPE(Standard_Transient)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY()
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY(AIS_InteractiveObject)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY(SelectMgr_SelectableObject)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY(PrsMgr_PresentableObject)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY(MMgt_TShared)
//  IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_ENTRY(Standard_Transient)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_END()
IMPLEMENT_STANDARD_TYPE_END(AIS_Text)

#include <gp_Pnt.hxx>
#include <Graphic2d_Array1OfVertex.hxx>
#include <Graphic2d_DisplayList.hxx>
#include <Graphic2d_Drawer.hxx>
#include <Graphic2d_Polyline.hxx>
#include <Graphic2d_Segment.hxx>
#include <Graphic2d_Text.hxx>
#include <Graphic2d_Vertex.hxx>
#include <Graphic2d_View.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <OSD_Environment.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_Text.hxx>
#include <PrsMgr_PresentationManager2d.hxx>
#include <Select2D_SensitiveBox.hxx>
#include <SelectMgr_Selection.hxx>

// --- Handle/Body Implementation

class TextProperties
{
public:
  TextProperties()
  {
    this->aspect = new Prs3d_TextAspect;
  }

  bool operator==(const TextProperties& other) const
  {
    return
        this->font == other.font &&
        this->position.SquareDistance(other.position) < 1e-6 &&
        this->text == other.text &&
        this->aspect == other.aspect;
  }

  QFont font;
  gp_Pnt position;
  QString text;
  Handle_Prs3d_TextAspect aspect;
};

class AIS_TextPrivate
{
public:
  AIS_TextPrivate()
  {
    //Graphic3d_AspectText3d::TexFontDisable();
    this->defaultColor = QColor("yellow");
    this->defaultTextBackgroundColor = QColor("black");
    this->defaultTextDisplayMode = AIS_Text::TextOnlyDisplay;
    this->defaultTextStyle = AIS_Text::NormalStyle;
  }

  Handle_Graphic3d_AspectText3d graphicAspect(unsigned i) const
  {
    return this->textProps[i].aspect->Aspect();
  }

  QFont defaultFont;
  QColor defaultColor;
  QColor defaultTextBackgroundColor;
  AIS_Text::TextDisplayMode defaultTextDisplayMode;
  AIS_Text::TextStyle defaultTextStyle;
  QList<TextProperties> textProps;
};

/*!
 * \class AIS_Text
 * \brief Interactive items specialized in the displaying of texts.
 *
 *
 * \enum AIS_Text::TextDisplayMode
 *       Various types to distinguish the way texts are displayed.
 * \var AIS_Text::TextDisplayMode AIS_Text::TextOnlyDisplay
 *      Display only text(default mode).
 * \var AIS_Text::TextDisplayMode AIS_Text::BackgroundDisplay
 *      Window background under the text.
 * \var AIS_Text::TextDisplayMode AIS_Text::Style3dDisplay
 *      Text displayed with a 3D style.
 * \var AIS_Text::TextDisplayMode AIS_Text::Style3dDisplay
 *      Text is displayed in XOR mode.
 *
 * \enum AIS_Text::TextStyle
 *
 * \var AIS_Text::TextStyle AIS_Text::NormalStyle
 *
 * \var AIS_Text::TextStyle AIS_Text::AnnotationStyle
 *
 */

// --- Lifecycle

//! Construct a default AIS_Text
AIS_Text::AIS_Text() :
  _d(new AIS_TextPrivate)
{
}

//! Construct a fully initialized AIS_Text
AIS_Text::AIS_Text(const QString& text, const gp_Pnt& pos) :
  _d(new AIS_TextPrivate)
{
  TextProperties defaultProps;
  _d->textProps.append(defaultProps);
  this->setText(text);
  this->setPosition(pos);
}

//! Destruct the instance and free any allocated resources
AIS_Text::~AIS_Text()
{
  delete _d;
}

// --- Access

//! Color of the \p i -th text displayed
QColor AIS_Text::color(unsigned i) const
{
  assert(this->isValidTextIndex(i) && "valid_text_index");

  Handle_Graphic3d_AspectText3d aspect = _d->graphicAspect(i);
  Quantity_Color occColor;
  Standard_CString occFont;
  Standard_Real occExpFactor;
  Standard_Real occSpace;
  aspect->Values(occColor, occFont, occExpFactor, occSpace);
  return occ::toQtColor(occColor);
}

//! Font of the \p i-th text displayed
QFont AIS_Text::font(unsigned i) const
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  return _d->textProps[i].font;
}

//! Position of the \p i-th text displayed
const gp_Pnt& AIS_Text::position(unsigned i) const
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  return _d->textProps[i].position;
}

//! \p i-th text displayed
QString AIS_Text::text(unsigned i) const
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  return _d->textProps[i].text;
}

// --- Status report

//! Is \p i a valid index to query some text ?
bool AIS_Text::isValidTextIndex(unsigned i) const
{
  return i < this->textsCount();
}

// --- Measurement

//! Count of texts displayed
unsigned AIS_Text::textsCount() const
{
  return static_cast<unsigned>(_d->textProps.count());
}

// --- Element change

//! Add a new item text item to be displayed at position \p pos
//!   Other text attributes are defaulted
void AIS_Text::addText(const QString& text, const gp_Pnt& pos)
{
  TextProperties newProps;
  _d->textProps.append(newProps);
  const unsigned i = this->textsCount() - 1; // Index of the last text item.
  this->setColor(_d->defaultColor, i);
  this->setFont(_d->defaultFont, i);
  this->setPosition(pos, i);
  this->setText(text, i);
  this->setTextDisplayMode(_d->defaultTextDisplayMode, i);
  this->setTextStyle(_d->defaultTextStyle, i);
  this->setTextBackgroundColor(_d->defaultTextBackgroundColor, i);
}

//! Set the color of the \p i-th displayed text to \p c
void AIS_Text::setColor(const QColor& c, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  _d->textProps[i].aspect->SetColor(occ::toOccColor(c));
  assert(this->color(i) == c && "color_set");
}

//! Set the font of the \p i-th displayed text to \p f
void AIS_Text::setFont(const QFont& f, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  //! \bug Apparently there is no direct nor possible way to translate Qt
  //!      fonts to OpenCascade fonts. OpenCascade expects pre-defined
  //!      fonts listed in the enumerated type Graphic3d_NameOfFont. So
  //!      at the time being this routine as well as font() do not work
  _d->textProps[i].font = f;
  assert(this->font(i) == f && "font_set");
}

//! Set the 3d position of the \p i-th displayed text to \p pos
void AIS_Text::setPosition(const gp_Pnt& pos, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  _d->textProps[i].position = pos;
}

//! Set the \p i-th displayed text to \p v
void AIS_Text::setText(const QString& v, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  _d->textProps[i].text = v;
  assert(this->text(i) == v && "text_set");
}

//! Set the color of the \p i-th text background to \p color
//!   Only works when the \p i-th text display mode is set to
//!   BackgroundDisplay
void AIS_Text::setTextBackgroundColor(const QColor& color, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");
  Handle_Graphic3d_AspectText3d aspect = _d->graphicAspect(i);
  aspect->SetColorSubTitle(occ::toOccColor(color));
}

void AIS_Text::setTextDisplayMode(TextDisplayMode mode, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");

  Aspect_TypeOfDisplayText occMode;
  switch (mode) {
  case TextOnlyDisplay:
    occMode = Aspect_TODT_NORMAL;
    break;
  case BackgroundDisplay:
    occMode = Aspect_TODT_SUBTITLE;
    break;
  case Style3dDisplay:
    occMode = Aspect_TODT_DEKALE;
    break;
  case XorTextDisplay:
    occMode = Aspect_TODT_BLEND;
    break;
  default:
    occMode = Aspect_TODT_NORMAL;
    break;
  }
  _d->graphicAspect(i)->SetDisplayType(occMode);
}

void AIS_Text::setTextStyle(TextStyle style, unsigned i)
{
  assert(this->isValidTextIndex(i) && "valid_text_index");

  Aspect_TypeOfStyleText occStyle;
  switch (style) {
  case NormalStyle:
    occStyle = Aspect_TOST_NORMAL;
    break;
  case AnnotationStyle:
    occStyle = Aspect_TOST_ANNOTATION;
    break;
  default:
    occStyle = Aspect_TOST_NORMAL;
    break;
  }
  _d->graphicAspect(i)->SetStyle(occStyle);
}

void AIS_Text::setDefaultColor(const QColor& c)
{
  _d->defaultColor = c;
}

void AIS_Text::setDefaultFont(const QFont& f)
{
  _d->defaultFont = f;
}

void AIS_Text::setDefaultTextBackgroundColor(const QColor& c)
{
  _d->defaultTextBackgroundColor = c;
}

void AIS_Text::setDefaultTextDisplayMode(TextDisplayMode mode)
{
  _d->defaultTextDisplayMode = mode;
}

void AIS_Text::setDefaultTextStyle(TextStyle style)
{
  _d->defaultTextStyle = style;
}

// --- Implementation

//! -- from PrsMgr_PresentableObject
void AIS_Text::Compute(const Handle_PrsMgr_PresentationManager3d& /*pm*/,
                       const Handle_Prs3d_Presentation& pres,
                       const Standard_Integer /*mode*/)
{
  for (unsigned i = 0; i < this->textsCount(); i++)
    Prs3d_Text::Draw(pres, _d->textProps[i].aspect,
                     //occ::toOccCstring(this->text(i)),
                     const_cast<char*>(qPrintable(this->text(i))),
                     this->position(i));
}

//! -- from PrsMgr_PresentableObject
void AIS_Text::Compute(const Handle_Prs3d_Projector& /*proj*/,
                       const Handle_Prs3d_Presentation& /*pres*/)
{
}

//! -- from PrsMgr_PresentableObject
void AIS_Text::Compute(const Handle_PrsMgr_PresentationManager2d& /*pres*/,
                       const Handle_Graphic2d_GraphicObject& /*grObj*/,
                       const Standard_Integer /*mode*/)
{
  //   Handle_Graphic2d_Text text =
  //     new Graphic2d_Text(grObj,(Standard_CString) m_text.ascii(),
  //    m_position.x(), m_position.y(),
  //    m_angle, Aspect_TOT_SOLID, m_scale);
  //   text->SetFontIndex(m_fontId);

  //   text->SetColorIndex(m_colorId);

  //   text->SetSlant(m_slant);
  //   text->SetUnderline(false);
  //   text->SetZoomable(true);
  //   grObj->Display();
  //   Real xOffset;
  //   Real yOffset;
  //   text->TextSize(m_width, m_height, xOffset, yOffset);
}

//! -- from SelectMgr_SelectableObject
void AIS_Text::ComputeSelection(const Handle_SelectMgr_Selection& /*sel*/,
                                const Standard_Integer /*mode*/)
{
}
