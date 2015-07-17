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
#include <QtCore/QVariant>

namespace qtcore {

/*! \brief Provides a collection of tools around QVariant
 *  \headerfile qvariant_utils.h <qttools/core/qvariant_utils.h>
 *  \ingroup qttools_core
 *
 */
class QTTOOLS_CORE_EXPORT QVariantUtils
{
public:
    template<typename T, template <typename> class CONTAINER>
    static CONTAINER<T> toTypedContainer(const CONTAINER<QVariant>& variants);

    template<typename T, template <typename> class CONTAINER>
    static CONTAINER<QVariant> toContainerOfVariants(const CONTAINER<T>& typeds);
};

} // namespace qtcore

// --
// -- Implementation
// --

#include <algorithm>
#include <functional>
#include <iterator>

namespace qtcore {

/*! \brief Converts a container of QVariant to a container of typed data (\c T)
 *
 * The container can be of any type (std::list<>, QVector<>, ...) the only
 * restriction is that it must satisfy the concept of Back Insertion Sequence
 * (see http://www.sgi.com/tech/stl/BackInsertionSequence.html)
 *
 * \sa toContainerOfVariants()
 */
template<typename T, template <typename> class CONTAINER>
CONTAINER<T> QVariantUtils::toTypedContainer(const CONTAINER<QVariant>& variants)
{
    CONTAINER<T> typeds;
    std::transform(variants.begin(), variants.end(),
                   std::back_inserter(typeds),
                   std::ptr_fun(&qVariantValue<T>));
    return typeds;
}

/*! \brief Converts a container of typed data (\c T) to a container of QVariant
 *
 * The container can be of any type (std::list<>, QVector<>, ...) the only
 * restriction is that it must satisfy the concept of Back Insertion Sequence
 * (see http://www.sgi.com/tech/stl/BackInsertionSequence.html)
 *
 * \sa toTypedContainer()
 */
template<typename T, template <typename> class CONTAINER>
CONTAINER<QVariant> QVariantUtils::toContainerOfVariants(const CONTAINER<T>& typeds)
{
    CONTAINER<QVariant> variants;
    std::transform(typeds.begin(), typeds.end(),
                   std::back_inserter(variants),
                   std::ptr_fun(&QVariant::fromValue<T>));
    return variants;
}

} // namespace qtcore

#endif // QTTOOLS_QVARIANT_TOOLS_H
