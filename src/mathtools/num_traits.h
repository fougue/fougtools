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

#ifndef MATHTOOLS_NUM_TRAITS_H
#define MATHTOOLS_NUM_TRAITS_H

namespace math {

/*! \brief Type traits on real numerical types (float, double, ...)
 *  \headerfile norm.h <mathtools/norm.h>
 *  \ingroup mathtools
 */
template<typename T>
struct BaseNumTraits
{
  typedef T Real;

  static Real precision() { return Real(0); }
};

template<typename T>
struct NumTraits : public BaseNumTraits<T>
{ };

/*! \brief Specialization for float
 *  \headerfile norm.h <mathtools/norm.h>
 *  \ingroup mathtools
 */
template<> struct NumTraits<float> : public BaseNumTraits<float>
{
  static Real precision() { return 1e-5f; }
};

/*! \brief Specialization for double
 *  \headerfile norm.h <mathtools/norm.h>
 *  \ingroup mathtools
 */
template<> struct NumTraits<double> : public BaseNumTraits<double>
{
  static Real precision() { return 1e-12; }
};

/*! \brief Specialization for long double
 *  \headerfile norm.h <mathtools/norm.h>
 *  \ingroup mathtools
 */
template<> struct NumTraits<long double> : public BaseNumTraits<long double>
{
  static Real precision() { return 1e-15l; }
};

} // namespace math

#endif // MATHTOOLS_NUM_TRAITS_H
