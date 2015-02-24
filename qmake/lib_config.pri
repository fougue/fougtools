include(config.pri)

TEMPLATE = lib

CONFIG(shared_libs):CONFIG += dll
CONFIG(static_libs):CONFIG += static
