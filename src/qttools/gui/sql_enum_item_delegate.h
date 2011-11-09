/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#ifndef QTTOOLS_SQL_ENUM_ITEM_DELEGATE_H
#define QTTOOLS_SQL_ENUM_ITEM_DELEGATE_H

#include <QtGui/QStyledItemDelegate>
#include <QtGui/QComboBox>
#include "qttools/sql/cpp_sql_enum_map.h"

namespace qttools {

// -- class SqlEnumItemDelegate
template<typename CPP_SQL_ENUM_MAP>
class SqlEnumItemDelegate : public QStyledItemDelegate
{
public:
  SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>(const CPP_SQL_ENUM_MAP& enumMap, QObject* parent = 0);

  QString displayText(const QVariant& value, const QLocale& locale) const;
  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option, const QModelIndex& index) const;
  void setEditorData(QWidget* editor, const QModelIndex& index) const;
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

private:
  const CPP_SQL_ENUM_MAP& m_enumMap;
};


// -- class ReadOnlySqlEnumItemDelegate
template<typename CPP_SQL_ENUM_MAP>
class ReadOnlySqlEnumItemDelegate : public SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>
{
public:
  ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>(const CPP_SQL_ENUM_MAP& enumMap,
                                                QObject* parent = 0);

  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

template<typename CPP_SQL_ENUM_MAP>
SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>* makeSqlEnumItemDelegate(
    const CPP_SQL_ENUM_MAP& enumMap, QObject* parent = 0);

template<typename CPP_SQL_ENUM_MAP>
ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>*
makeReadOnlySqlEnumItemDelegate(const CPP_SQL_ENUM_MAP& enumMap, QObject* parent = 0);



// --
// -- Implementation (SqlEnumItemDelegate)
// --

template<typename CPP_SQL_ENUM_MAP>
SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::SqlEnumItemDelegate(const CPP_SQL_ENUM_MAP& enumMap,
                                                           QObject* parent)
  : QStyledItemDelegate(parent),
    m_enumMap(enumMap)
{
}

template<typename CPP_SQL_ENUM_MAP>
QString SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::displayText(const QVariant& value,
                                                           const QLocale& /*locale*/) const
{
  return value.toString();
}

template<typename CPP_SQL_ENUM_MAP>
QWidget* SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::createEditor(QWidget* parent,
                                                             const QStyleOptionViewItem& /*option*/,
                                                             const QModelIndex& /*index*/) const
{
  QComboBox* editor = new QComboBox(parent);
  for (int i = 0; i < m_enumMap.size(); ++i)
    editor->addItem(m_enumMap.sqlValue(m_enumMap.cppValue(i)));
  return editor;
}

template<typename CPP_SQL_ENUM_MAP>
void SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::setEditorData(QWidget* editor,
                                                          const QModelIndex& index) const
{
  QComboBox* stateEditor = qobject_cast<QComboBox*>(editor);
  const QString sqlValue = index.data().toString();
  if (stateEditor != 0)
    stateEditor->setCurrentIndex(m_enumMap.index(m_enumMap.cppValue(sqlValue)));
}

template<typename CPP_SQL_ENUM_MAP>
void SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::setModelData(QWidget* editor,
                                                         QAbstractItemModel* model,
                                                         const QModelIndex& index) const
{
  QComboBox* stateEditor = qobject_cast<QComboBox*>(editor);
  if (stateEditor != 0) {
    const int currEditorId = stateEditor->currentIndex();
    model->setData(index, m_enumMap.sqlValue(m_enumMap.cppValue(currEditorId)));
  }
}

template<typename CPP_SQL_ENUM_MAP>
SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>* makeSqlEnumItemDelegate(const CPP_SQL_ENUM_MAP& enumMap,
                                                               QObject* parent)
{
  return new SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>(enumMap, parent);
}


// --
// -- Implementation (ReadOnlySqlEnumItemDelegate)
// --

template<typename CPP_SQL_ENUM_MAP>
ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::ReadOnlySqlEnumItemDelegate(const CPP_SQL_ENUM_MAP& enumMap,
                                                                           QObject* parent)
  : SqlEnumItemDelegate<CPP_SQL_ENUM_MAP>(enumMap, parent)
{
}

template<typename CPP_SQL_ENUM_MAP>
QWidget* ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>::createEditor(QWidget* /*parent*/,
                                                                     const QStyleOptionViewItem& /*option*/,
                                                                     const QModelIndex& /*index*/) const
{
  return 0;
}

template<typename CPP_SQL_ENUM_MAP>
ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>*
makeReadOnlySqlEnumItemDelegate(const CPP_SQL_ENUM_MAP& enumMap, QObject* parent)
{
  return new ReadOnlySqlEnumItemDelegate<CPP_SQL_ENUM_MAP>(enumMap, parent);
}
} // namespace qttools

#endif // QTTOOLS_SQL_ENUM_ITEM_DELEGATE_H
