/****************************************************************************
**
**  FougTools
**  Copyright FougSys (19 Feb. 2015)
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

#pragma once

#include <iterator>

namespace cpp {

/*! \brief Push iterator
 *
 *  A push_iterator is a special type of output iterator designed to allow
 *  algorithms that usually overwrite elements (such as copy) to instead push
 *  new elements automatically into the container.
 *
 *  The container needs to have a push() member function (such as the standard
 *  containers queue and stack).
 *
 *  Using the assignment operator on the returned iterator (either dereferenced
 *  or not), causes the container to expand by one element, which is
 *  initialized to the value assigned.
 *
 *  The returned iterator supports all other typical operations of output
 *  iterators but have no effect: all values assigned are pushed into the
 *  container.
 *
 *  \ingroup cpptools
 */
template <typename CONTAINER>
class push_iterator :
        public std::iterator<std::output_iterator_tag, void, void, void, void>
{
protected:
    CONTAINER* m_container;

public:
    typedef CONTAINER CONTAINER_type;

    explicit push_iterator(CONTAINER& x)
        : m_container(&x)
    {}

    push_iterator<CONTAINER>& operator=(const typename CONTAINER::value_type& value)
    {
        m_container->push(value);
        return *this;
    }

    push_iterator<CONTAINER>& operator=(typename CONTAINER::value_type&& value)
    {
        m_container->push(std::move(value));
        return *this;
    }

    push_iterator<CONTAINER>& operator*()
    { return *this; }

    push_iterator<CONTAINER>& operator++()
    { return *this; }

    push_iterator<CONTAINER> operator++(int)
    { return *this; }
};

/*! \brief Constructs a push_iterator that pushes new elements into \p x.
 *
 *  \param x Container on which the iterator will push new elements. \n Container should be a
 *           container class with member push() defined.
 *
 *  \ingroup cpptools
 */
template<typename CONTAINER>
push_iterator<CONTAINER> pusher(CONTAINER& x)
{
    return push_iterator<CONTAINER>(x);
}

} // namespace cpp
