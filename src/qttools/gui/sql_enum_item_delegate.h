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
# define QTTOOLS_SQL_ENUM_ITEM_DELEGATE_H

# include <QtGui/QStyledItemDelegate>
# include <QtGui/QComboBox>
# include "qttools/sql/cpp_sql_enum_map.h"

namespace qttools {

// -- class SqlEnumItemDelegate
template<typename _CPP_SQL_ENUM_MAP_>
class SqlEnumItemDelegate : public QStyledItemDelegate
{
public:
  SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>(const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent = 0);

  QString displayText(const QVariant& value, const QLocale& locale) const;
  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option, const QModelIndex& index) const;
  void setEditorData(QWidget* editor, const QModelIndex& index) const;
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

private:
  const _CPP_SQL_ENUM_MAP_& _enumMap;
};


// -- class ReadOnlySqlEnumItemDelegate
template<typename _CPP_SQL_ENUM_MAP_>
class ReadOnlySqlEnumItemDelegate :
    public SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>
{
public:
  ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>(const _CPP_SQL_ENUM_MAP_& enumMap,
                                                  QObject* parent = 0);

  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

template<typename _CPP_SQL_ENUM_MAP_>
SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>* makeSqlEnumItemDelegate(
    const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent = 0);

template<typename _CPP_SQL_ENUM_MAP_>
ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>*
makeReadOnlySqlEnumItemDelegate(const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent = 0);



// --
// -- Implementation (SqlEnumItemDelegate)
// --

template<typename _CPP_SQL_ENUM_MAP_>
SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::SqlEnumItemDelegate(
    const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent) :
  QStyledItemDelegate(parent),
  _enumMap(enumMap)
{
}

template<typename _CPP_SQL_ENUM_MAP_>
QString SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::displayText(
    const QVariant& value,
    const QLocale& /*locale*/) const
{
  return value.toString();
}

template<typename _CPP_SQL_ENUM_MAP_>
QWidget* SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::createEditor(
    QWidget* parent,
    const QStyleOptionViewItem& /*option*/,
    const QModelIndex& /*index*/) const
{
  QComboBox* editor = new QComboBox(parent);
  for (int i = 0; i < this->_enumMap.size(); ++i)
    editor->addItem(this->_enumMap.sqlValue(this->_enumMap.cppValue(i)));
  return editor;
}

template<typename _CPP_SQL_ENUM_MAP_>
void SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::setEditorData(
    QWidget* editor,
    const QModelIndex& index) const
{
  QComboBox* stateEditor = qobject_cast<QComboBox*>(editor);
  const QString sqlValue = index.data().toString();
  if (stateEditor != 0)
    stateEditor->setCurrentIndex(
          this->_enumMap.index(this->_enumMap.cppValue(sqlValue)));
}

template<typename _CPP_SQL_ENUM_MAP_>
void SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::setModelData(
    QWidget* editor,
    QAbstractItemModel* model,
    const QModelIndex& index) const
{
  QComboBox* stateEditor = qobject_cast<QComboBox*>(editor);
  if (stateEditor != 0)
  {
    const int currEditorId = stateEditor->currentIndex();
    model->setData(index, this->_enumMap.sqlValue(
                     this->_enumMap.cppValue(currEditorId)));
  }
}

template<typename _CPP_SQL_ENUM_MAP_>
SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>* makeSqlEnumItemDelegate(
    const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent)
{
  return new SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>(enumMap, parent);
}


// --
// -- Implementation (ReadOnlySqlEnumItemDelegate)
// --

template<typename _CPP_SQL_ENUM_MAP_>
ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::ReadOnlySqlEnumItemDelegate(
    const _CPP_SQL_ENUM_MAP_& enumMap, QObject* parent) :
  SqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>(enumMap, parent)
{
}

template<typename _CPP_SQL_ENUM_MAP_>
QWidget* ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>::createEditor(
    QWidget* /*parent*/,
    const QStyleOptionViewItem& /*option*/,
    const QModelIndex& /*index*/) const
{
  return 0;
}

template<typename _CPP_SQL_ENUM_MAP_>
ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>*
makeReadOnlySqlEnumItemDelegate(const _CPP_SQL_ENUM_MAP_& enumMap,
                                QObject* parent)
{
  return new ReadOnlySqlEnumItemDelegate<_CPP_SQL_ENUM_MAP_>(enumMap, parent);
}
} // namespace qttools

#endif // QTTOOLS_SQL_ENUM_ITEM_DELEGATE_H
