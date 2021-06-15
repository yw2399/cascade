#include <cascade/object.hpp>
#include <functional>

namespace derecho {
namespace cascade {

template <typename KT, typename VT>
using output_collector_t=std::function<void(const KT& key, const VT& value)>;

template <typename KT1,typename VT1, typename KT2, typename VT2>
void mapper(const KT1& k1,const VT1& v1,const output_collector_t<KT2,VT2>& collector);

template <typename KT2,typename VT2,typename KT3, typename VT3>
void reducer(const KT2& k1, const std::set<VT2>& v2_set, const output_collector_t<KT3,VT3>& collector);

}
}
