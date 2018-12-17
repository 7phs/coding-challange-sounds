#pragma once

#include <memory>
#include "BingBangBoom.h"
#include "Executor.h"
#include "AudioSourceRouter.h"
#include "AudioSourceStorage.h"

namespace app {
    namespace model {
        // A factory for a BingBangBoom instance
        // Now it is a simple implementation, just for architecture's building
        class BingBangBoomFactory {
        public:
            static std::unique_ptr<BingBangBoomExecutor> create() {
                return std::make_unique<Executor>(
                        std::make_unique<AudioSourceRouter>(),
                        std::make_unique<AudioSourceStorage>()
                );
            }
        };
    }
}