/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
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
