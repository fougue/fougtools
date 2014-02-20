#ifndef BITS_MATH_UTILS_HELPERS_H
# define BITS_MATH_UTILS_HELPERS_H

// Requires at least Visual C++ 2010
//# include <cstdint>

namespace math {

//! \cond INCLUDE_INTERNAL
namespace __impl
{
template<typename T>
class TypeTraits
{
public:
  typedef int IntegralType_t;

  static bool isNativeIntegralType()
  {
    return true;
  }

  static IntegralType_t twoComplementValue()
  {
    // Default value, always wrong (just to make the compiler happy)
    return 0x1;
  }
}; // class TypeTraits
/*
template<>
class TypeTraits<float>
{
public:
  typedef std::int32_t IntegralType_t;

  static IntegralType_t twoComplementValue()
  {
    return 0x80000000;
  }

  static IntegralType_t maxDistIntsUpperBound()
  {
    return 4 * 1024 * 1024;
  }

  static bool isNativeIntegralType()
  {
    return false;
  }
}; // class TypeTraits<float>

template<>
class TypeTraits<double>
{
public:
  typedef std::int64_t IntegralType_t;

  static IntegralType_t twoComplementValue()
  {
    return INT64_C(0x8000000000000000);
  }

  static IntegralType_t maxDistIntsUpperBound()
  {
    return 4 * 1024 * 1024;
  }

  static bool isNativeIntegralType()
  {
    return false;
  }
}; // class TypeTraits<double>
*/
} // namespace __impl
//! \endcond
} // namespace math

#endif // BITS_MATH_UTILS_HELPERS_H
