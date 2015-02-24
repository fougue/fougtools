#include "StdAsyncRunner.h"

namespace Task {

StdAsyncRunner::StdAsyncRunner(Runnable *runner, std::launch policy)
    : BaseRunner(runner),
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
    std::async(m_policy, &BaseRunner::execRunnableFunc, this);
}

} // namespace Task
