#pragma once

#include <QtCore/QObject>

namespace Task {

class BaseRunner;
class Manager;

/*! \brief Provides task Qt signals, to be forwarded to the Manager object
 *
 *  RunnerSignals allows BaseRunner to not have to inherit from QObject, instead
 *  BaseRunner embeds RunnerSignals instance.
 */
class RunnerSignals : public QObject
{
    Q_OBJECT

public:
    RunnerSignals(BaseRunner* runner, QObject* parent = nullptr);

    void emitAboutToRun();
    void emitStarted(const QString& title);
    void emitProgressStep(const QString &title);
    void emitProgress(int pct);
    void emitMessage(const QString &msg);
    void emitEnded();

signals:
    void aboutToRun(BaseRunner* runner);
    void started(quint64 taskId, const QString& title);
    void progressStep(quint64 taskId, const QString& title);
    void progress(quint64 taskId, int pct);
    void message(quint64 taskId, const QString& msg);
    void ended(quint64 taskId);

private:
    BaseRunner* m_runner;
};

} // namespace Task
