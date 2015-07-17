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

#include "ais_text.h"

#include <vector>

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

namespace occ {
IMPLEMENT_STANDARD_HANDLE(AIS_Text, AIS_InteractiveObject)

//IMPLEMENT_STANDARD_RTTI(AIS_Text)
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
} // namespace occ

#include <gp_Pnt.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <OSD_Environment.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_Text.hxx>
#include <SelectMgr_Selection.hxx>

namespace occ {

// --- Handle/Body Implementation

namespace internal {

    class TextProperties
    {
    public:
        TextProperties()
            : m_font(nullptr),
              m_aspect(new Prs3d_TextAspect)
        { }

        bool operator==(const TextProperties& other) const
        {
            return
                    m_font == other.m_font
                    && m_position.SquareDistance(other.m_position) < 1e-6
                    && m_text == other.m_text
                    && m_aspect == other.m_aspect;
        }

        const char* m_font;
        gp_Pnt m_position;
        TCollection_ExtendedString m_text;
        Handle_Prs3d_TextAspect m_aspect;
    };

} // namespace internal

class AIS_Text::Private
{
public:
    Private()
        : m_defaultFont("Courrier" /*Graphic3d_NOF_ASCII_MONO*/),
          m_defaultColor(Quantity_NOC_YELLOW),
          m_defaultTextBackgroundColor(Quantity_NOC_GREEN),
          m_defaultTextDisplayMode(Aspect_TODT_NORMAL),
          m_defaultTextStyle(Aspect_TOST_NORMAL)
    {
        //Graphic3d_AspectText3d::TexFontDisable();
    }

