//------------------------------------------------------------------------------
// Copyright (c) 2013, Lars Baehren <lbaehren@gmail.com>
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#ifndef DAL_IO_IOSTREAM_H
#define DAL_IO_IOSTREAM_H

#include <iostream>
#include <string>
#include <set>
#include <valarray>
#include <vector>

namespace dal {

    namespace io {

        /*!
         * @file swir/io/iostream,h
         * @ingroup tropomi_swir_cpp
         * @brief Overloading of output operators.
         *
         * While the output operator `<<` is available for atomic datatypes - such as
         * _int_, _float_, etc. - the same unfortunately is not true for containers such
         * as `vector<T>`, `set<T>`, etc. In order to enable the same type of syntax,
         * e.g.
         * @code
         * std::cout << "-- vector<bool>   = " << vec_bool   << std::endl;
         * @endcode
         * we hereby provide overloading of the output operator.
         *
         * @note Operator overloading is **not** to take place within the confines of
         * a namespace, in order to be generally applicable.
         */

        //______________________________________________________________________
        //                                                                  show

        /*!
          @brief Write elements of an array/vector/set to an output stream

          @param os    -- Stream to which the output is written.
          @param start -- Iterator pointing to the first element.
          @param end   -- Iterator pointing to the position after the last element.
        */
        template <typename T>
            std::ostream& show (std::ostream& os,
                                T start,
                                T end)
            {
                T it;

                os << "[";
                for (it=start; it!=end; ++it) {
                    os << " " << *it;
                }
                os << " ]";

                return os;
            }

        //______________________________________________________________________
        //                                                                  show

        /*!
         * @brief Write elements of an array to an output stream
         * @param os    -- Stream to which the output is written
         * @param arr   -- Pointer to the array with the data to be displayed
         * @param nelem -- The number of elements stored within the array
         */
        template <typename T, typename S>
            void show (std::ostream& os,
                       T *arr,
                       S const &nelem)
        {
            os << "[";

            for (S n(0); n<nelem; ++n) {
                os << " " << arr[n];
            }

            os << " ]";
        }

        //______________________________________________________________________
        //                                                            operator<<

        /*!
         * @brief Overloading of output operator to display std::valarray<T>
         * @param os  -- Output stream to which the result will be written to
         * @param vec -- The valarray to be displayed
         */
        template <typename T>
            std::ostream& operator<< (std::ostream &os,
                                      const std::valarray<T> &vec)
            {
                os << "[";

                for (size_t n=0; n<vec.size(); ++n) {
                    os << " " <<  vec[n];
                }
                os << " ]";

                return os;
            }

        //______________________________________________________________________
        //                                                            operator<<

        /*!
         * @brief Overloading of output operator to display std::vector<T>
         * @param os  -- Output stream to which the result will be written to
         * @param vec -- The vector to be displayed
         */
        template <typename T>
            std::ostream& operator<< (std::ostream &os,
                                      const std::vector<T> &vec)
            {
                return show (os, vec.begin(), vec.end());
            }

        //______________________________________________________________________
        //                                                            operator<<

        /*!
         * @brief Overloading of output operator to display std::set<T>
         * @param os  -- Output stream to which the result will be written to
         * @param s   -- The set to be displayed
         */
        template <typename T>
            std::ostream& operator<< (std::ostream &os,
                                      const std::set<T> &s)
            {
                return show (os, s.begin(), s.end());
            }

    };  //  namespace io - END

};  //  namespace dal - END

#endif
