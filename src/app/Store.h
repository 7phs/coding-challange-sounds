#pragma once

#include <iostream>
#include "../command/Arguments.h"

namespace app {
    // A command - storing a source reference
    class CommandStore : public command::Command {
    public:
        CommandStore() = default;

        virtual ~CommandStore() = default;

        // A description of a command showed in help command
        virtual std::string description() const {
            return "Store a given srcReference for later usage";
        }

        // An operator stored a srcReference
        virtual void operator()(const command::Params& params) const {
            int srcReference = params.get<int>(command::ParamSrcReference, app::model::validate_src_reference);
            std::string filePath = params.get<std::string>(command::ParamFile);

            auto guard = model::BingBangBoomFactory::create();
            auto v = static_cast<model::BingBangBoom*>(guard.get());

            v->initialize(srcReference);

            if (v->save(filePath)) {
                std::cout << "Success" << std::endl;
            } else {
                std::cerr << "Error: failed to store a source references" << std::endl;
            }
        }
    };
}
