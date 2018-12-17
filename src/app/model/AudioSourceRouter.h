#pragma once

#include <string>
#include "AudioSource.h"
#include "Executor.h"

namespace app {
    namespace model {
        // A router of an adio sources.
        // Now it is a simple implemenation for an architecture building
        class AudioSourceRouter : public Router {
        public:
            AudioSourceRouter() = default;
            virtual ~AudioSourceRouter() = default;

            // Routing a source reference to an audio source
            std::unique_ptr<AudioSource> route(const int srcReference) {
                auto v = std::make_unique<AudioSource>();

                v->initialize(srcReference);

                return v;
            };
        };
    }
}