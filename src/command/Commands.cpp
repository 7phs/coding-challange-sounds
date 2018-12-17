#include <string>
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "Arguments.h"

namespace test {
    class TestCommand : public command::Command {
    public:
        TestCommand(std::string &&description, command::cmd_func &&callback) : description_(description),
                                                                               callback_(callback) {}

        virtual ~TestCommand() = default;

        // A description of a command showed in help command
        std::string description() const {
            return description_;
        }

        // An operator calculated and show the sound output
        void operator()(const command::Params &params) const {
            callback_(params);
        }

    private:
        std::string description_;
        command::cmd_func callback_;
    };
}

BOOST_AUTO_TEST_CASE(command_arguments_positive_cases) {
    int value = 0;

    auto commands = command::CommandArguments();
    commands.add("one", std::make_unique<test::TestCommand>("1", [&](const command::Params &) {
        value = 1;
    }));
    commands.add("three", std::make_unique<test::TestCommand>("3", [&](const command::Params &) {
        value = 3;
    }));

    BOOST_CHECK_EQUAL(commands.string(), "\n'one' - 1;\n'three' - 3;\n");

    auto cmd = commands.bind_command_name();

    *cmd = "one";
    BOOST_CHECK(commands.execute());
    BOOST_CHECK_EQUAL(value, 1);

    *cmd = "three";
    BOOST_CHECK(commands.execute());
    BOOST_CHECK_EQUAL(value, 3);

    *cmd = "unknown";
    BOOST_CHECK(!commands.execute());
}