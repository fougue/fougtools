#include <QApplication>
#include <QtCore/QtDebug>

#include "length_editor_widget.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  LengthEditorWidget lenEditor;
  lenEditor.show();
  return app.exec();
}
