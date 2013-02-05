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

INCLUDEPATH *= $$PWD/.. $$PWD/../..

QT *= gui declarative

HEADERS += \
    $$PWD/length_double_spinbox.h \
    $$PWD/line_edit_with_auto_tool_tip.h \
    $$PWD/line_numbers_bar.h \
    $$PWD/qcombo_box_current_item_keeper.h \
    $$PWD/qstandard_item_explorer.h \
    $$PWD/wait_dialog.h \
    $$PWD/widget_tools.h \
    $$PWD/gui.h \
    $$PWD/measurement_system_preferences.h \
    $$PWD/length_editor_manager.h \
    $$PWD/abstract_length_editor.h \
    $$PWD/item_view_tools.h \
    $$PWD/indexed_selection_model.h \
    $$PWD/message_dialog.h \
    $$PWD/tree_combo_box.h \
    $$PWD/qml_tools.h

SOURCES += \
    $$PWD/length_double_spinbox.cpp \
    $$PWD/line_edit_with_auto_tool_tip.cpp \
    $$PWD/line_numbers_bar.cpp \
    $$PWD/qcombo_box_current_item_keeper.cpp \
    $$PWD/qstandard_item_explorer.cpp \
    $$PWD/wait_dialog.cpp \
    $$PWD/widget_tools.cpp \
    $$PWD/measurement_system_preferences.cpp \
    $$PWD/length_editor_manager.cpp \
    $$PWD/abstract_length_editor.cpp \
    $$PWD/item_view_tools.cpp \
    $$PWD/indexed_selection_model.cpp \
    $$PWD/message_dialog.cpp \
    $$PWD/tree_combo_box.cpp \
    $$PWD/qml_tools.cpp

HEADERS += $$PWD/../core/task.h
SOURCES += $$PWD/../core/task.cpp
