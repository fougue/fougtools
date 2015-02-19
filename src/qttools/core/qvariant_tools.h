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

#ifndef QTTOOLS_QVARIANT_TOOLS_H
#define QTTOOLS_QVARIANT_TOOLS_H

#include "core.h"
#include <QtCore/QVariant>

namespace qttools {

/*! \brief Provides a collection of tools around QVariant
 *  \headerfile qvariant_tools.h <qttools/core/qvariant_tools.h>
 *  \ingroup qttools_core
 *
 */
class QTTOOLS_CORE_EXPORT QVariantTools
{
public:
    template<typename T, template <typename> class CONTAINER>
    static CONTAINER<T> toTypedContainer(const CONTAINER<QVariant>& variants);

    template<typename T, template <typename> class CONTAINER>
    static CONTAINER<QVariant> toContainerOfVariants(const CONTAINER<T>& typeds);
};

} // namespace qttools

// --
// -- Implementation
// --

#include <algorithm>
#include <functional>
#include <iterator>

namespace qttools {

/*! \brief Converts a container of QVariant to a container of typed data (\c T)
 *
 * The container can be of any type (std::list<>, QVector<>, ...) the only restriction is that it
 * must satisfy the concept of Back Insertion Sequence (see http://www.sgi.com/tech/stl/BackInsertionSequence.html)
 *
 * \sa toContainerOfVariants()
 */
template<typename T, template <typename> class CONTAINER>
CONTAINER<T> QVariantTools::toTypedContainer(const CONTAINER<QVariant>& variants)
{
    CONTAINER<T> typeds;
    std::transform(variants.begin(), variants.end(),
                   std::back_inserter(typeds),
                   std::ptr_fun(&qVariantValue<T>));
    return typeds;
}

/*! \brief Converts a container of typed data (\c T) to a container of QVariant
 *
 * The container can be of any type (std::list<>, QVector<>, ...) the only restriction is that it
 * must satisfy the concept of Back Insertion Sequence (see http://www.sgi.com/tech/stl/BackInsertionSequence.html)
 *
 * \sa toTypedContainer()
 */
template<typename T, template <typename> class CONTAINER>
CONTAINER<QVariant> QVariantTools::toContainerOfVariants(const CONTAINER<T>& typeds)
{
    CONTAINER<QVariant> variants;
    std::transform(typeds.begin(), typeds.end(),
                   std::back_inserter(variants),
                   std::ptr_fun(&QVariant::fromValue<T>));
    return variants;
}

} // namespace qttools

#endif // QTTOOLS_QVARIANT_TOOLS_H
