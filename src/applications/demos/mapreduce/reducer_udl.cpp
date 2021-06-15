#include <cascade/user_defined_logic_interface.hpp>
#include <iostream>
#include <memory>
#include "mapreduce_interface.hpp"

namespace derecho{
namespace cascade{
#define MY_UUID     "d81f3768-cd8f-11eb-9811-0242ac110002"
#define MY_DESC     "Cascade MapReduce's Reducer Implementation"

std::string get_uuid() {
    return MY_UUID;
}

std::string get_description() {
    return MY_DESC;
}

class ReducerOCDPO: public OffCriticalDataPathObserver {
    virtual void operator() (const std::string& key_string,
                             const uint32_t prefix_length,
                             persistent::version_t version,
                             const mutils::ByteRepresentable* const value_ptr,
                             const std::unordered_map<std::string,bool>& outputs,
                             ICascadeContext* ctxt,
                             uint32_t worker_id) override {}

    static std::shared_ptr<OffCriticalDataPathObserver> ocdpo_ptr;
public:
    static void initialize() {
        if (!ocdpo_ptr) {
            ocdpo_ptr = std::make_shared<ReducerOCDPO>();
        }
    }

    static auto get() {
        return ocdpo_ptr;
    }
};

std::shared_ptr<OffCriticalDataPathObserver> ReducerOCDPO::ocdpo_ptr;

void initialize(ICascadeContext*) {
    ReducerOCDPO::initialize();
}

std::shared_ptr<OffCriticalDataPathObserver> get_observer() {
    return ReducerOCDPO::get();
}

void release(ICascadeContext*) {
    // nothing to release
    return;
}

}//namespace cascade
}//namespace derecho
