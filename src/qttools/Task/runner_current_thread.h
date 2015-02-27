#pragma once

#include "base_runner.h"

namespace Task {

struct CurrentThread { };

/*! \brief Task runner executing in the current thread context
 */
template<>
class Runner<CurrentThread> : public BaseRunner
{
public:
    Runner<CurrentThread>(const Manager *mgr)
        : BaseRunner(mgr),
          m_isAbortRequested(false)
    { }

protected:
    bool isAbortRequested() override
    { return m_isAbortRequested; }

    void requestAbort() override
    { m_isAbortRequested = true; }

    void launch() override
    { this->execRunnableFunc(); }

private:
    bool m_isAbortRequested;
};

} // namespace Task
