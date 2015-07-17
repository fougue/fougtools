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

#include "quantity_editor_manager.h"

#include "abstract_quantity_editor.h"

namespace qtgui {

namespace internal {

class QuantityEditorManagerCreator : public QuantityEditorManager
{
public:
    QuantityEditorManagerCreator()
    { }

    ~QuantityEditorManagerCreator()
    { }
};

} // namespace internal

/*!
 * \class QuantityEditorManager
 * \brief Manages a set of AbstractQuantityEditor objects that will get notified
 *        when the current measurement system is changed
 *
 * \headerfile quantity_editor_manager.h <qttools/gui/quantity_editor_manager.h>
 * \ingroup qttools_gui
 */

QuantityEditorManager::QuantityEditorManager()
    : m_measureSys(QLocale::MetricSystem)
{
}

QuantityEditorManager::~QuantityEditorManager()
{
}

void QuantityEditorManager::attach(AbstractQuantityEditor* editor)
{
    if (editor != NULL)
        m_qtyEditors.insert(editor);
}

void QuantityEditorManager::detach(AbstractQuantityEditor* editor)
{
    if (editor != NULL)
        m_qtyEditors.remove(editor);
}

Q_GLOBAL_STATIC(internal::QuantityEditorManagerCreator, globalCoreInstance)

QuantityEditorManager* QuantityEditorManager::globalInstance()
{
    return globalCoreInstance();
}

QLocale::MeasurementSystem QuantityEditorManager::measurementSytem() const
{
    return m_measureSys;
}

void QuantityEditorManager::setMeasurementSystem(QLocale::MeasurementSystem sys)
{
    if (sys == m_measureSys)
        return;

    foreach (AbstractQuantityEditor* qtyEditor, m_qtyEditors)
        qtyEditor->updateEditor(sys);
    m_measureSys = sys;
    emit currentMeasurementSytemChanged(sys);
}

} // namespace qtgui
