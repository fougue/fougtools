#include <QtCore/QCoreApplication>
#include <QtCore/QList>
#include <QtCore/QtDebug>

#include "test_cpptools.h"
#include "test_qttools_core.h"
#include "test_qttools_gui.h"
#include "test_qttools_script.h"

#ifdef FOUGTOOLS_HAVE_OCCTOOLS
# include "test_occtools.h"
#endif // FOUGTOOLS_HAVE_OCCTOOLS

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK
# include "test_qttools_task.h"
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK

#include <iostream>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    // Parse command line
    QStringList argList;
    for (int i = 0; i < argc; ++i)
        argList.append(QString(argv[i]));

    // Run tests
    QList<QObject*> testObjects;
    testObjects << new TestCppTools
                << new TestQtToolsCore
                << new TestQtToolsGui
                << new TestQtToolsScript;
#ifdef FOUGTOOLS_HAVE_OCCTOOLS
    testObjects << new TestOccTools;
#endif // FOUGTOOLS_HAVE_OCCTOOLS

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK
    testObjects << new TestQtToolsTask;
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK

    int exitCode = 0;
    foreach (QObject* iTestObject, testObjects)
        exitCode += QTest::qExec(iTestObject, argList);

    if (exitCode != 0)
        std::cout << exitCode << " failed" << std::endl;
    qDeleteAll(testObjects);
    return exitCode;
}
