#pragma once

namespace app {
    namespace model {
        // An implemetation of requirements for a valid range of srcReference
        bool validate_src_reference(int &srcReference) {
            return srcReference >= 0 && srcReference <= 100;
        }
    }
}