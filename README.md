FougTools: Handy C++ libraries
==============================

This is FougTools v0.7dev

FougTools is a collection of utility libraries for the C++ language, Qt and
Open Cascade toolkits.

Check doxygen generated documentation at:
    http://www.fougsys.fr/projects/fougtools_doc


Building FougTools
==================

Create a file named `_local_config.pri` in the folder where FougTools will
be built and define the following variables, depending on your needs:
~~~~~~~~~~~~~{.sh}
    # Everything will be installed here
    PREFIX_DIR = /opt/lib/fougtools/install

    # Build static libraries (use "+= shared_libs" for DLLs)
    CONFIG += static_libs

    # If you want to build occtools (optional)
    CONFIG += occtools
    occtools:CONFIG(debug, debug|release) {
        # Path to build directory of OpenCascade(debug)
        CASCADE_ROOT = /opt/lib/opencascade/debug/install
    } else {
        # Path to build directory of OpenCascade(release)
        CASCADE_ROOT = /opt/lib/opencascade/release/install
    }

    # If you want to build unit tests and examples
    CONFIG += build_utest  build_examples
~~~~~~~~~~~~~

Or use Ruby configure script `qmake/configure.rb`.
It will generate the `_local_config.pri` file for you, see help with:
~~~~~~~~~~~~~{.sh}
    ruby $FOUGTOOLS/qmake/configure.rb -h
~~~~~~~~~~~~~

Note that on Windows, qmake complains about deprecated support of
backslash '\' characters.
So you may have to escape backslashes like `C:\\path\\to\\opencascade`
or simply use Unix separators instead `C:/path/to/opencascade`

Once configuration is done, then type: 
~~~~~~~~~~~~~{.sh}
    qmake -r $FOUGTOOLS/qmake/fougtools.pro
    (n)make
    (n)make install
~~~~~~~~~~~~~


Coding style
============

The coding style is borrowed from Qt-Creator:
  http://doc-snapshot.qt-project.org/qtcreator-extending/coding-style.html

With these exceptions:

  * Formatting/Capitalizing Identifiers: namespace names begin with a lower case letter
  * Use this pattern for pimpl class:
~~~~~~~~~~~~~{.cpp}
       class Foo
       {
       public:
         Foo();
         // API ...

       private:
         class Private;
         Private* const d;
       };
~~~~~~~~~~~~~
  This has the advantage to not have to forward declare the Private class outside Foo


How to report a bug
===================

If you think you have found a bug in FougTools, we would like to hear
about it so that we can fix it. The FougTools bug tracking system is
open to the public at https://github.com/fougsys/fougtools/issues.

Before reporting a bug, please use the bug-tracker's search functions
to see if the issue is already known.

Always include the following information in your bug report: the name
and version number of your compiler; the name and version number of
your operating system; the version of FougTools you are using, and
what configure options it was compiled with.

If the problem you are reporting is only visible at run-time, try to
create a small test program that shows the problem when run.


License
=======

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
http://www.cecill.info

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
