#include <iostream>
#include <string>
#include "mapreduce.hpp"

struct MapTask : public mapreduce::map_task
<
    std::string, std::pair<char const*, std::uintmax_t>
>
{
    template <typename Runtime>
    void operator()(Runtime& runtime, key_type const& key, value_type& value) const
    {
        //Use the function runtime.emit_intermediate().
    }
};

template <typename KeyType>
struct ReduceTask : public mapreduce::reduce_task<KeyType, unsigned>
{
    using typename mapreduce::reduce_task<KeyType, unsigned>::key_type;

    template <typename Runtime, typename It>
    void operator()(Runtime& runtime, key_type const& key, It it, It const ite) const
    {
        //Use the function runtime.emit().
    }
};