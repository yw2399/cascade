#include <cascade/object.hpp>
#include <unistd.h>

namespace derecho {
namespace cascade {

uint64_t ObjectWithUInt64Key::IK = INVALID_UINT64_OBJECT_KEY;
ObjectWithUInt64Key ObjectWithUInt64Key::IV;
std::string ObjectWithStringKey::IK;
ObjectWithStringKey ObjectWithStringKey::IV;

/*
 *  IMPORTANT NOTICE of Blob Implementation
 *
 *  Blob is an inner type of ObjectWithXXXKeys class, which is repsonsible for store the objects with various length.
 *  Copy constructor is heavy for large objects. We found that sometimes, the Linux malloc/memcpy behave wiredly if the
 *  memory is not aligned to page boundary. It incurs a lot of page walks (The phenomenon can be reproduced by
 *  'wired_reconnecting_external_client' branch with a setup of 1 VCSS node, 1MB message, and 1 external client). To
 *  solve this issue, we only use full pages for Blob data buffer. To further improve the performance, we should use
 *  hugepages.
 */
static const std::size_t page_size = sysconf(_SC_PAGESIZE);
#define PAGE_ALIGNED_NEW(x) (new char[((x)+page_size-1)/page_size*page_size])

Blob::Blob(const char* const b, const decltype(size) s) :
    bytes(nullptr), size(0), is_emplaced(false) {
    if(s > 0) {
        char* t_bytes = PAGE_ALIGNED_NEW(s);
        if (b != nullptr) {
            memcpy(t_bytes, b, s);
        } else {
            bzero(t_bytes, s);
        }
        bytes = t_bytes;
        size = s;
    }
}

Blob::Blob(const char* b, const decltype(size) s, bool emplaced) :
    bytes(b), size(s), is_emplaced(emplaced) {
    if ( (size>0) && (is_emplaced==false)) {
        char* t_bytes = PAGE_ALIGNED_NEW(s);
        if (b != nullptr) {
            memcpy(t_bytes, b, s);
        } else {
            bzero(t_bytes, s);
        }
        bytes = t_bytes;
    }
    // exclude illegal argument combinations like (0x982374,0,false)
    if (size == 0) {
        bytes = nullptr;
    }
}

Blob::Blob(const Blob& other) :
    bytes(nullptr), size(0) {
    if(other.size > 0) {
        char* t_bytes = PAGE_ALIGNED_NEW(other.size);
        memcpy(t_bytes, other.bytes, other.size);
        bytes = t_bytes;
        size = other.size;
    }
}

Blob::Blob(Blob&& other) : 
    bytes(other.bytes), size(other.size) {
    other.bytes = nullptr;
    other.size = 0;
}

Blob::Blob() : bytes(nullptr), size(0) {}

Blob::~Blob() {
    if(bytes && ! is_emplaced) {
        delete [] bytes;
    }
}

Blob& Blob::operator=(Blob&& other) {
    const char* swp_bytes = other.bytes;
    std::size_t swp_size = other.size;
    other.bytes = bytes;
    other.size = size;
    bytes = swp_bytes;
    size = swp_size;
    return *this;
}

Blob& Blob::operator=(const Blob& other) {
    if(bytes != nullptr) {
        delete bytes;
    }
    size = other.size;
    if(size > 0) {
        char* t_bytes = PAGE_ALIGNED_NEW(size);
        memcpy(t_bytes, other.bytes, size);
        bytes = t_bytes;
    } else {
        bytes = nullptr;
    }
    return *this;
}

std::size_t Blob::to_bytes(char* v) const {
    ((std::size_t*)(v))[0] = size;
    if(size > 0) {
        memcpy(v + sizeof(size), bytes, size);
    }
    return size + sizeof(size);
}

std::size_t Blob::bytes_size() const {
    return size + sizeof(size);
}

void Blob::post_object(const std::function<void(char const* const, std::size_t)>& f) const {
    f((char*)&size, sizeof(size));
    f(bytes, size);
}

mutils::context_ptr<Blob> Blob::from_bytes_noalloc(mutils::DeserializationManager* ctx, const char* const v) {
    return mutils::context_ptr<Blob>{new Blob(const_cast<char*>(v) + sizeof(std::size_t), ((std::size_t*)(v))[0], true)};
}

mutils::context_ptr<Blob> Blob::from_bytes_noalloc_const(mutils::DeserializationManager* ctx, const char* const v) {
    return mutils::context_ptr<Blob>{new Blob(const_cast<char*>(v) + sizeof(std::size_t), ((std::size_t*)(v))[0], true)};
}

std::unique_ptr<Blob> Blob::from_bytes(mutils::DeserializationManager*, const char* const v) {
    return std::make_unique<Blob>(v + sizeof(std::size_t), ((std::size_t*)(v))[0]);
}

/** ObjectWithStringKey Implementation **/

/*
bool ObjectWithUInt64Key::operator==(const ObjectWithUInt64Key& other) {
    return (this->key == other.key) && (this->version == other.version);
}
*/

bool ObjectWithUInt64Key::is_valid() const {
    return (key != INVALID_UINT64_OBJECT_KEY);
}

// constructor 0 : copy constructor
ObjectWithUInt64Key::ObjectWithUInt64Key(const uint64_t _key,
                                         const Blob& _blob) : 
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key(_key),
    blob(_blob) {}

// constructor 0.5 : copy constructor
ObjectWithUInt64Key::ObjectWithUInt64Key(const persistent::version_t _version,
                                         const uint64_t _timestamp_us,
                                         const persistent::version_t _previous_version,
                                         const persistent::version_t _previous_version_by_key,
                                         const uint64_t _key,
                                         const Blob& _blob,
                                         bool  emplaced) :
    version(_version),
    timestamp_us(_timestamp_us),
    previous_version(_previous_version),
    previous_version_by_key(_previous_version_by_key),
    key(_key), 
    blob(_blob.bytes,_blob.size,emplaced) {}

// constructor 1 : copy consotructor
ObjectWithUInt64Key::ObjectWithUInt64Key(const uint64_t _key,
                                         const char* const _b,
                                         const std::size_t _s) :
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key(_key),
    blob(_b, _s) {}

// constructor 1.5 : copy constructor
ObjectWithUInt64Key::ObjectWithUInt64Key(const persistent::version_t _version,
                                         const uint64_t _timestamp_us,
                                         const persistent::version_t _previous_version,
                                         const persistent::version_t _previous_version_by_key,
                                         const uint64_t _key,
                                         const char* const _b,
                                         const std::size_t _s) :
    version(_version),
    timestamp_us(_timestamp_us),
    previous_version(_previous_version),
    previous_version_by_key(_previous_version_by_key),
    key(_key),
    blob(_b, _s) {}

// constructor 2 : move constructor
ObjectWithUInt64Key::ObjectWithUInt64Key(ObjectWithUInt64Key&& other) :
    version(other.version),
    timestamp_us(other.timestamp_us),
    previous_version(other.previous_version),
    previous_version_by_key(other.previous_version_by_key),
    key(other.key),
    blob(std::move(other.blob)) {}

// constructor 3 : copy constructor
ObjectWithUInt64Key::ObjectWithUInt64Key(const ObjectWithUInt64Key& other) :
    version(other.version),
    timestamp_us(other.timestamp_us),
    previous_version(other.previous_version),
    previous_version_by_key(other.previous_version_by_key),
    key(other.key),
    blob(other.blob) {}

// constructor 4 : default invalid constructor
ObjectWithUInt64Key::ObjectWithUInt64Key() :
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key(INVALID_UINT64_OBJECT_KEY) {}

const uint64_t& ObjectWithUInt64Key::get_key_ref() const {
    return this->key;
}

bool ObjectWithUInt64Key::is_null() const {
    return (this->blob.size == 0);
}

void ObjectWithUInt64Key::set_version(persistent::version_t ver) const {
    this->version = ver;
}

persistent::version_t ObjectWithUInt64Key::get_version() const {
    return this->version;
}

void ObjectWithUInt64Key::set_timestamp(uint64_t ts_us) const {
    this->timestamp_us = ts_us;
}

uint64_t ObjectWithUInt64Key::get_timestamp() const {
    return this->timestamp_us;
}

void ObjectWithUInt64Key::set_previous_version(persistent::version_t prev_ver, persistent::version_t prev_ver_by_key) const {
    this->previous_version = prev_ver;
    this->previous_version_by_key = prev_ver_by_key;
}

bool ObjectWithUInt64Key::verify_previous_version(persistent::version_t prev_ver, persistent::version_t prev_ver_by_key) const {
    // NOTICE: We provide the default behaviour of verify_previous_version as a demonstration. Please change the
    // following code or implementing your own Object Types with a verify_previous_version implementation to customize
    // it. The default behavior is self-explanatory and can be disabled by setting corresponding object previous versions to
    // INVALID_VERSION.

    return ((this->previous_version == persistent::INVALID_VERSION)?true:(this->previous_version >= prev_ver)) &&
           ((this->previous_version_by_key == persistent::INVALID_VERSION)?true:(this->previous_version_by_key >= prev_ver_by_key));
}

template <>
ObjectWithUInt64Key create_null_object_cb<uint64_t,ObjectWithUInt64Key,&ObjectWithUInt64Key::IK,&ObjectWithUInt64Key::IV>(const uint64_t& key) {
    return ObjectWithUInt64Key(key,Blob{});
}

std::size_t ObjectWithUInt64Key::to_bytes(char* v) const {
    std::size_t pos = 0;
    pos+=mutils::to_bytes(version, v + pos);
    pos+=mutils::to_bytes(timestamp_us, v + pos);
    pos+=mutils::to_bytes(previous_version, v + pos);
    pos+=mutils::to_bytes(previous_version_by_key, v + pos);
    pos+=mutils::to_bytes(key, v + pos);
    pos+=mutils::to_bytes(blob, v + pos);
    return pos;
}

std::size_t ObjectWithUInt64Key::bytes_size() const {
    return mutils::bytes_size(version) +
           mutils::bytes_size(timestamp_us) +
           mutils::bytes_size(previous_version) +
           mutils::bytes_size(previous_version_by_key) +
           mutils::bytes_size(key) +
           mutils::bytes_size(blob);
}

void ObjectWithUInt64Key::post_object(const std::function<void(char const* const, std::size_t)>& f) const {
    mutils::post_object(f, version);
    mutils::post_object(f, timestamp_us);
    mutils::post_object(f, previous_version);
    mutils::post_object(f, previous_version_by_key);
    mutils::post_object(f, key);
    mutils::post_object(f, blob);
}

std::unique_ptr<ObjectWithUInt64Key> ObjectWithUInt64Key::from_bytes(mutils::DeserializationManager* dsm, const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // this is a copy constructor
    return std::make_unique<ObjectWithUInt64Key>(
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob);
}

mutils::context_ptr<ObjectWithUInt64Key> ObjectWithUInt64Key::from_bytes_noalloc(
    mutils::DeserializationManager* dsm,
    const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // TODO: solve the memory leak here: ObjectWithString object is malloc-ed
    return mutils::context_ptr<ObjectWithUInt64Key>(
        new ObjectWithUInt64Key{
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob,true});
}

mutils::context_ptr<const ObjectWithUInt64Key> ObjectWithUInt64Key::from_bytes_noalloc_const(
    mutils::DeserializationManager* dsm,
    const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // TODO: solve the memory leak here: ObjectWithString object is malloc-ed
    return mutils::context_ptr<const ObjectWithUInt64Key>(
        new ObjectWithUInt64Key{
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob,true});
}


/** ObjectWithStringKey Implementation **/

/*
bool ObjectWithStringKey::operator==(const ObjectWithStringKey& other) {
    return (this->key == other.key) && (this->version == other.version);
}
*/

bool ObjectWithStringKey::is_valid() const {
    return !key.empty();
}

// constructor 0 : copy constructor
ObjectWithStringKey::ObjectWithStringKey(const std::string& _key, 
                                         const Blob& _blob) : 
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key(_key),
    blob(_blob) {}
// constructor 0.5 : copy constructor
ObjectWithStringKey::ObjectWithStringKey(const persistent::version_t _version,
                                         const uint64_t _timestamp_us,
                                         const persistent::version_t _previous_version,
                                         const persistent::version_t _previous_version_by_key,
                                         const std::string& _key,
                                         const Blob& _blob,
                                         const bool emplaced) :
    version(_version),
    timestamp_us(_timestamp_us),
    previous_version(_previous_version),
    previous_version_by_key(_previous_version_by_key),
    key(_key), 
    blob(_blob.bytes,_blob.size,emplaced) {}

// constructor 1 : copy consotructor
ObjectWithStringKey::ObjectWithStringKey(const std::string& _key,
                                         const char* const _b, 
                                         const std::size_t _s) : 
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key(_key),
    blob(_b, _s) {}
// constructor 1.5 : copy constructor
ObjectWithStringKey::ObjectWithStringKey(const persistent::version_t _version,
                                         const uint64_t _timestamp_us,
                                         const persistent::version_t _previous_version,
                                         const persistent::version_t _previous_version_by_key,
                                         const std::string& _key,
                                         const char* const _b,
                                         const std::size_t _s) : 
    version(_version),
    timestamp_us(_timestamp_us),
    previous_version(_previous_version),
    previous_version_by_key(_previous_version_by_key),
    key(_key), 
    blob(_b, _s) {}

// constructor 2 : move constructor
ObjectWithStringKey::ObjectWithStringKey(ObjectWithStringKey&& other) : 
    version(other.version),
    timestamp_us(other.timestamp_us),
    previous_version(other.previous_version),
    previous_version_by_key(other.previous_version_by_key),
    key(other.key),
    blob(std::move(other.blob)) {}

// constructor 3 : copy constructor
ObjectWithStringKey::ObjectWithStringKey(const ObjectWithStringKey& other) : 
    version(other.version),
    timestamp_us(other.timestamp_us),
    previous_version(other.previous_version),
    previous_version_by_key(other.previous_version_by_key),
    key(other.key),
    blob(other.blob) {}

// constructor 4 : default invalid constructor
ObjectWithStringKey::ObjectWithStringKey() : 
    version(persistent::INVALID_VERSION),
    timestamp_us(0),
    previous_version(INVALID_VERSION),
    previous_version_by_key(INVALID_VERSION),
    key() {}

const std::string& ObjectWithStringKey::get_key_ref() const {
    return this->key;
}

bool ObjectWithStringKey::is_null() const {
    return (this->blob.size == 0);
}

void ObjectWithStringKey::set_version(persistent::version_t ver) const {
    this->version = ver;
}

persistent::version_t ObjectWithStringKey::get_version() const {
    return this->version;
}

void ObjectWithStringKey::set_timestamp(uint64_t ts_us) const {
    this->timestamp_us = ts_us;
}

uint64_t ObjectWithStringKey::get_timestamp() const {
    return this->timestamp_us;
}

void ObjectWithStringKey::set_previous_version(persistent::version_t prev_ver, persistent::version_t prev_ver_by_key) const {
    this->previous_version = prev_ver;
    this->previous_version_by_key = prev_ver_by_key;
}

bool ObjectWithStringKey::verify_previous_version(persistent::version_t prev_ver, persistent::version_t prev_ver_by_key) const {
    // NOTICE: We provide the default behaviour of verify_previous_version as a demonstration. Please change the
    // following code or implementing your own Object Types with a verify_previous_version implementation to customize
    // it. The default behavior is self-explanatory and can be disabled by setting corresponding object previous versions to
    // INVALID_VERSION.

    return ((this->previous_version == persistent::INVALID_VERSION)?true:(this->previous_version >= prev_ver)) &&
           ((this->previous_version_by_key == persistent::INVALID_VERSION)?true:(this->previous_version_by_key >= prev_ver_by_key));
}

template <>
ObjectWithStringKey create_null_object_cb<std::string,ObjectWithStringKey,&ObjectWithStringKey::IK,&ObjectWithStringKey::IV>(const std::string& key) {
    return ObjectWithStringKey(key,Blob{});
}

std::size_t ObjectWithStringKey::to_bytes(char* v) const {
    std::size_t pos = 0;
    pos+=mutils::to_bytes(version, v + pos);
    pos+=mutils::to_bytes(timestamp_us, v + pos);
    pos+=mutils::to_bytes(previous_version, v + pos);
    pos+=mutils::to_bytes(previous_version_by_key, v + pos);
    pos+=mutils::to_bytes(key, v + pos);
    pos+=mutils::to_bytes(blob, v + pos);
    return pos;
}

std::size_t ObjectWithStringKey::bytes_size() const {
    return mutils::bytes_size(version) +
           mutils::bytes_size(timestamp_us) +
           mutils::bytes_size(previous_version) +
           mutils::bytes_size(previous_version_by_key) +
           mutils::bytes_size(key) +
           mutils::bytes_size(blob);
}

void ObjectWithStringKey::post_object(const std::function<void(char const* const, std::size_t)>& f) const {
    mutils::post_object(f, version);
    mutils::post_object(f, timestamp_us);
    mutils::post_object(f, previous_version);
    mutils::post_object(f, previous_version_by_key);
    mutils::post_object(f, key);
    mutils::post_object(f, blob);
}

std::unique_ptr<ObjectWithStringKey> ObjectWithStringKey::from_bytes(mutils::DeserializationManager* dsm, const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<std::string>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // this is a copy constructor
    return std::make_unique<ObjectWithStringKey>(
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob);
}

mutils::context_ptr<ObjectWithStringKey> ObjectWithStringKey::from_bytes_noalloc(
    mutils::DeserializationManager* dsm,
    const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<std::string>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // TODO: solve the memory leak here: ObjectWithString object is malloc-ed
    return mutils::context_ptr<ObjectWithStringKey>(
        new ObjectWithStringKey{
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob,true});
}

mutils::context_ptr<const ObjectWithStringKey> ObjectWithStringKey::from_bytes_noalloc_const(
    mutils::DeserializationManager* dsm,
    const char* const v) {
    size_t pos = 0;
    auto p_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_version);
    auto p_timestamp_us = mutils::from_bytes_noalloc<uint64_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_timestamp_us);
    auto p_previous_version = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_previous_version_by_key = mutils::from_bytes_noalloc<persistent::version_t>(dsm,v + pos);
    pos += mutils::bytes_size(*p_previous_version);
    auto p_key = mutils::from_bytes_noalloc<std::string>(dsm,v + pos);
    pos += mutils::bytes_size(*p_key);
    auto p_blob = mutils::from_bytes_noalloc<Blob>(dsm, v + pos);
    // TODO: solve the memory leak here: ObjectWithString object is malloc-ed
    return mutils::context_ptr<const ObjectWithStringKey>(
        new ObjectWithStringKey{
        *p_version,
        *p_timestamp_us,
        *p_previous_version,
        *p_previous_version_by_key,
        *p_key,
        *p_blob,true});
}

} // namespace cascade
} // namespace derecho

