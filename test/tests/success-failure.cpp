/* Unit testing for outcomes
(C) 2017 Niall Douglas <http://www.nedproductions.biz/> (149 commits)


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
    (See accompanying file Licence.txt or copy at
          http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../../include/outcome/success_failure.hpp"
#include "quickcpplib/include/boost/test/unit_test.hpp"

BOOST_OUTCOME_AUTO_TEST_CASE(works / success - failure, "Tests that the success and failure type sugars work as intended")
{
  using namespace OUTCOME_V2_NAMESPACE;
#ifdef __cpp_deduction_guides
  std::cout << "__cpp_deduction_guides = 1" << std::endl;
#endif
  {
    auto a = success(5);
    auto b = success();
    auto c = success("hello");
    static_assert(std::is_same<decltype(a), success_type<int>>::value, "");
    static_assert(std::is_same<decltype(b), success_type<void>>::value, "");
    static_assert(std::is_same<decltype(c), success_type<const char *>>::value, "");
    static_assert(std::is_same<decltype(a._value), int>::value, "");
    // static_assert(std::is_same<decltype(b.value), int>::value, "");
    static_assert(std::is_same<decltype(c._value), const char *>::value, "");
  }
  {
    auto e = std::make_exception_ptr(5);
    auto a = failure(5);
    auto b = failure(5, e);
    auto c = failure(5, 5);
    static_assert(std::is_same<decltype(a), failure_type<int, void>>::value, "");
    static_assert(std::is_same<decltype(b), failure_type<int, std::exception_ptr>>::value, "");
    static_assert(std::is_same<decltype(c), failure_type<int, int>>::value, "");
    static_assert(std::is_same<decltype(a._error), int>::value, "");
    static_assert(std::is_same<decltype(b._error), int>::value, "");
    static_assert(std::is_same<decltype(b._exception), std::exception_ptr>::value, "");
    static_assert(std::is_same<decltype(c._error), int>::value, "");
    static_assert(std::is_same<decltype(c._exception), int>::value, "");
  }
}
