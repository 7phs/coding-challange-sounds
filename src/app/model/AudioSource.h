#pragma once

#include <string>

namespace app {
    namespace model {
        const std::string Bing = "Bing";
        const std::string Bang = "Bang";
        const std::string Boom = "Boom";
        const std::string Meh = "Meh";

        const int OrionNone = 0x0;
        const int OrionA = 0x1;
        const int OrionB = 0x2;

        // An audio source storing a link between devices
        class AudioSource {
        public:
            AudioSource() {}

            ~AudioSource() = default;

            void initialize(int srcReference) {
                srcReference_ = srcReference;

                linked_ = AudioSource::make_link(srcReference);
            }

            const int get_reference() const {
                return srcReference_;
            }

            // "Playing" a sound depends on linking status
            const std::string &play() const {
                switch (linked_) {
                    case OrionA:
                        return Bing;
                    case OrionB:
                        return Bang;
                    case OrionA | OrionB:
                        return Boom;
                    default:
                        return Meh;
                }
            }

        protected:
            // Making ling by a coding challenge requirements
            static int make_link(int srcReference) {
                if (srcReference % 3 == 0 || srcReference % 4 == 0) {
                    if (srcReference % 3 == 0 && srcReference % 4 == 0) {
                        return OrionA | OrionB;
                    } else if (srcReference % 3 == 0) {
                        return OrionA;
                    } else if (srcReference % 4 == 0) {
                        return OrionB;
                    }
                }

                return OrionNone;
            }

        private:
            int linked_ = OrionNone;

            int srcReference_ = 0;
        };
    }
}