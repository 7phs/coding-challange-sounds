#pragma once

#include <string>

namespace app {
    namespace model {
        class BingBangBoom {
        public:
            // Initialize the object with a new srcReference.
            virtual void initialize(const int srcReference) = 0;

            // Calculate & return the expected state according to the excercise.
            virtual std::string calculate() const = 0;

            // Store a given srcReference for later usage
            // Return true when this succeeded, false if it failed.
            virtual bool save(const std::string &filePath) const = 0;

            // Load a stored srcReference from a file.
            // Return true when this succeeded, false if it failed
            virtual bool load(const std::string &filePath) = 0;
        };
    }
}
