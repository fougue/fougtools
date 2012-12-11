include(config.pri)

TEMPLATE = subdirs
CONFIG *= ordered
SUBDIRS += qttools_core \
           qttools_gui \
           qttools_network \
           qttools_sql

occtools:SUBDIRS += occtools
