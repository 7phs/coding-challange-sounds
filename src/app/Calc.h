#pragma once

#include <iostream>
#include "../command/Arguments.h"
#include "../command/Params.h"
#include "model/Factory.h"
#include "model/SourceReference.h"

namespace app {
    // A command - immediately calculating the sound output
    class CommandCalc : public command::Command {
    public:
        CommandCalc() = default;

        virtual ~CommandCalc() = default;

        // A description of a command showed in help command
        std::string description() const {
            return "Immediately calculate and show the sound output for a given input srcReference";
        }

        // An operator calculated and show the sound output
        void operator()(const command::Params& params) const {
            int srcReference = params.get<int>(command::ParamSrcReference, app::model::validate_src_reference);

            auto guard = model::BingBangBoomFactory::create();
            auto v = static_cast<model::BingBangBoom*>(guard.get());

            v->initialize(srcReference);

            std::cout << v->calculate() << std::endl;
        }
    };
}
