# Config tests
load(configure)
#CONFIG += recheck
qtCompileTest(variadic_templates)
#config_variadic_templates:message(Variadic templates supported)

include(config.pri)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += qttools_core \
           qttools_gui \
           qttools_qml \
           qttools_network \
           qttools_script \
           qttools_sql

qttools_task {
    SUBDIRS += qttools_task
} else {
    warning(qttools_task will not be built : requires support of C++11 variadic templates and Qt >= 5.4.0)
}

occtools:SUBDIRS += occtools
build_utest:SUBDIRS += utest
build_examples:SUBDIRS += examples

HEADERS += ../src/fougtools_global.h

FOUGTOOLS_QMAKE_PATH = $$PWD # QMake substitution does not expand $$PWD correctly
fougtools_pri.input = $$PWD/fougtools.pri.in
fougtools_pri.output = $$PREFIX_DIR/qmake/fougtools.pri
QMAKE_SUBSTITUTES += fougtools_pri

OTHER_FILES += \
    configure.rb \
    fougtools.pri.body \
    fougtools.pri.in \
    ../README.md \
    ../doc/Doxyfile

# INSTALLS for globals
globals_qmake.path  = $$PREFIX_DIR/qmake
globals_qmake.files = \
    compiler_config.pri \
    func_cleanpath.pri \
    func_minqtversion.pri \
    func_systempath.pri \
    func_vcs_revnum.pri

globals_include.path  = $$PREFIX_DIR/include
globals_include.files = ../src/*.h

INSTALLS += globals_qmake globals_include

# INSTALLS for cpptools
cpptools_include.path  = $$PREFIX_DIR/include/cpptools
cpptools_include.files = ../src/cpptools/*.h
INSTALLS += cpptools_include

# INSTALLS for mathtools
mathtools_include.path  = $$PREFIX_DIR/include/mathtools
mathtools_include.files = ../src/mathtools/*.h
INSTALLS += mathtools_include

# INSTALLS for scripts
scripts.path  = $$PREFIX_DIR/scripts
scripts.files = ../scripts/*.rb
INSTALLS += scripts

# Automatic generation of version infos
VER_MAJ = 0
VER_MIN = 7
VER_PAT = 0
include(func_vcs_revnum.pri)
_FOUGTOOLS_VERSION = "$$VER_MAJ"."$$VER_MIN"."$$VER_PAT"dev-$$vcs_revnum(git, $$PWD)
message(FougTools v$$_FOUGTOOLS_VERSION)

# Add custom "doc" target
_CMD_SEP = ;
win32:_CMD_SEP = &
gendoc.target   = doc
gendoc.commands = \
    $$QMAKE_COPY $$[QT_INSTALL_DOCS]/qtcore/qtcore.tags $$PWD/../doc $$_CMD_SEP \
    $$QMAKE_COPY $$[QT_INSTALL_DOCS]/qtgui/qtgui.tags $$PWD/../doc $$_CMD_SEP \
    $$QMAKE_COPY $$[QT_INSTALL_DOCS]/qtwidgets/qtwidgets.tags $$PWD/../doc $$_CMD_SEP \
    $$QMAKE_COPY $$[QT_INSTALL_DOCS]/qtsql/qtsql.tags $$PWD/../doc $$_CMD_SEP \
    echo PROJECT_NUMBER = $$_FOUGTOOLS_VERSION > $$PWD/../doc/_project_number.dox $$_CMD_SEP \
    cd $$PWD/../doc $$_CMD_SEP \
    doxygen Doxyfile $$_CMD_SEP \
    cd $$PWD
QMAKE_EXTRA_TARGETS += gendoc
