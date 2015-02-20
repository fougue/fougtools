#pragma once

#include <QtCore/QVariant>
#include <QtCore/QString>

#include <unordered_map>

namespace Task {

class Runnable;

/*! \brief Provides feedback on the progress of an executing operation (Runnable)
 */
class Progress
{
public:
    ~Progress();

    int value() const;
    void setValue(int pct);

    const QString& step() const;
    void setStep(const QString& title);

    void outputMessage(const QString& msg);

    QVariant data(int key) const;
    void setData(int key, const QVariant& value);

    bool isAbortRequested() const;

private:
    Progress(Runnable* runnable);

    friend class Manager;
    friend class Runnable;

    Runnable* m_runnable;
    std::unordered_map<int, QVariant> m_dataHash;
    int m_value;
    QString m_step;
};

} // namespace Task
