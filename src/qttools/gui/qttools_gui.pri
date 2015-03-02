INCLUDEPATH += $$PWD/.. $$PWD/../..

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

HEADERS += \
    $$PWD/abstract_length_editor.h \
    $$PWD/code_editor.h \
    $$PWD/gui.h \
    $$PWD/indexed_selection_model.h \
    $$PWD/length_double_spinbox.h \
    $$PWD/quantity_editor_manager.h \
    $$PWD/line_numbers_bar.h \
    $$PWD/measurement_system_preferences.h \
    $$PWD/message_dialog.h \
    $$PWD/proxy_styled_item_delegate.h \
    $$PWD/qcombo_box_current_item_keeper.h \
    $$PWD/qstandard_item_explorer.h \
    $$PWD/tree_combo_box.h \
    $$PWD/item_view_buttons.h \
    $$PWD/wait_dialog.h \
    $$PWD/strict_stack_widget.h \
    $$PWD/abstract_quantity_editor.h \
    $$PWD/item_view_utils.h \
    $$PWD/qcombo_box_utils.h \
    $$PWD/qwidget_utils.h \
    \
    $$PWD/../core/qsignal_mapper_utils.h

SOURCES += \
    $$PWD/abstract_length_editor.cpp \
    $$PWD/code_editor.cpp \
    $$PWD/indexed_selection_model.cpp \
    $$PWD/length_double_spinbox.cpp \
    $$PWD/quantity_editor_manager.cpp \
    $$PWD/line_numbers_bar.cpp \
    $$PWD/measurement_system_preferences.cpp \
    $$PWD/message_dialog.cpp \
    $$PWD/proxy_styled_item_delegate.cpp \
    $$PWD/qcombo_box_current_item_keeper.cpp \
    $$PWD/qstandard_item_explorer.cpp \
    $$PWD/tree_combo_box.cpp \
    $$PWD/item_view_buttons.cpp \
    $$PWD/wait_dialog.cpp \
    $$PWD/strict_stack_widget.cpp \
    $$PWD/abstract_quantity_editor.cpp \
    $$PWD/item_view_utils.cpp \
    $$PWD/qcombo_box_utils.cpp \
    $$PWD/qwidget_utils.cpp \
    \
    $$PWD/../core/qsignal_mapper_utils.cpp
