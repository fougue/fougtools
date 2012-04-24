#include "qstring_tools.h"

namespace qttools {

bool QStringLocalEqualTo::operator()(const QString &lhs, const QString &rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) == 0;
}

bool QStringLocalNotEqualTo::operator()(const QString &lhs, const QString &rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) != 0;
}

bool QStringLocalAwareLess::operator()(const QString& lhs, const QString& rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) < 0;
}

bool QStringLocalAwareLessEqual::operator()(const QString &lhs, const QString &rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) <= 0;
}

bool QStringLocalAwareGreater::operator()(const QString &lhs, const QString &rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) > 0;
}

bool QStringLocalAwareGreaterEqual::operator()(const QString &lhs, const QString &rhs) const
{
  return QString::localeAwareCompare(lhs, rhs) >= 0;
}

} // namespace qttools

#include <QtCore/QHash>
std::size_t hash_value(QString const& str)
{
  return qHash(str);
}
