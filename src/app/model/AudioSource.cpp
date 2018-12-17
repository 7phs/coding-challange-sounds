#include <boost/test/unit_test.hpp>
#include "AudioSource.h"

BOOST_AUTO_TEST_CASE( audio_source_positive_cases )
{
    app::model::AudioSource v;

    v.initialize(3);
    BOOST_CHECK_EQUAL(v.get_reference(), 3);
    BOOST_CHECK_EQUAL(v.play(), app::model::Bing);

    v.initialize(4);
    BOOST_CHECK_EQUAL(v.play(), app::model::Bang);

    v.initialize(12);
    BOOST_CHECK_EQUAL(v.play(), app::model::Boom);

    v.initialize(37);
    BOOST_CHECK_EQUAL(v.play(), app::model::Meh);
}