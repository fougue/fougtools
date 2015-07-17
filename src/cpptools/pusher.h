/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
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

#include <iterator>

namespace cpp {

/*! Push iterator
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
 *  \param x Container on which the iterator will push new elements.
 *         \n Container should be a container class with member push() defined.
 *
 *  \ingroup cpptools
 */
template<typename CONTAINER>
push_iterator<CONTAINER> pusher(CONTAINER& x)
{
    return push_iterator<CONTAINER>(x);
}

} // namespace cpp
