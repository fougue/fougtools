#pragma once

#include "base_runner.h"

#include <future>

namespace Task {

struct StdAsync { };

/*! \brief Task runner based on std::async()
 */
template<>
class Runner<StdAsync> : public BaseRunner
{
public:
    Runner<StdAsync>(const Manager* mgr, std::launch policy = std::launch::async)
        : BaseRunner(mgr),
          m_isAbortRequested(false),
          m_policy(policy)
    { }

protected:
    bool isAbortRequested() override
    { return m_isAbortRequested; }

    void requestAbort() override
    { m_isAbortRequested = true; }

    void launch() override
    { std::async(m_policy, [=] { this->execRunnableFunc(); } ); }

private:
    bool m_isAbortRequested;
    std::launch m_policy;
};

} // namespace Task
