#include <boost/test/unit_test.hpp>
#include "AudioSourceRouter.h"

BOOST_AUTO_TEST_CASE( audio_source_router_positive_cases )
{
    app::model::AudioSourceRouter router;

    auto v = router.route(3);
    BOOST_CHECK_EQUAL(v->play(), app::model::Bing);

    v = router.route(4);
    BOOST_CHECK_EQUAL(v->play(), app::model::Bang);

    v = router.route(12);
    BOOST_CHECK_EQUAL(v->play(), app::model::Boom);

    v = router.route(37);
    BOOST_CHECK_EQUAL(v->play(), app::model::Meh);
}