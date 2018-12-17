#include <boost/test/unit_test.hpp>
#include "AudioSourceStorage.h"
#include "Helper.h"

BOOST_AUTO_TEST_CASE(audio_source_storage_positive_cases) {
    app::model::AudioSourceStorage storage1;
    app::model::AudioSourceStorage storage2;

    auto temp_file_name = random_file_path();
    auto random_reference = random_int();

    BOOST_CHECK(storage1.initialize(temp_file_name));
    BOOST_CHECK(storage2.initialize(temp_file_name));
    BOOST_CHECK(storage1.save(random_reference));

    int exist = 0;
    BOOST_CHECK(storage2.load(exist));
    BOOST_CHECK_EQUAL(exist, random_reference);

    BOOST_CHECK(boost::filesystem::remove(temp_file_name));
}