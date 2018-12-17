#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "command/Arguments.h"
#include "app/Calc.h"
#include "app/Store.h"
#include "app/Load.h"

int main(int argc, char **argv) {
    return command::Arguments(boost::filesystem::basename(argv[0]))
            .add_command("calc", std::make_unique<app::CommandCalc>())
            .add_command("store", std::make_unique<app::CommandStore>())
            .add_command("load", std::make_unique<app::CommandLoad>())
            .run(argc, argv);
}