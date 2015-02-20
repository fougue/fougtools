#pragma once

#include "RunnableSignals.h"

namespace Task {

class Runnable;

/*! \brief Base class for all runner objects
 *
 *  BaseRunner provides control over a Runnable object : start/abort
 */
class BaseRunner
{
public:
    BaseRunner(Runnable* runnable);
    virtual ~BaseRunner();

    inline RunnableSignals* taskSignals()
    { return &m_signals; }

    inline Runnable* runnable()
    { return m_runnable; }

    void execRunnableFunc();

    virtual bool isAbortRequested();

    virtual void requestAbort();

    virtual void launch();

private:
    RunnableSignals m_signals;
    Runnable* m_runnable;
};

} // namespace Task
