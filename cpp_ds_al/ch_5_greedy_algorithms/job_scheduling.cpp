#include <iostream>
#include <algorithm>
#include <vector>

struct Job
{
    int id, start_time, end_time;
    Job(int i, int s, int e) : id(i), start_time(s), end_time(e){}
};

bool compare(Job job1, Job job2)
{
    if(job1.end_time < job2.end_time) return true;
    return false;
}

auto Schedule(std::vector<Job>& jobs, int n)
{
    std::vector<Job> job_contents;
    std::sort(jobs.begin(), jobs.end(), compare);

    int current_job_end_time = jobs.front().end_time;
    job_contents.emplace_back(jobs.front());

    for(int i = 1; i < n; ++i)
        if(jobs[i].start_time >= current_job_end_time)
        {
            job_contents.emplace_back(jobs[i]);
            current_job_end_time = jobs[i].end_time;
        }

    return job_contents;
}

void PrintJobs(std::vector<Job> jobs)
{
    int max_end_time = 0;

    for(auto& job : jobs)
        max_end_time = std::max(max_end_time, job.end_time);

    for(auto& job : jobs)
    {
        std::cout << '[' << job.id << "] " << job.start_time 
            << " -> " << job.end_time << "\t|";
            
        for(int i = 0; i < job.start_time - 1; ++i) std::cout << ' ';
        for(int i = 0; i < job.end_time - job.start_time; ++i) std::cout << '*';
        for(int i = 0; i < max_end_time - job.end_time; ++i) std::cout << ' ';
        
        std::cout << '|' << std::endl;
    }
    std::cout << std::endl;
}