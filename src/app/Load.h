#pragma once

#include <iostream>
#include "../command/Arguments.h"

namespace app {
    // A command - loading stored a source reference and calculating sound out
    class CommandLoad : public command::Command {
    public:
        CommandLoad() = default;

        virtual ~CommandLoad() = default;

        // A description of a command showed in help command
        virtual std::string description() const {
            return "Load a srcReference that was previously stored, calculate and show the sound output";
        }

        // An operator loaded a srcReference and calc a sound output
        virtual void operator()(const command::Params& params) const {
            std::string filePath = params.get<std::string>(command::ParamFile);

            auto guard = model::BingBangBoomFactory::create();
            auto v = static_cast<model::BingBangBoom*>(guard.get());

            if (!v->load(filePath)) {
                std::cerr << "Error: failed to load a source references" << std::endl;
                return;
            }

            std::cout << v->calculate() << std::endl;
        }
    };
}
