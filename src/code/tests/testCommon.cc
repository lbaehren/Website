
#include <Common.h>

//_______________________________________________________________________________
//                                                                 test_operators

/*!
  \brief Test overloading of output operator for std::vector<T>, etc.

  \param length -- Length of the vector, set, etc. used for testing operator 
         overloading.
*/
int test_operators (unsigned int const &length=10)
{
  std::cout << "\n[TestCommon::test_operators]\n" << std::endl;

  /* Test overloading for std::vector<T> */
  {
    std::vector<int> vectInt (length,1);
    std::vector<short> vectShort (length,2);
    std::vector<long> vectLong (length,3);
    std::vector<float> vectFloat (length,4.0);
    std::vector<double> vectDouble (length,5.0);
    std::vector<std::string> vectString (length,"a");

    std::cout << "-- vectInt    = " << vectInt    << std::endl;
    std::cout << "-- vectShort  = " << vectShort  << std::endl;
    std::cout << "-- vectLong   = " << vectLong   << std::endl;
    std::cout << "-- vectFloat  = " << vectFloat  << std::endl;
    std::cout << "-- vectDouble = " << vectDouble << std::endl;
    std::cout << "-- vectString = " << vectString << std::endl;
  }

  return 0;
}

//_______________________________________________________________________________
//                                                                           main

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
