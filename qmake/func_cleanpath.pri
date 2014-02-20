# Declare and define portable function cleanPath(string)
#   For Qt5 it is just a wrapper around clean_path()
#   clean_path() does not exist in Qt4, so cleanPath() is portable
#
#   Doc: Returns path with directory separators normalized (converted to "/")
#        and redundant ones removed, and "."s and ".."s resolved (as far as possible).
#        This function is a wrapper around QDir::cleanPath.
#        (See https://qt-project.org/doc/qt-5.0/qtdoc/qmake-function-reference.html#clean-path-path)
isEqual(QT_MAJOR_VERSION, 5) {

    defineReplace(cleanPath) {
        return($$clean_path($$1))
    }

} else { # qt4

    defineReplace(cleanPath) {
        win32:1 ~= s|\\\\|/|g
        contains(1, ^/.*):pfx = /
        else:pfx =
        segs = $$split(1, /)
        out =
        for(seg, segs) {
            equals(seg, ..):out = $$member(out, 0, -2)
            else:!equals(seg, .):out += $$seg
        }
        return($$join(out, /, $$pfx))
    }

} # qt5
