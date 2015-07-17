/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#pragma once

#include <QtCore/QObject>

namespace qtcore {

/*! Wraps (adapts) any class object into a QObject instance
 *
 *  This class is useful to let Qt handle the lifecycle of a non QObject : wrap
 *  an instance to a QObject and then let its parent takes ownership
 *
 * \headerfile qobject_wrap.h <qttools/core/qobject_wrap.h>
 * \ingroup qttools_core
 */
template<typename T>
class QObjectWrap : public QObject
{
public:
    QObjectWrap(const T& value, QObject* parent = nullptr);
    QObjectWrap(T&& value, QObject* parent = nullptr);

    const T& value() const;
    void setValue(const T& val);
    void setValue(T&& val);

private:
    T m_value;
};

/*! Create a QObjectWrap<T> owning \p value
 *
 *  This is equivalent to qtcore::QObjectWrap<T>(\p value, \p parent), but
 *  usually requires less typing
 *  \relates QObjectWrap
 */
template<typename T>
QObjectWrap<T>* wrapAsQObject(const T& value, QObject* parent = nullptr);


// --
// -- Implementation
// --

template<typename T>
QObjectWrap<T>::QObjectWrap(const T& value, QObject* parent)
    : QObject(parent),
      m_value(value)
{ }

template<typename T>
QObjectWrap<T>::QObjectWrap(T&& value, QObject* parent)
    : QObject(parent),
      m_value(value)
{ }

template<typename T>
const T& QObjectWrap<T>::value() const
{ return m_value; }

template<typename T>
void QObjectWrap<T>::setValue(const T& val)
{ m_value = val; }

template<typename T>
void QObjectWrap<T>::setValue(T&& val)
{ m_value = val; }

template<typename T>
QObjectWrap<T>* wrapAsQObject(const T& value, QObject* parent)
{
    return new QObjectWrap<T>(value, parent);
}

} // namespace qtcore
