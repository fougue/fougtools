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

#ifdef GEOM_PROJECT_POINT_ON_TRIANGLE_H

namespace geom
{
  template<typename _PNT_VEC_TRAITS_>
  const std::pair<typename _PNT_VEC_TRAITS_::Pnt_t, bool>
  projectPointOnTriangle(
    const typename _PNT_VEC_TRAITS_::Pnt_t& p,
    const typename _PNT_VEC_TRAITS_::Pnt_t& v0,
    const typename _PNT_VEC_TRAITS_::Pnt_t& v1,
    const typename _PNT_VEC_TRAITS_::Pnt_t& v2)
  {
    typedef typename _PNT_VEC_TRAITS_::Pnt_t Pnt_t;
    typedef typename _PNT_VEC_TRAITS_::Vec_t Vec_t;

    const Vec_t e0(_PNT_VEC_TRAITS_::vector(v0, v1));
    const Vec_t e1(_PNT_VEC_TRAITS_::vector(v0, v2));
    const Vec_t D(_PNT_VEC_TRAITS_::vector(p, v0));

    const double a = _PNT_VEC_TRAITS_::dot(e0, e0);
    const double b = _PNT_VEC_TRAITS_::dot(e0, e1);
    const double c = _PNT_VEC_TRAITS_::dot(e1, e1);
    const double d = _PNT_VEC_TRAITS_::dot(e0, D);
    const double e = _PNT_VEC_TRAITS_::dot(e1, D);

    const double det = a * c - b * b;
    double s = b * e - c * d;
    double t = b * d - a * e;

    int region = 0;
    if (s + t <= det)
    {
      if (s < 0.)
      {
        if (t < 0.)
          region = 4;
        else
          region = 3;
      }
      else if (t < 0.)
        region = 5;
    }
    else
    {
      if (s < 0.)
        region = 2;
      else if (t < 0.)
        region = 6;
      else
        region = 1;
    }

    switch (region)
    {
      case 0 :
      {
        const double invDet = 1. / det;
        s *= invDet;
        t *= invDet; break;
      }
      case 1 :
      {
        const double numer = c + e - b - d;
        if (numer <= 0.)
          s = 0.;
        else
        {
          const double denom = a - 2. * b + c;
          s = (numer >= denom ? 1. : numer / denom);
        }
        t = 1. - s; break;
      }
      case 2 :
        s = 0.;
        t = 1.; break;
      case 3 :
        s = 0.;
        t = (e >= 0. ? 0. : (-e >= c ? 1. : -e / c)); break;
      case 4:
        s = 0.;
        t = 0.; break;
      case 5 :
        t = 0.;
        s = (d >= 0. ? 0. : (-d >= a ? 1. : -d / a)); break;
      case 6 :
        s = 1.;
        t = 0.; break;
    }

    return std::make_pair(_PNT_VEC_TRAITS_::translate(
                          _PNT_VEC_TRAITS_::translate(v0, e0 * s), e1 * t),
                          region == 0);
  }

  /*! \struct project_point_on_triangle
   *  \brief  Wraps projectPointOnTriangle() as a unary functor.
   */

  //! Construct the functor : \p v0 , \p v1 , \p v2 are the vertices of the
  //! triangle to project points to.
  template<typename _PNT_VEC_TRAITS_>
  project_point_on_triangle<_PNT_VEC_TRAITS_>::project_point_on_triangle(
          const typename _PNT_VEC_TRAITS_::Pnt_t& v0,
          const typename _PNT_VEC_TRAITS_::Pnt_t& v1,
          const typename _PNT_VEC_TRAITS_::Pnt_t& v2) :
    _v0(v0), _v1(v1), _v2(v2)
  {
  }

  template<typename _PNT_VEC_TRAITS_>
  const std::pair<typename _PNT_VEC_TRAITS_::Pnt_t, bool>
  project_point_on_triangle<_PNT_VEC_TRAITS_>::operator()(
    const typename _PNT_VEC_TRAITS_::Pnt_t pnt)
  {
    return projectPointOnTriangle<_PNT_VEC_TRAITS_>(
                 pnt, this->_v0, this->_v1, this->_v2);
  }

} // namespace geom

#endif // GEOM_PROJECT_POINT_ON_TRIANGLE_H
