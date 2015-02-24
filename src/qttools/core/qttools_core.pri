#############################################################################
##
##  FougTools
##  Copyright FougSys (1 Mar. 2011)
##  contact@fougsys.fr
##
## This software is a computer program whose purpose is to provide utility
## tools for the C++ language and the Qt toolkit.
##
## This software is governed by the CeCILL-C license under French law and
## abiding by the rules of distribution of free software.  You can  use,
## modify and/ or redistribute the software under the terms of the CeCILL-C
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info".
##
## As a counterpart to the access to the source code and  rights to copy,
## modify and redistribute granted by the license, users are provided only
## with a limited warranty  and the software's author,  the holder of the
## economic rights,  and the successive licensors  have only  limited
## liability.
##
## In this respect, the user's attention is drawn to the risks associated
## with loading,  using,  modifying and/or developing or reproducing the
## software by the user in light of its specific status of free software,
## that may mean  that it is complicated to manipulate,  and  that  also
## therefore means  that it is reserved for developers  and  experienced
## professionals having in-depth computer knowledge. Users are therefore
## encouraged to load and test the software's suitability as regards their
## requirements in conditions enabling the security of their systems and/or
## data to be ensured and,  more generally, to use and operate it in the
## same conditions as regards security.
##
## The fact that you are presently reading this means that you have had
## knowledge of the CeCILL-C license and that you accept its terms.
##
#############################################################################

HEADERS += \
    $$PWD/abstract_cipher.h \
    $$PWD/plugins_loader.h \
    $$PWD/abstract_signal_dispatch.h \
    $$PWD/core.h \
    $$PWD/grid_numbering.h \
    $$PWD/grid_struct.h \
    $$PWD/log.h \
    $$PWD/log_unqualified.h \
    $$PWD/qobject_wrap.h \
    $$PWD/qt_plugin_def.h \
    $$PWD/runtime_error.h \
    $$PWD/scoped_connection.h \
    $$PWD/singleton.h \
    $$PWD/sleep.h \
    $$PWD/wait_loop.h \
    $$PWD/wait_loop_stop_condition.h \
    $$PWD/unique_id.h \
    $$PWD/plugins_loader_instance_filter.h \
    $$PWD/plugins_loader_instance_iface_filter.h \
    \
    $$PWD/internal/wait_loop_p.h \
    $$PWD/internal/wait_loop_time_out_stop_condition.h \
    $$PWD/item_model_utils.h \
    $$PWD/qatomic_utils.h \
    $$PWD/qlocale_utils.h \
    $$PWD/qobject_utils.h \
    $$PWD/qsignal_mapper_utils.h \
    $$PWD/qstring_utils.h \
    $$PWD/qvariant_utils.h

SOURCES += \
    $$PWD/abstract_cipher.cpp \
    $$PWD/plugins_loader.cpp \
    $$PWD/abstract_signal_dispatch.cpp \
    $$PWD/log.cpp \
    $$PWD/runtime_error.cpp \
    $$PWD/scoped_connection.cpp \
    $$PWD/sleep.cpp \
    $$PWD/grid_numbering.cpp \
    $$PWD/grid_struct.cpp \
    $$PWD/wait_loop.cpp \
    $$PWD/wait_loop_stop_condition.cpp \
    $$PWD/unique_id.cpp \
    $$PWD/plugins_loader_instance_filter.cpp \
    $$PWD/plugins_loader_instance_iface_filter.cpp \
    \
    $$PWD/internal/wait_loop_p.cpp \
    $$PWD/internal/wait_loop_time_out_stop_condition.cpp \
    $$PWD/item_model_utils.cpp \
    $$PWD/qatomic_utils.cpp \
    $$PWD/qlocale_utils.cpp \
    $$PWD/qobject_utils.cpp \
    $$PWD/qsignal_mapper_utils.cpp \
    $$PWD/qstring_utils.cpp