    const char* m_defaultFont;
    Quantity_Color m_defaultColor;
    Quantity_Color m_defaultTextBackgroundColor;
    Aspect_TypeOfDisplayText m_defaultTextDisplayMode;
    Aspect_TypeOfStyleText m_defaultTextStyle;
    std::vector<internal::TextProperties> m_textProps;
};

/*!
 * \class AIS_Text
 * \brief Interactive items specialized in text display
 *
 * \headerfile ais_text.h <occtools/ais_text.h>
 * \ingroup occtools
 */

//! Constructs a default AIS_Text
AIS_Text::AIS_Text()
    : d(new Private)
{
}

//! Constructs a fully initialized AIS_Text
AIS_Text::AIS_Text(
        const TCollection_ExtendedString &text, const gp_Pnt& pos)
    : d(new Private)
{
    internal::TextProperties defaultProps;
    d->m_textProps.push_back(defaultProps);
    this->setText(text);
    this->setPosition(pos);
}

//! Destructs the instance and free any allocated resources
AIS_Text::~AIS_Text()
{
    delete d;
}

Handle_Prs3d_TextAspect AIS_Text::presentationTextAspect(unsigned i) const
{
    if (this->isValidTextIndex(i))
        return d->m_textProps.at(i).m_aspect;
    return Handle_Prs3d_TextAspect();
}

Handle_Graphic3d_AspectText3d AIS_Text::graphicTextAspect(unsigned i) const
{
    if (this->isValidTextIndex(i))
        return d->m_textProps.at(i).m_aspect->Aspect();
    return Handle_Graphic3d_AspectText3d();
}

//! Returns the position of the \p i-th text displayed
gp_Pnt AIS_Text::position(unsigned i) const
{
    return this->isValidTextIndex(i) ?
                d->m_textProps.at(i).m_position : gp_Pnt();
}

//! Returns the \p i-th text displayed
TCollection_ExtendedString AIS_Text::text(unsigned i) const
{
    return this->isValidTextIndex(i) ?
                d->m_textProps.at(i).m_text : TCollection_ExtendedString();
}

//! Is \p i a valid index to query some text ?
bool AIS_Text::isValidTextIndex(unsigned i) const
{
    return i < this->textsCount();
}

//! Returns the count of texts displayed
unsigned AIS_Text::textsCount() const
{
    return static_cast<unsigned>(d->m_textProps.size());
}

/*! \brief Adds a new item text item to be displayed at position \p pos
 *
 *   Other text attributes are defaulted
 */
void AIS_Text::addText(
        const TCollection_ExtendedString &text, const gp_Pnt& pos)
{
    internal::TextProperties newProps;
    d->m_textProps.push_back(newProps);
    const unsigned i = this->textsCount() - 1; // Index of the last text item

    this->presentationTextAspect(i)->SetColor(d->m_defaultColor);
    this->presentationTextAspect(i)->SetFont(d->m_defaultFont);

    this->setPosition(pos, i);
    this->setText(text, i);
    this->setTextDisplayMode(d->m_defaultTextDisplayMode, i);
    this->setTextStyle(d->m_defaultTextStyle, i);
    this->setTextBackgroundColor(d->m_defaultTextBackgroundColor, i);
}

//! Sets the position of the \p i-th displayed text to \p pos
void AIS_Text::setPosition(const gp_Pnt& pos, unsigned i)
{
    if (this->isValidTextIndex(i))
        d->m_textProps[i].m_position = pos;
}

//! Sets the \p i-th displayed text to \p v
void AIS_Text::setText(const TCollection_ExtendedString &v, unsigned i)
{
    if (this->isValidTextIndex(i))
        d->m_textProps[i].m_text = v;
}

/*! \brief Sets the color of the \p i-th text background to \p color
 *
 *  Only works when the \p i-th text display mode is set to Aspect_TODT_SUBTITLE
 */
void AIS_Text::setTextBackgroundColor(const Quantity_Color& color, unsigned i)
{
    if (this->isValidTextIndex(i))
        this->graphicTextAspect(i)->SetColorSubTitle(color);
}

void AIS_Text::setTextDisplayMode(Aspect_TypeOfDisplayText mode, unsigned i)
{
    if (this->isValidTextIndex(i))
        this->graphicTextAspect(i)->SetDisplayType(mode);
}

void AIS_Text::setTextStyle(Aspect_TypeOfStyleText style, unsigned i)
{
    if (this->isValidTextIndex(i))
        this->graphicTextAspect(i)->SetStyle(style);
}

void AIS_Text::setDefaultColor(const Quantity_Color &c)
{
    d->m_defaultColor = c;
}

void AIS_Text::setDefaultFont(const char *fontName)
{
    d->m_defaultFont = fontName;
}

void AIS_Text::setDefaultTextBackgroundColor(const Quantity_Color& c)
{
    d->m_defaultTextBackgroundColor = c;
}

void AIS_Text::setDefaultTextDisplayMode(Aspect_TypeOfDisplayText mode)
{
    d->m_defaultTextDisplayMode = mode;
}

void AIS_Text::setDefaultTextStyle(Aspect_TypeOfStyleText style)
{
    d->m_defaultTextStyle = style;
}

// --- Implementation

//! -- from PrsMgr_PresentableObject
void AIS_Text::Compute(
        const Handle_PrsMgr_PresentationManager3d& /*pm*/,
        const Handle_Prs3d_Presentation& pres,
        const Standard_Integer /*mode*/)
{
    const auto txtCount = this->textsCount();
    for (unsigned i = 0; i < txtCount; ++i) {
        Prs3d_Text::Draw(
                    pres,
                    this->presentationTextAspect(i),
                    this->text(i),
                    this->position(i));
    }
}

//! -- from PrsMgr_PresentableObject
void AIS_Text::Compute(
        const Handle_Prs3d_Projector& /*proj*/,
        const Handle_Prs3d_Presentation& /*pres*/)
{
}

//! -- from SelectMgr_SelectableObject
void AIS_Text::ComputeSelection(
        const Handle_SelectMgr_Selection& /*sel*/,
        const Standard_Integer /*mode*/)
{
}

} // namespace occ
