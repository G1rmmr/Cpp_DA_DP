#include <iostream>
#include "mapreduce.hpp"

namespace PrimeCalculator
{
    bool const IsPrime(long const number)
    {
        if(number > 2)
        {
            if(number % 2 == 0) return false;

            long const num = std::abs(number);
            long const sqrt_num = static_cast<long>(std::sqrt(
                static_cast<double>(num)));

            for(long i = 3; i <= sqrt_num; i += 2)
                if(num % i == 0) return false;
        }
        else if(number <= 1) return false;
        return true;
    }

    template <typename MapTask>
    class NumberSource : mapreduce::detail::noncopyble
    {
    public:
        NumberSource(long first, long last, long step)
            : sequence_(0), first_(first), last_(last), step_(step){}

        bool const SetUpKey(typename MapTask::key_type& key)
        {
            key = sequence_++;
            return (key * step_ <= last_);
        }

        bool const GetData(typename MapTask::key_type const& key
            , typename MapTask::value_type& value)
        {
            typename MapTask::value_type val;

            val.first = first_ + (key * step_);
            val.second = std::min(val.first + step_ - 1, last_);

            std::swap(val, value);
            return true;
        }

    private:
        long sequence_;
        long const step_;
        long const last_;
        long const first_;
    };

    struct MapTask : public mapreduce::map_task<long, std::pair<long, long>>
    {
        template <typename Runtime>
        void operator()(Runtime& runtime, key_type const&, value_type const& value) const
        {
            for(key_type loop = value.first; loop <= value.second; ++loop)
                runtime.emit_intermediate(IsPrime(loop), loop);
        }
    };

    struct ReduceTask : public mapreduce::reduce_task<bool, long>
    {
        template <typename Runtime, typename It>
        void operator()(Runtime& runtime, key_type const& key, It it, It ite) const
        {
            if(key) std::for_each(it, ite, std::bind(&Runtime::emit, &runtime
                , true, std::placeholders::_1));
        }
    };

    typedef mapreduce::Job<PrimeCalculator::MapTask,
        PrimeCalculator::ReduceTask,
        mapreduce::null_combiner,
        PrimeCalculator::NumberSource<PrimeCalculator::MapTask>> Job;
}

int main()
{
    mapreduce::specification spec;
    int prime_limit = 1000;

    int cpu_cores = std::max(1U, std::thread::hardware_concurrency());
    spec.map_tasks = cpu_cores;
    spec.reduce_tasks = cpu_cores;

    PrimeCalculator::Job::datasource_type datasource(0, prime_limit
        , prime_limit / spec.reduce_tasks);

    std::cout << "Range in (0, " << prime_limit 
    << "), search the prime numbers: " << std::endl;

    std::cout << "The number of cpu cores: " << cpu_cores << std::endl;

    PrimeCalculator::Job Job(datasource, spec);
    mapreduce::results result;

    Job.run<mapreduce::schedule_policy::cpu_parallel<PrimeCalculator::Job>>(result);

    std::cout << "Mapreduce operating time: " << result.job_runtime.count() << " sec."
    << std::endl;

    std::cout << "The number of prime numbers: " 
    << std::distance(Job.begin_results(), Job.end_results()) << std::endl;

    for(auto it = Job.begin_results(); it != job.end_results(); ++it)
        std::cout << it->second << ' ';

    std::cout << std::endl;
    return 0;
}