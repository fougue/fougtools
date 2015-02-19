#ifndef LENGTH_EDITOR_WIDGET_H
#define LENGTH_EDITOR_WIDGET_H

#include <QWidget>

class LengthEditorWidget : public QWidget
{
    Q_OBJECT

public:
    LengthEditorWidget(QWidget *parent = NULL);
    ~LengthEditorWidget();

private slots:
    void onSystemComboBoxChanged(int id);
    void onUnitComboBoxChanged(int id);

private:
    void selectPreferredUnit(const QString& unitText);

    class Ui_LengthEditorWidget *m_ui;
};

#endif // LENGTH_EDITOR_WIDGET_H
