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

#include "qttools/gui/line_numbers_bar.h"

#include <QtCore/QRect>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QScrollBar>
#include <QtGui/QTextBlock>
#include <QtGui/QTextDocument>
#include <QtGui/QTextEdit>
#include <QtGui/QToolTip>

namespace qttools {

/*! \class LineNumbersBarPrivate
 *  \brief Internal (pimpl of LineNumbersBar)
 */
class LineNumbersBarPrivate
{
public:
  LineNumbersBarPrivate() :
    edit(0),
    stopRect(),
    currentRect(),
    bugRect(),
    stopLine(-1),
    currentLine(-1),
    bugLine(-1),
    stopMarker(),
    currentMarker(),
    bugMarker()
  {
  }

  QTextEdit* edit;
  QRect stopRect;
  QRect currentRect;
  QRect bugRect;
  int stopLine;
  int currentLine;
  int bugLine;
  QPixmap stopMarker;
  QPixmap currentMarker;
  QPixmap bugMarker;
};



/*! \class LineNumbersBar
 *  \brief Provides numbering of the lines of a QTextEdit as a vertical bar
 */

LineNumbersBar::LineNumbersBar(QWidget *parent) :
  QWidget(parent),
  _d(new LineNumbersBarPrivate)
{
  // Make room for 4 digits and the breakpoint icon
  this->setFixedWidth(this->fontMetrics().width(QString("000") + 10 + 32));
  //  _d->stopMarker = QPixmap( "images/no.png" );
  //   currentMarker = QPixmap( "images/next.png" );
  //   bugMarker = QPixmap( "images/bug.png" );
}

LineNumbersBar::~LineNumbersBar()
{
  delete _d;
}

void LineNumbersBar::setCurrentLine(int lineno)
{
  _d->currentLine = lineno;
}

void LineNumbersBar::setStopLine(int lineno)
{
  _d->stopLine = lineno;
}

void LineNumbersBar::setBugLine(int lineno)
{
  _d->bugLine = lineno;
}

void LineNumbersBar::setTextEdit(QTextEdit* edit)
{
  _d->edit = edit;
  connect(edit->document()->documentLayout(), SIGNAL(update(const QRectF&)),
          this, SLOT(update()));
  connect(edit->verticalScrollBar(), SIGNAL(valueChanged(int)),
          this, SLOT(update()));
}

void LineNumbersBar::paintEvent(QPaintEvent* /*event*/)
{
  QAbstractTextDocumentLayout* layout = _d->edit->document()->documentLayout();
  int contentsY = _d->edit->verticalScrollBar()->value();
  qreal pageBottom = contentsY + _d->edit->viewport()->height();
  const QFontMetrics fm = this->fontMetrics();
  const int ascent = this->fontMetrics().ascent() + 1; // height = ascent + descent + 1
  int lineCount = 1;
  QPainter p(this);

  _d->bugRect = QRect();
  _d->stopRect = QRect();
  _d->currentRect = QRect();

  for (QTextBlock block = _d->edit->document()->begin();
       block.isValid();
       block = block.next(), ++lineCount) {
    const QRectF boundingRect(layout->blockBoundingRect(block));
    QPointF position(boundingRect.topLeft());
    if (position.y() + boundingRect.height() < contentsY)
      continue;
    if (position.y() > pageBottom)
      break;
    const QString txt(QString::number(lineCount));
    p.drawText(this->width() - fm.width(txt),
               qRound(position.y() ) - contentsY + ascent, txt);
    // Bug marker
    if (_d->bugLine == lineCount) {
      p.drawPixmap(1, qRound(position.y() ) - contentsY, _d->bugMarker);
      _d->bugRect = QRect(1, qRound(position.y()) - contentsY,
                          _d->bugMarker.width(),
                          _d->bugMarker.height());
    }
    // Stop marker
    if (_d->stopLine == lineCount) {
      p.drawPixmap(19, qRound(position.y()) - contentsY, _d->stopMarker);
      _d->stopRect = QRect(19, qRound(position.y()) - contentsY,
                           _d->stopMarker.width(),
                           _d->stopMarker.height());
    }
    // Current line marker
    if (_d->currentLine == lineCount) {
      p.drawPixmap(19, qRound(position.y()) - contentsY, _d->currentMarker);
      _d->currentRect = QRect(19, qRound(position.y()) - contentsY,
                              _d->currentMarker.width(),
                              _d->currentMarker.height());
    }
  }
}

bool LineNumbersBar::event(QEvent* event)
{
  if (event->type() == QEvent::ToolTip) {
    QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
    if (_d->stopRect.contains(helpEvent->pos()))
      QToolTip::showText(helpEvent->globalPos(), "Stop Here");
    else if (_d->currentRect.contains(helpEvent->pos()))
      QToolTip::showText( helpEvent->globalPos(), "Current Line" );
    else if (_d->bugRect.contains(helpEvent->pos()))
      QToolTip::showText( helpEvent->globalPos(), "Error Line" );
  }
  return QWidget::event(event);
}

} // namespace qttools
