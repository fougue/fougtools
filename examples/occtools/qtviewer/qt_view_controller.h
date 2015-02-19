#ifndef QT_VIEW_CONTROLLER_H
#define QT_VIEW_CONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QPoint>

namespace occ { class QtView; }

class QtViewController : public QObject
{
    Q_OBJECT

public:
    QtViewController(occ::QtView* qtView = NULL);

    bool eventFilter(QObject* watched, QEvent* event);

private slots:
    void showActionMenu(const QPoint& pos);

private:
    QPoint m_prevPos;
    occ::QtView* m_qtView;
};

#endif // QT_VIEW_CONTROLLER_H
