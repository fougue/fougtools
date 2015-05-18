/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
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
****************************************************************************/

#pragma once

#include <cstddef>
#include <cstdint>

namespace cpp {

/*! \brief 32/64b FNV-1a string hashing (Fowler-Noll-Vo hash)
 *
 *  See http://www.isthe.com/chongo/tech/comp/fnv
 *
 *  \ingroup cpptools
 */
template<unsigned SIZE = sizeof(std::size_t)*8> // Target arch bit size by default
struct hash_fnv_1a
{
    static_assert(SIZE == 32 || SIZE == 64, "Bit size must be 32 or 64");

private:
    template<unsigned N>
    struct helper
    { };

    template<>
    struct helper<32>
    {
        typedef std::uint32_t uint_type;
        static const uint_type offsetBasis = 2166136261U;
        static const uint_type prime = 16777619U;
    };

    template<>
    struct helper<64>
    {
        typedef std::uint64_t uint_type;
        static const uint_type offsetBasis = 14695981039346656037ULL;
        static const uint_type prime = 1099511628211ULL;
    };

    typedef helper<SIZE> helper_t;

public:
    typedef typename helper_t::uint_type uint_type;

    //! Hash on byte sequence \p byteSeq of length \p len
    template<typename BYTE>
    uint_type operator()(const BYTE* byteSeq, std::size_t len) const
    {
        auto hash = helper_t::offsetBasis;
        for (std::size_t i = 0; i < len; ++i)
            hashStep(hash, *(byteSeq + i));
        return hash;
    }

    //! Hash on byte sequence \p byteSeq which must be null terminated
    template<typename BYTE>
    uint_type operator()(const BYTE* byteSeq) const
    {
        auto hash = helper_t::offsetBasis;
        for (; *byteSeq != 0; ++byteSeq)
            hashStep(hash, *byteSeq);
        return hash;
    }

    //! Hash on byte sequence delimited by begin/end iterators
    template<typename ITERATOR>
    uint_type operator()(ITERATOR begin, ITERATOR end) const
    {
        auto hash = helper_t::offsetBasis;
        for (; begin != end; ++begin)
            hashStep(hash, *begin);
        return hash;
    }

private:
    template<typename BYTE>
    static inline void hashStep(uint_type& hash, BYTE byte)
    {
        static_assert(sizeof(BYTE) == 1, "valid BYTE type");
        hash ^= static_cast<uint_type>(byte); // XOR on the low order byte of hash
        hash *= helper_t::prime;
    }
};

typedef hash_fnv_1a<32> hash32_fnv_1a;
typedef hash_fnv_1a<64> hash64_fnv_1a;

} // namespace cpp
