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

#include "abstract_quantity_editor.h"

#include "quantity_editor_manager.h"

namespace qtgui {

/*! \class AbstractQuantityEditor
 *  \brief Base abstract class for editor of quantities, works in coordination
 *         with QuantityEditorManager
 *
 *  \headerfile abstract_quantity_editor.h <qttools/gui/abstract_qantity_editor.h>
 *  \ingroup qttools_gui
 */

/*! Construct and auto-attach this editor with QuantityEditorManager::attach()
 */
AbstractQuantityEditor::AbstractQuantityEditor()
{
    QuantityEditorManager::globalInstance()->attach(this);
}

/*! Destroy and auto-detach this editor with QuantityEditorManager::detach()
 */
AbstractQuantityEditor::~AbstractQuantityEditor()
{
    QuantityEditorManager::globalInstance()->detach(this);
}

/*! Called by QuantityEditorManager when the current measurement system was
 *  switched to another one
 *
 *  Does nothing by default
 */
void AbstractQuantityEditor::updateEditor(QLocale::MeasurementSystem /*newSys*/)
{
}

QLocale::MeasurementSystem AbstractQuantityEditor::measurementSystem() const
{
    return QuantityEditorManager::globalInstance()->measurementSytem();
}

} // namespace qtgui
