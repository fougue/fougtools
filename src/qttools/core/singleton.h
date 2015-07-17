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

#include <QtCore/QAtomicPointer>
#include <QtCore/QMutex>

namespace qtcore {

template<typename T>
class Singleton
{
public:
    static T* instance();
    static void release();

private:
    static QAtomicPointer<T> m_instance;
    static QMutex m_mutex;
};

// --
// -- Implementation
// --

template<typename T>
T* Singleton<T>::instance()
{
    if (!m_instance) {
        m_mutex.lock();
        if (!m_instance)
            m_instance = new T;
        m_mutex.unlock();
    }
    return m_instance;
}

template<typename T>
void Singleton<T>::release()
{
    m_mutex.lock();
    if (m_instance)
        delete m_instance;
    m_instance = NULL;
    m_mutex.unlock();
}

} // namespace qtcore

template<typename T>
QAtomicPointer<T> qtcore::Singleton<T>::m_instance;

template<typename T>
QMutex qtcore::Singleton<T>::m_mutex;
