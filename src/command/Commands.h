#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "Params.h"

namespace command {
    typedef std::function<void(const Params &)> cmd_func;

    // An interface of a command which implementing an action
    // A description use for showing help
    class Command {
    public:
        virtual ~Command() = default;

        // A description of a command showed in help command
        virtual std::string description() const = 0;

        // A coomand action
        virtual void operator()(const Params &params) const = 0;
    };

    typedef std::unique_ptr<Command> cmd_pointer;

    // A collection of a command line parameters for a command and the name of the command
    class CommandArguments {
    public:
        CommandArguments() = default;

        ~CommandArguments() = default;

        // Add the new command for the collection using name of it
        void add(std::string &&name, cmd_pointer &&cmd) {
            commands_.emplace(std::move(name), std::forward<cmd_pointer>(cmd));
        }

        // Binding a name of the command, using for executing one
        std::string *bind_command_name() {
            return &command_name_;
        }

        // Binding a param for a command
        std::string *bind_param(const std::string &name) {
            return params_.bind(name);
        }

        // Executing a command selected by the command's name. Return false if not found a command by name
        bool execute() const {
            auto it = commands_.find(command_name_);

            if (it == end(commands_)) {
                return false;
            }

            (*std::get<cmd_pointer>(*it))(params_);

            return true;
        }

        // Stringify command's collection
        std::string string() const {
            std::stringstream s;

            auto descriptions = command_descriptions();

            copy(begin(descriptions), end(descriptions), std::ostream_iterator<std::string>(s, ";\n"));

            return "\n" + s.str();
        }

    protected:
        // Transform a map of commands to a vector of it's description
        std::vector<std::string> command_descriptions() const {
            std::vector<std::string> v;

            std::transform(begin(commands_), end(commands_), std::back_inserter(v), [](auto &r) {
                return "'" + std::get<0>(r) + "' - " + std::get<cmd_pointer>(r)->description();
            });

            return v;
        }

    private:
        std::map<std::string, cmd_pointer> commands_;

        std::string command_name_;

        Params params_;
    };
}