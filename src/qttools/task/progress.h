#pragma once

#include <QtCore/QVariant>
#include <QtCore/QString>

#include <unordered_map>

namespace qttask {

class BaseRunner;

/*! \brief Provides feedback on the progress of an executing operation
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
    friend class Manager;
    friend class BaseRunner;

    Progress(BaseRunner* runner);

    BaseRunner* m_runner;
    std::unordered_map<int, QVariant> m_dataHash;
    int m_value;
    QString m_step;
};

} // namespace qttask
