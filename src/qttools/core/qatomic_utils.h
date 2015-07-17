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

#include "core.h"

#include <QtCore/QAtomicPointer>
class QAtomicInt;

namespace qtcore {

class QTTOOLS_CORE_EXPORT QAtomicUtils
{
public:
    // QAtomicInt
    static int loadRelaxed(const QAtomicInt& atomInt);

    static void storeRelaxed(QAtomicInt* atomInt, int newVal);
    static void storeRelease(QAtomicInt* atomInt, int newVal);

    // QAtomicPointer
    template<typename T>  static T* loadRelaxed(const QAtomicPointer<T>& atomPtr);

    template<typename T>  static void storeRelaxed(QAtomicPointer<T>* atomPtr, T* newPtr);
    template<typename T>  static void storeRelease(QAtomicPointer<T>* atomPtr, T* newPtr);
};



// --
// -- Implementation
// --

template<typename T>  T* QAtomicUtils::loadRelaxed(const QAtomicPointer<T>& atomPtr)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    return atomPtr.load();
#else
    return atomPtr;
#endif
}

template<typename T>  void QAtomicUtils::storeRelaxed(QAtomicPointer<T>* atomPtr, T* newPtr)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    atomPtr->store(newPtr);
#else
    atomPtr->fetchAndStoreRelaxed(newPtr);
#endif
}

template<typename T>  void QAtomicUtils::storeRelease(QAtomicPointer<T>* atomPtr, T* newPtr)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    atomPtr->storeRelease(newPtr);
#else
    atomPtr->fetchAndStoreRelease(newPtr);
#endif
}

} // namespace qtcore
