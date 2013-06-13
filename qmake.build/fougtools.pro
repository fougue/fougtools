include(config.pri)

TEMPLATE = subdirs
CONFIG *= ordered
SUBDIRS += qttools_core \
           qttools_gui \
           qttools_qml \
           qttools_network \
           qttools_script \
           qttools_sql

occtools:SUBDIRS += occtools
utest:SUBDIRS += ../utest

HEADERS += ../src/fougtools_global.h

# INSTALLS for globals
globals_include.path  = $$PREFIX_DIR/include
globals_include.files = ../src/*.h
INSTALLS += globals_include

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
