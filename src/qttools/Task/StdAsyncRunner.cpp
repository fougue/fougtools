#include "StdAsyncRunner.h"

namespace Task {

StdAsyncRunner::StdAsyncRunner(const Manager *mgr, std::launch policy)
    : BaseRunner(mgr),
      m_isAbortRequested(false),
      m_policy(policy)
{ }

bool StdAsyncRunner::isAbortRequested()
{
    return m_isAbortRequested;
}

void StdAsyncRunner::requestAbort()
{
    m_isAbortRequested = true;
}

void StdAsyncRunner::launch()
{
    std::async(m_policy, [=] { this->execRunnableFunc(); } );
}

} // namespace Task
