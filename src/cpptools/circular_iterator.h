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

namespace cpp {

/*! \brief Iterator next to \p iCurr bounded between \p iBegin and \p iEnd
 *
 *  \retval ++iCurr when \p iCurr \c != \p iEnd
 *  \retval iBegin when \p iCurr \c == \p iEnd
 *
 *  \ingroup cpptools
 */
template<typename BI_ITERATOR>
BI_ITERATOR circularNext(BI_ITERATOR iBegin, BI_ITERATOR iEnd, BI_ITERATOR iCurr)
{
    if (iCurr == --iEnd)
        return iBegin;
    return ++iCurr;
}

/*! \brief Iterator prior to \p iCurr bounded between \p iBegin and \p iEnd
 *
 *  \retval --iCurr when \p iCurr \c != \p iBegin
 *  \retval iEnd when \p iCurr \c == \p iBegin
 *
 *  \ingroup cpptools
 */
template<typename BI_ITERATOR>
BI_ITERATOR circularPrior(BI_ITERATOR iBegin, BI_ITERATOR iEnd, BI_ITERATOR iCurr)
{
    if (iCurr == iBegin)
        return --iEnd;
    return --iCurr;
}

/*! \brief Iterator advanced by \p d bounded between \p iBegin and \p iEnd
 *
 *  \todo Improve performance (direct calculation instead of a \c for loop)
 *
 *  \ingroup cpptools
 */
template<typename BI_ITERATOR, typename DISTANCE>
BI_ITERATOR circularAdvance(BI_ITERATOR iBegin, BI_ITERATOR iEnd,
                            BI_ITERATOR iCurr, DISTANCE d)
{
    const DISTANCE absD = d < 0 ? -d : d;
    for (DISTANCE i = 0; i < absD; ++i) {
        iCurr = d < 0 ? circularPrior(iBegin, iEnd, iCurr) :
                        circularNext(iBegin, iEnd, iCurr);
    }
    return iCurr;
}

} // namespace cpp
