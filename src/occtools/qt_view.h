/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
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

#ifndef OCC_QT_VIEW_H
#define OCC_QT_VIEW_H

#include "occtools.h"

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
# include "../cpptools/functor.h"
#endif

#include <QWidget>

#include <Aspect_GraphicCallbackProc.hxx>
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_V3d_View.hxx>

namespace occ {

class OCCTOOLS_EXPORT QtView : public QWidget
{
  Q_OBJECT

public:
  QtView(const Handle_AIS_InteractiveContext& context3d, QWidget* parent = NULL);
  ~QtView();

  Handle_AIS_InteractiveContext context() const;
  Handle_V3d_View internalView() const;

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
  typedef cpp::Functor0<void> PaintCallback;
  int addPaintCallback(const PaintCallback& callback);
  void removePaintCallback(int callbackId);
  Aspect_GraphicCallbackStruct* paintCallbackData() const;
#endif

  QPaintEngine* paintEngine() const;

public slots:
  void redraw();
  void fitAll();

protected:
  void paintEvent(QPaintEvent* event);
  void resizeEvent(QResizeEvent* event);

private:
  friend int occ_QtView_paintCallBack(Aspect_Drawable, void*, Aspect_GraphicCallbackStruct*);
  class Private;
  Private* const d;
};

} // namespace occ

#endif // OCC_QT_VIEW_H
