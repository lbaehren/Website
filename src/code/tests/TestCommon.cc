#include <Common.h>

/*!
  \brief Test overloading of output operator for std::vector<T>, etc.
*/
int test_operators (unsigned int const &length=10)
{
  std::cout << "\n[TestCommon::test_operators]\n" << std::endl;

  std::vector<int> vectInt (length);
  std::vector<short> vectShort (length);
  std::vector<long> vectLong (length);
  std::vector<float> vectFloat (length);
  std::vector<double> vectDouble (length);
  
  std::cout << "-- vectInt    = " << vectInt    << std::endl;
  std::cout << "-- vectShort  = " << vectShort  << std::endl;
  std::cout << "-- vectLong   = " << vectLong   << std::endl;
  std::cout << "-- vectFloat  = " << vectFloat  << std::endl;
  std::cout << "-- vectDouble = " << vectDouble << std::endl;
}

/*!
  \file TestCommon.cc
  \ingroup Blog
  \brief A collection of tests for the collection of common functions
  \author Lars Baehren
*/
int main ()
{
  int status = 0;

  status += test_operators();

  return 0;
}
