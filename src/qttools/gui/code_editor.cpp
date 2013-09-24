/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "code_editor.h"

#include <QtGui/QPainter>
#include <QtGui/QTextBlock>

namespace qttools {

/*! \class CodeEditor::Private
 *  \brief Pimpl of CodeEditor (internal)
 */
class CodeEditor::Private
{
public:
  Private(CodeEditor* backPtr);

  void lineNumberAreaPaintEvent(QPaintEvent *event);
  int lineNumberAreaWidth();

  void updateLineNumberAreaWidth(int newBlockCount);
  void highlightCurrentLine();
  void updateLineNumberArea(const QRect &rect, int dy);

  CodeEditor* m_backPtr;
  QWidget* m_lineNumberArea;
};

/*! \class CodeEditor::LineNumberArea
 *  \brief Provides a buddy widget with line numbering capacity (internal)
 */

class CodeEditor::LineNumberArea : public QWidget
{
public:
  LineNumberArea(CodeEditor::Private *editor);

  QSize sizeHint() const;

protected:
  void paintEvent(QPaintEvent *event);

private:
  CodeEditor::Private* m_codeEditor;
};

CodeEditor::LineNumberArea::LineNumberArea(CodeEditor::Private *editor)
  : QWidget(editor->m_backPtr),
    m_codeEditor(editor)
{
}

QSize CodeEditor::LineNumberArea::sizeHint() const
{
  return QSize(m_codeEditor->lineNumberAreaWidth(), 0);
}

void CodeEditor::LineNumberArea::paintEvent(QPaintEvent *event)
{
  m_codeEditor->lineNumberAreaPaintEvent(event);
}

CodeEditor::Private::Private(CodeEditor* backPtr)
  : m_backPtr(backPtr),
    m_lineNumberArea(new CodeEditor::LineNumberArea(this))
{
}

int CodeEditor::Private::lineNumberAreaWidth()
{
  int digits = 1;
  int max = qMax(1, m_backPtr->blockCount());
  while (max >= 10) {
    max /= 10;
    ++digits;
  }

  return 3 + m_backPtr->fontMetrics().width(QLatin1Char('9')) * digits;
}

void CodeEditor::Private::lineNumberAreaPaintEvent(QPaintEvent *event)
{
  QPainter painter(m_lineNumberArea);
  painter.fillRect(event->rect(), Qt::lightGray);

  QTextBlock block = m_backPtr->firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = (int) m_backPtr->blockBoundingGeometry(block).translated(m_backPtr->contentOffset()).top();
  int bottom = top + (int) m_backPtr->blockBoundingRect(block).height();

  while (block.isValid() && top <= event->rect().bottom()) {
    if (block.isVisible() && bottom >= event->rect().top()) {
      painter.setPen(Qt::black);
      painter.drawText(0, top, m_lineNumberArea->width(), m_backPtr->fontMetrics().height(),
                       Qt::AlignRight, QString::number(blockNumber + 1));
    }

    block = block.next();
    top = bottom;
    bottom = top + (int) m_backPtr->blockBoundingRect(block).height();
    ++blockNumber;
  }
}

void CodeEditor::Private::updateLineNumberAreaWidth(int newBlockCount)
{
  Q_UNUSED(newBlockCount);
  m_backPtr->setViewportMargins(this->lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::Private::highlightCurrentLine()
{
  QList<QTextEdit::ExtraSelection> extraSelections;

  if (!m_backPtr->isReadOnly()) {
    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(Qt::yellow).lighter(160);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = m_backPtr->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
  }

  m_backPtr->setExtraSelections(extraSelections);
}

void CodeEditor::Private::updateLineNumberArea(const QRect &rect, int dy)
{
  if (dy)
    m_lineNumberArea->scroll(0, dy);
  else
    m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

  if (rect.contains(m_backPtr->viewport()->rect()))
    this->updateLineNumberAreaWidth(0);
}

/*! \class CodeEditor
 *  \brief Provides a text editor with a line numbering bar
 *
 * \headerfile code_editor.h <qttools/gui/code_editor.h>
 * \ingroup qttools_gui
 *
 */

CodeEditor::CodeEditor(QWidget *parent)
  : QPlainTextEdit(parent),
    d(new Private(this))
{
  connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
  connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
  connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

  d->updateLineNumberAreaWidth(0);
  d->highlightCurrentLine();
}

CodeEditor::~CodeEditor()
{
  delete d;
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
  QPlainTextEdit::resizeEvent(e);

  const QRect cr = this->contentsRect();
  d->m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
                                         d->lineNumberAreaWidth(), cr.height()));
}

} // namespace qttools

#include "moc_code_editor.cpp"
