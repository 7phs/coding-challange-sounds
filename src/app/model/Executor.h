#pragma once

#include <memory>
#include "BingBangBoom.h"
#include "AudioSource.h"

namespace app {
    namespace model {
        // An interface of router of audio sources
        class Router {
        public:
            virtual ~Router() {};

            // Initialize the object with a new srcReference.
            virtual std::unique_ptr<AudioSource> route(const int srcReference) = 0;
        };

        // An interface of a storage of a source reference. Should be refactoring for general cases
        class Storage {
        public:
            virtual ~Storage() {};

            // Initialize the object with a new srcReference.
            virtual bool initialize(const std::string &filePath) = 0;

            // Initialize the object with a new srcReference.
            virtual bool save(const int srcReference) const = 0;

            // Initialize the object with a new srcReference.
            virtual bool load(int &srcReference) const = 0;
        };

        class BingBangBoomExecutor : public BingBangBoom {
        public:
            virtual ~BingBangBoomExecutor() {};
        };

        // An aggregator of a two features (storing/loading and execution) for implementing interface requirements
        class Executor : public BingBangBoomExecutor {
        public:
            Executor(std::unique_ptr<Router>&& router, std::unique_ptr<Storage>&& storage) : router_(std::move(router)),
                                                                                         storage_(std::move(storage)) {}

            virtual ~Executor() = default;

            void initialize(const int srcReference) {
                source_ = router_->route(srcReference);
            }

            // Calculate & return the expected state according to the excercise.
            std::string calculate() const {
                return static_cast<std::string>(source_->play());
            }

            // Store a given srcReference for later usage
            // Return true when this succeeded, false if it failed.
            bool save(const std::string &filePath) const {
                if (!storage_->initialize(filePath)) {
                    return false;
                }

                const int srcReference = source_->get_reference();

                return storage_->save(srcReference);
            }

            // Load a stored srcReference from a file.
            // Return true when this succeeded, false if it failed
            bool load(const std::string &filePath) {
                int srcReference = 0;

                if (!storage_->initialize(filePath) || !storage_->load(srcReference)) {
                    return false;
                }

                source_ = router_->route(srcReference);

                return true;
            }

        private:
            std::unique_ptr<Router> router_;
            std::unique_ptr<Storage> storage_;
            std::unique_ptr<AudioSource> source_;
        };
    }
}