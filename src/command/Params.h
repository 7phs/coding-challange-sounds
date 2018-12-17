#pragma once

#include <string>
#include <map>
#include <boost/program_options.hpp>

namespace command {
    // A collection of command line parameters which supports validation of a parameters
    class Params {
    public:
        Params() = default;

        ~Params() = default;

        // Binding a param for a parameter's option
        std::string *bind(const std::string &name) {
            auto it = params_.find(name);
            if (it == params_.end()) {
                params_[name] = "";
            }

            return &params_[name];
        }

        // Get a value of a parameter without validation, if a param not found raise an exception
        template<typename T>
        T get(const std::string &name) const noexcept(false) {
            return this->get<T>(name, Params::without_validation<T>);
        }

        // Get a value of a parameter with validation, if a param not found or invalid raise an exception
        template<typename T>
        T get(const std::string &name, std::function<bool(T &)> validator) const noexcept(false) {
            auto it = params_.find(name);
            if (it == params_.end() || std::get<1>(*it).empty()) {
                throw boost::program_options::required_option(name);
            }

            std::string value = std::get<1>(*it);
            T v{};

            cast(name, value, v);
            if (!validator(v)) {
                invalid_param(name);
            }

            return v;
        }

    protected:
        // Dumb validator
        template<typename T>
        static bool without_validation(T &) {
            return true;
        }

        // Casting a parameter's value to an int, raise an exception if a string is invalid
        void cast(const std::string &name, std::string &value, int &casted) const noexcept(false) {
            try {
                casted = std::stoi(value);
            } catch (std::exception &) {
                invalid_param(name);
            }
        }

        // Just a copy value - it is a string to string cast
        void cast(const std::string &name, std::string &value, std::string &casted) const noexcept(false) {
            casted = value;
        }

        // Raise an exception for an invalid param
        static void invalid_param(const std::string &name) noexcept(false) {
            throw boost::program_options::error("invalid " + name);
        }

    private:
        std::map<std::string, std::string> params_;
    };
}