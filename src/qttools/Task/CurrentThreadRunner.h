#pragma once

#include "BaseRunner.h"

namespace Task {

/*! \brief Task runner executing in the current thread context
 */
class CurrentThreadRunner : public BaseRunner
{
public:
    CurrentThreadRunner(const Manager* mgr);

    bool isAbortRequested() override;
    void requestAbort() override;

    void launch() override;

private:
    bool m_isAbortRequested;
};

} // namespace Task
