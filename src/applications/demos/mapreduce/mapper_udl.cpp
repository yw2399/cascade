#include <cascade/user_defined_logic_interface.hpp>
#include <iostream>
#include <memory>
#include "mapreduce_interface.hpp"

namespace derecho{
namespace cascade{
#define MY_UUID     "9d2363ce-cd7f-11eb-8433-0242ac110002"
#define MY_DESC     "Cascade MapReducer's Mapper Implementation"

std::string get_uuid() {
    return MY_UUID;
}

std::string get_description() {
    return MY_DESC;
}

class MapperOCDPO: public OffCriticalDataPathObserver {
    virtual void operator() (const std::string& key_string,
                             const uint32_t prefix_length,
                             persistent::version_t version,
                             const mutils::ByteRepresentable* const value_ptr,
                             const std::unordered_map<std::string,bool>& outputs,
                             ICascadeContext* ctxt,
                             uint32_t worker_id) override {
        mapper<std::string,ObjectWithStringKey,std::string,ObjectWithStringKey>(
                key_string,
                *dynamic_cast<const ObjectWithStringKey*>(value_ptr),
                [&outputs, ctxt](const std::string& key, const ObjectWithStringKey& value){
                    auto* typed_ctxt = dynamic_cast<CascadeContext<VolatileCascadeStoreWithStringKey,
                                                                   PersistentCascadeStoreWithStringKey,
                                                                   TriggerCascadeNoStoreWithStringKey>*>(ctxt);
                    for (auto iter = outputs.begin(); iter != outputs.end(); ++iter) {
                        //TODO: Think about the key/value pair. The key can only be decided here. What the value type
                        //should be? ByteRepresentable???
                    }
                });
    }

    static std::shared_ptr<OffCriticalDataPathObserver> ocdpo_ptr;
public:
    static void initialize() {
        if (!ocdpo_ptr) {
            ocdpo_ptr = std::make_shared<MapperOCDPO>();
        }
    }

    static auto get() {
        return ocdpo_ptr;
    }
};

std::shared_ptr<OffCriticalDataPathObserver> MapperOCDPO::ocdpo_ptr;

void initialize(ICascadeContext*) {
    MapperOCDPO::initialize();
}

std::shared_ptr<OffCriticalDataPathObserver> get_observer() {
    return MapperOCDPO::get();
}

void release(ICascadeContext*) {
    // nothing to release
    return;
}

}//namespace cascade
}//namespace derecho
