#include "test_cpptools.h"
#include "test_qttools.h"

#ifdef FOUGTOOLS_HAVE_OCCTOOLS
# include "test_occtools.h"
#endif // FOUGTOOLS_HAVE_OCCTOOLS

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    // Run tests
    std::vector<QObject*> testObjects;
    testObjects.push_back(new TestCppTools);
    testObjects.push_back(new TestQtTools);
#ifdef FOUGTOOLS_HAVE_OCCTOOLS
    testObjects.push_back(new TestOccTools);
#endif // FOUGTOOLS_HAVE_OCCTOOLS

    int exitCode = 0;
    for (auto testObj : testObjects) {
        exitCode += QTest::qExec(testObj, argc, argv);
        delete testObj;
    }
    if (exitCode != 0)
        std::cout << exitCode << " failed" << std::endl;
    return exitCode;
}
