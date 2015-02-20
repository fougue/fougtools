#pragma once

#include "Runnable.h"

#include <QtCore/QObject>

namespace Task {

/*! \brief Provides task Qt signals, to be forwarded to the Manager object
 *
 *  RunnableSignals allows BaseRunner to not have to inherit from QObject, instead
 *  BaseRunner embeds RunnableSignals instance.
 */
class RunnableSignals : public QObject
{
    Q_OBJECT

public:
    RunnableSignals(Manager* mgr,
                    const Runnable* runnable,
                    QObject* parent = nullptr);

    inline const Runnable* runnable() const
    { return m_runnable; }

    inline void emitStarted(quint64 taskId, const QString& title)
    { emit started(taskId, title); }

    inline void emitProgressStep(const QString &title)
    { emit progressStep(m_runnable->taskId(), title); }

    inline void emitProgress(int pct)
    { emit progress(m_runnable->taskId(), pct); }

    inline void emitMessage(const QString &msg)
    { emit message(m_runnable->taskId(), msg); }

    inline void emitEnded(quint64 taskId)
    { emit ended(taskId); }

signals:
    void started(quint64 taskId, const QString& title);
    void progressStep(quint64 taskId, const QString& title);
    void progress(quint64 taskId, int pct);
    void message(quint64 taskId, const QString& msg);
    void ended(quint64 taskId);

private:
    const Runnable* m_runnable;
};

} // namespace Task
