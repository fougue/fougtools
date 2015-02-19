#include "length_editor_widget.h"
#include "ui_length_editor_widget.h"

#include <QtCore/QtDebug>
#include <qttools/gui/abstract_length_editor.h>
#include <qttools/gui/quantity_editor_manager.h>

LengthEditorWidget::LengthEditorWidget(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::LengthEditorWidget)
{
    m_ui->setupUi(this);
    connect(m_ui->systemCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSystemComboBoxChanged(int)));
    connect(m_ui->unitCombo, SIGNAL(activated(int)),
            this, SLOT(onUnitComboBoxChanged(int)));
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
        qttools::QuantityEditorManager::globalInstance()->setMeasurementSystem(QLocale::MetricSystem);
        foreach (qttools::AbstractLengthEditor::MetricUnit unit, qttools::AbstractLengthEditor::allMetricUnits())
            m_ui->unitCombo->addItem(qttools::AbstractLengthEditor::unitText(unit), QVariant::fromValue(unit));
        this->selectPreferredUnit(qttools::AbstractLengthEditor::unitText(m_ui->lenSpin->preferredMetricUnit()));
    }
    else if (id == 1) {
        qttools::QuantityEditorManager::globalInstance()->setMeasurementSystem(QLocale::ImperialSystem);
        foreach (qttools::AbstractLengthEditor::ImperialUnit unit, qttools::AbstractLengthEditor::allImperialUnits())
            m_ui->unitCombo->addItem(qttools::AbstractLengthEditor::unitText(unit), QVariant::fromValue(unit));
        this->selectPreferredUnit(qttools::AbstractLengthEditor::unitText(m_ui->lenSpin->preferredImperialUnit()));
    }
}

void LengthEditorWidget::onUnitComboBoxChanged(int id)
{
    if (m_ui->systemCombo->currentIndex() == 0) {
        m_ui->lenSpin->setPreferredMetricUnit(
                    m_ui->unitCombo->itemData(id).value<qttools::AbstractLengthEditor::MetricUnit>());
    }
    else if (m_ui->systemCombo->currentIndex() == 1) {
        m_ui->lenSpin->setPreferredImperialUnit(
                    m_ui->unitCombo->itemData(id).value<qttools::AbstractLengthEditor::ImperialUnit>());
    }
}

void LengthEditorWidget::selectPreferredUnit(const QString &unitText)
{
    m_ui->unitCombo->setCurrentIndex(m_ui->unitCombo->findText(unitText));
}
