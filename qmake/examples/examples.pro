include(../config.pri)

TEMPLATE = subdirs
SUBDIRS  = \
    qttools_item_view_buttons \
    qttools_length_editor \
    qttools_tree_combo_box

occtools:SUBDIRS += occtools_qtviewer
