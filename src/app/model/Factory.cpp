#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "Factory.h"
#include "Helper.h"

BOOST_AUTO_TEST_CASE(factory_positive_cases) {
    auto executor1 = app::model::BingBangBoomFactory::create();
    auto executor2 = app::model::BingBangBoomFactory::create();

    auto temp_file_name = random_file_path();

    executor1->initialize(3);
    BOOST_CHECK_EQUAL(executor1->calculate(), app::model::Bing);
    BOOST_CHECK(executor1->save(temp_file_name));
    BOOST_CHECK(executor2->load(temp_file_name));
    BOOST_CHECK_EQUAL(executor2->calculate(), app::model::Bing);

    executor1->initialize(4);
    BOOST_CHECK_EQUAL(executor1->calculate(), app::model::Bang);
    BOOST_CHECK(executor1->save(temp_file_name));
    BOOST_CHECK(executor2->load(temp_file_name));
    BOOST_CHECK_EQUAL(executor2->calculate(), app::model::Bang);

    executor1->initialize(12);
    BOOST_CHECK_EQUAL(executor1->calculate(), app::model::Boom);
    BOOST_CHECK(executor1->save(temp_file_name));
    BOOST_CHECK(executor2->load(temp_file_name));
    BOOST_CHECK_EQUAL(executor2->calculate(), app::model::Boom);

    executor1->initialize(37);
    BOOST_CHECK_EQUAL(executor1->calculate(), app::model::Meh);
    BOOST_CHECK(executor1->save(temp_file_name));
    BOOST_CHECK(executor2->load(temp_file_name));
    BOOST_CHECK_EQUAL(executor2->calculate(), app::model::Meh);

    BOOST_CHECK(boost::filesystem::remove(temp_file_name));
}