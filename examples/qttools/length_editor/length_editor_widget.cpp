#include "length_editor_widget.h"
#include "ui_length_editor_widget.h"

#include <QtCore/QtDebug>
#include <qttools/gui/abstract_length_editor.h>
#include <qttools/gui/quantity_editor_manager.h>
#include <qttools/gui/qcombo_box_utils.h>

LengthEditorWidget::LengthEditorWidget(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::LengthEditorWidget)
{
    m_ui->setupUi(this);
    QObject::connect(m_ui->systemCombo, qtgui::QComboBoxUtils::signalCurrentIndexChanged_int(),
                     this, &LengthEditorWidget::onSystemComboBoxChanged);
    QObject::connect(m_ui->unitCombo, qtgui::QComboBoxUtils::signalActivated_int(),
                     this, &LengthEditorWidget::onUnitComboBoxChanged);
    this->onSystemComboBoxChanged(0);
}

LengthEditorWidget::~LengthEditorWidget()
{
    delete m_ui;
}

void LengthEditorWidget::onSystemComboBoxChanged(int id)
{
    m_ui->unitCombo->clear();
    if (id == 0) {
        qtgui::QuantityEditorManager::globalInstance()->setMeasurementSystem(QLocale::MetricSystem);
        foreach (qtgui::AbstractLengthEditor::MetricUnit unit, qtgui::AbstractLengthEditor::allMetricUnits())
            m_ui->unitCombo->addItem(qtgui::AbstractLengthEditor::unitText(unit), QVariant::fromValue(unit));
        this->selectPreferredUnit(qtgui::AbstractLengthEditor::unitText(m_ui->lenSpin->preferredMetricUnit()));
    }
    else if (id == 1) {
        qtgui::QuantityEditorManager::globalInstance()->setMeasurementSystem(QLocale::ImperialSystem);
        foreach (qtgui::AbstractLengthEditor::ImperialUnit unit, qtgui::AbstractLengthEditor::allImperialUnits())
            m_ui->unitCombo->addItem(qtgui::AbstractLengthEditor::unitText(unit), QVariant::fromValue(unit));
        this->selectPreferredUnit(qtgui::AbstractLengthEditor::unitText(m_ui->lenSpin->preferredImperialUnit()));
    }
}

void LengthEditorWidget::onUnitComboBoxChanged(int id)
{
    if (m_ui->systemCombo->currentIndex() == 0) {
        m_ui->lenSpin->setPreferredMetricUnit(
                    m_ui->unitCombo->itemData(id).value<qtgui::AbstractLengthEditor::MetricUnit>());
    }
    else if (m_ui->systemCombo->currentIndex() == 1) {
        m_ui->lenSpin->setPreferredImperialUnit(
                    m_ui->unitCombo->itemData(id).value<qtgui::AbstractLengthEditor::ImperialUnit>());
    }
}

void LengthEditorWidget::selectPreferredUnit(const QString &unitText)
{
    m_ui->unitCombo->setCurrentIndex(m_ui->unitCombo->findText(unitText));
}
