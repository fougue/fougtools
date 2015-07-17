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

#include <tuple>

namespace cpp {

/*! Apply function \p f to each element in tuple \p t */
template<typename TUPLE, typename FUNC>
void tuple_for_each(TUPLE& t, FUNC f);

/*! Apply function \p f to each element in tuple \p t starting from end */
template<typename TUPLE, typename FUNC>
void tuple_reversed_for_each(TUPLE& t, FUNC f);

// --
// -- Implementation
// --

namespace internal {

template<std::size_t N, std::size_t I, typename TUPLE, typename FUNC>
struct impl_tuple_for_each
{
    static void call(TUPLE& t, FUNC f)
    {
        f(std::get<N - I>(t));
        impl_tuple_for_each<N, I - 1, TUPLE, FUNC>::call(t, f);
    }
};

template<std::size_t N, typename TUPLE, typename FUNC>
struct impl_tuple_for_each<N, 1, TUPLE, FUNC>
{
    static void call(TUPLE& t, FUNC f)
    {
        f(std::get<N - 1>(t));
    }
};

// Empty tuple
template<typename TUPLE, typename FUNC>
struct impl_tuple_for_each<0, 0, TUPLE, FUNC>
{
    static void call(TUPLE&, FUNC)
    { }
};

template<std::size_t N, std::size_t I, typename TUPLE, typename FUNC>
struct impl_tuple_reversed_for_each
{
    static void call(TUPLE& t, FUNC f)
    {
        f(std::get<N - I - 1>(t));
        impl_tuple_reversed_for_each<N, I + 1, TUPLE, FUNC>::call(t, f);
    }
};

template<std::size_t N, typename TUPLE, typename FUNC>
struct impl_tuple_reversed_for_each<N, N, TUPLE, FUNC>
{
    static void call(TUPLE&, FUNC)
    { }
};

// Empty tuple
template<typename TUPLE, typename FUNC>
struct impl_tuple_reversed_for_each<0, 0, TUPLE, FUNC>
{
    static void call(TUPLE&, FUNC)
    { }
};

} // namespace internal

template<typename TUPLE, typename FUNC>
void tuple_for_each(TUPLE& t, FUNC f)
{
    internal::impl_tuple_for_each<
            std::tuple_size<TUPLE>::value,
            std::tuple_size<TUPLE>::value,
            TUPLE,
            FUNC>
            ::call(t, f);
}

template<typename TUPLE, typename FUNC>
void tuple_reversed_for_each(TUPLE& t, FUNC f)
{
    internal::impl_tuple_reversed_for_each<
            std::tuple_size<TUPLE>::value, 0, TUPLE, FUNC>
            ::call(t, f);
}

} // namespace cpp
