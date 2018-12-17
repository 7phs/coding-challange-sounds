#include <boost/test/unit_test.hpp>
#include "Params.h"

BOOST_AUTO_TEST_CASE(params_positive_cases) {
    command::Params params;

    std::string name_str = "str";
    std::string name_int = "int";

    auto param1 = params.bind(name_str);
    auto param2 = params.bind(name_int);

    *param1 = "value 2";
    *param2 = "27";

    try {
        BOOST_CHECK_EQUAL(params.get<std::string>(name_str), "value 2");
    } catch (std::exception &e) {
        BOOST_FAIL("invalid str param");
    }

    try {
        BOOST_CHECK_EQUAL(params.get<int>(name_int, [](int &v) -> bool {
            return v > 0;
        }), 27);
    } catch (std::exception &e) {
        BOOST_FAIL(std::string("invalid str param: ") + e.what());
    }

    try {
        params.get<int>(name_int, [](int &v) -> bool {
            return v > 100;
        });
        BOOST_FAIL("invalid int validation");
    } catch (std::exception &e) {
    }
}
