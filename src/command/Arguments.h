#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <boost/program_options.hpp>
#include "Commands.h"

namespace command {
    static std::string const ParamFile {"file"};
    static std::string const ParamSrcReference {"srcReference"};

    // A helper to configure a command line options for implementing sub-commands
    class Arguments {
    public:
        Arguments(const std::string &app_name) : app_name_(app_name), description_("Options") {};

        ~Arguments() = default;

        // Add a command with name for executing it
        Arguments &add_command(std::string &&name, cmd_pointer &&cmd) {
            commands_.add(std::move(name), std::forward<cmd_pointer>(cmd));

            return *this;
        }

        // Parsing a command line and choosing a command to execute
        int run(int argc, char **argv) {
            finalize_();

            boost::program_options::variables_map vm;

            try {
                auto options = boost::program_options::command_line_parser(argc, argv)
                        .options(description_)
                        .positional(positions_)
                        .run();

                boost::program_options::store(options, vm);

                boost::program_options::notify(vm);

                if (vm.count("execute")) {
                    if (!commands_.execute()) {
                        show_help();
                    }
                } else if (vm.count("help")) {
                    show_help();
                } else {
                    show_help();
                }
            }
            catch (boost::program_options::required_option &e) {
                std::cerr << "Error: " << e.what() << std::endl;

                show_help();

                return 1;
            }
            catch (boost::program_options::error &e) {
                std::cerr << "Error: " << e.what() << std::endl;

                show_help();

                return 1;
            }

            return 0;
        }

        // Show a help string
        void show_help() const {
            std::cout << "Usage: " << app_name_ << " [options] [command] " << std::endl << std::endl;
            std::cout << description_ << std::endl;
        }

    protected:
        // Register a program options after added all of commands
        void finalize_() {
            description_.add_options()
                    ("help", "show help message")
                    ("execute",
                     boost::program_options::value<std::string>(commands_.bind_command_name()),
                     std::string("execute a command: " + commands_.string()).c_str())
                    (ParamFile.c_str(),
                     boost::program_options::value<std::string>(commands_.bind_param(ParamFile)),
                     "a file name to store or to load stored reference")
                    (ParamSrcReference.c_str(),
                     boost::program_options::value<std::string>(commands_.bind_param(ParamSrcReference)),
                     "the audio source link to an Orion system");

            positions_.add("execute", 1);
        }

    protected:
        boost::program_options::options_description description_;
        boost::program_options::positional_options_description positions_;

        std::string app_name_;
        CommandArguments commands_;
    };
}
