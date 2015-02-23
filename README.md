Introduction
============

This is FougTools v0.6dev

FougTools is a collection of utility tools for the C++ language, Qt and 
Open Cascade toolkits.

Check doxygen generated documentation at:
    http://www.fougsys.fr/projects/fougtools_doc


Building FougTools
==================

Create a file named `_local_config.pri` in the folder where FougTools will
be built and define the following variables, depending on your needs:

    PREFIX_DIR = /opt/lib/fougtools/build  # Everything will be installed here
    CONFIG += occtools                     # If you want to build occtools (optional)
    occtools:CONFIG(debug, debug|release) {
        CASCADE_ROOT = /opt/lib/occ/build  # Path to build dir of OpenCascade(debug)
    } else {
        CASCADE_ROOT = /opt/lib/occ/build  # Path to build dir of OpenCascade(release)
    }
    CONFIG += build_utest     # If you want to build unit tests
    CONFIG += build_exmaples  # If you want to build examples

Or use Ruby configure script `qmake/configure.rb`.
It will generate the `_local_config.pri` file for you, see help with:

    ruby $FOUGTOOLS/qmake/configure.rb -h

Note that on Windows, qmake complains about deprecated support of
backslash '\' characters.
So you may have to escape backslashes like `C:\\path\\to\\opencascade`
or simply use Unix separators instead `C:/path/to/opencascade`

Once configuration is done, then type: 

    qmake -r $FOUGTOOLS/qmake/fougtools.pro
    (n)make
    (n)make install


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
