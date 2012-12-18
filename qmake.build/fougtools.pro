include(config.pri)

TEMPLATE = subdirs
CONFIG *= ordered
SUBDIRS += qttools_core \
           qttools_gui \
           qttools_network \
           qttools_script \
           qttools_sql

occtools:SUBDIRS += occtools

# INSTALLS for cpptools
cpptools_include.path  = $$_PREFIX/include/cpptools
cpptools_include.files = ../src/cpptools/*.h
INSTALLS += cpptools_include

# INSTALLS for mathtools
mathtools_include.path  = $$_PREFIX/include/mathtools
mathtools_include.files = ../src/mathtools/*.h
INSTALLS += mathtools_include
