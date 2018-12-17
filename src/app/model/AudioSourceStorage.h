#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Executor.h"

namespace app {
    namespace model {
        class AudioSourceStorage : public Storage {
        public:
            AudioSourceStorage() = default;

            virtual ~AudioSourceStorage() = default;

            bool initialize(const std::string &filePath) {
                filePath_ = filePath;

                return true;
            }

            // Storing a source reference into a file which name used in initialisation
            bool save(const int srcReference) const {
                try {
                    std::ofstream file;

                    file.open(filePath_, std::ios::out | std::ios::binary);

                    file << srcReference;

                    file.close();
                } catch (std::exception &e) {
                    return false;
                }

                return true;
            }

            // Storing a source reference from a file which name used in initialisation
            bool load(int &srcReference) const {
                try {
                    std::ifstream file;

                    file.open(filePath_, std::ios::in | std::ios::binary);

                    file >> srcReference;

                    file.close();
                } catch (const std::exception& e) {
                    return false;
                }

                return true;
            }

        private:
            std::string filePath_;
        };
    }
}