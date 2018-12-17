#include <boost/test/unit_test.hpp>
#include "SourceReference.h"

BOOST_AUTO_TEST_CASE(source_reference_positive_cases) {
    int ref;

    ref = 0;
    BOOST_CHECK(app::model::validate_src_reference(ref));
    ref = 34;
    BOOST_CHECK(app::model::validate_src_reference(ref));
    ref = 134;
    BOOST_CHECK(!app::model::validate_src_reference(ref));
    ref = -1;
    BOOST_CHECK(!app::model::validate_src_reference(ref));
}