#pragma once

#include <QtTest/QTest>

class TestQtTools : public QObject
{
    Q_OBJECT

private slots:
    // Core
    void core_QLocaleUtils_test();

    // Gui
    void gui_QStandardItemExplorer_test();

    // Script
    void script_Calculator_test();

    // Sql
    void sql_SqlCppEnumMap_test();

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK
    // Task
    void task_Manager_test();
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK
};
