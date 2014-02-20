# Declare and define portable function systemPath(string)
#   For Qt5 it is just a wrapper around system_path()
#   system_path() does not exist in Qt4, so systemPath() is portable
#
#   Doc: Converts all directory separators within path to separators that are
#        compatible with the shell that is used by the system() functions to invoke commands.
#        For example, slashes are converted to backslashes for the Windows shell.
#        (See https://qt-project.org/doc/qt-5.1/qmake/qmake-function-reference.html#system-path-path
isEqual(QT_MAJOR_VERSION, 5) {

    defineReplace(systemPath) {
        return($$system_path($$1))
    }

} else { # qt4

    defineReplace(systemPath) {
        win32:1 ~= s||/\\\\|g
        else:1 ~= s|\\\\|/|g
    }

} # qt5
