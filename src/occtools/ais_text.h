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
#include "handle_ais_text.h"

#include <AIS_InteractiveObject.hxx>
#include <Aspect_TypeOfDisplayText.hxx>
#include <Aspect_TypeOfStyleText.hxx>
#include <gp_Pnt.hxx>
#include <Handle_Graphic3d_AspectText3d.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Handle_Prs3d_Projector.hxx>
#include <Handle_Prs3d_TextAspect.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <SelectMgr_Selection.hxx>
#include <Quantity_Color.hxx>
#include <TCollection_ExtendedString.hxx>

namespace occ {

class OCCTOOLS_EXPORT AIS_Text : public AIS_InteractiveObject
{
public:
    AIS_Text();
    AIS_Text(const TCollection_ExtendedString& text, const gp_Pnt& pos);
    virtual ~AIS_Text();

    //  DEFINE_STANDARD_RTTI(AIS_Text)

    Handle_Prs3d_TextAspect presentationTextAspect(unsigned i = 0) const;
    Handle_Graphic3d_AspectText3d graphicTextAspect(unsigned i = 0) const;

    void setDefaultColor(const Quantity_Color& c);
    void setDefaultFont(const char* fontName);
    void setDefaultTextBackgroundColor(const Quantity_Color& c);
    void setDefaultTextDisplayMode(Aspect_TypeOfDisplayText mode);
    void setDefaultTextStyle(Aspect_TypeOfStyleText style);

    gp_Pnt position(unsigned i = 0) const;
    void setPosition(const gp_Pnt& pos, unsigned i = 0);

    TCollection_ExtendedString text(unsigned i = 0) const;
    void setText(const TCollection_ExtendedString& v, unsigned i = 0);
    bool isValidTextIndex(unsigned i) const;

    void setTextBackgroundColor(const Quantity_Color& color, unsigned i = 0);
    void setTextDisplayMode(Aspect_TypeOfDisplayText mode, unsigned i = 0);
    void setTextStyle(Aspect_TypeOfStyleText style, unsigned i = 0);

    unsigned textsCount() const;
    void addText(const TCollection_ExtendedString& text, const gp_Pnt& pos);

    // --- Implementation
protected:
    void Compute(
            const Handle_PrsMgr_PresentationManager3d& pm,
            const Handle_Prs3d_Presentation& pres,
            const Standard_Integer mode) override;
    void Compute(
            const Handle_Prs3d_Projector& proj,
            const Handle_Prs3d_Presentation& pres) override;
    void ComputeSelection(
            const Handle_SelectMgr_Selection& sel,
            const Standard_Integer mode) override;

private:
    class Private;
    Private* const d;
};

} // namespace occ
