#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

class Job
{
    public:
        int id, num_of_pages;
        std::string user_name;

        Job(int id, int num_of_pages, std::string user_name);
        ~Job();
};

Job::Job(int id, int num_of_pages, std::string user_name)
{
    this->id = id;
    this->num_of_pages = num_of_pages;
    this->user_name = user_name;
}

Job::~Job()
{
    std::cout << "id : " << this->id <<'\n';
    std::cout << "Processed pages : " << this->num_of_pages <<'\n';
    std::cout << "user name : " << this->user_name <<'\n';
}

class Printer
{
    public:
        std::queue<Job> Jobs;

        void AddNewJob(Job NowJob);
        void ProcessJobs();
};

void Printer::AddNewJob(Job NowJob)
{
    this->Jobs.push(NowJob);
}

void Printer::ProcessJobs()
{
    while(!this->Jobs.empty())
    {   
        Job NowJob = this->Jobs.front();
        this->Jobs.pop();
        NowJob.~Job();
    }
}

int main()
{
    Job something1 = Job(1, 3, "One");
    Job something2 = Job(2, 3, "Two");
    Job something3 = Job(3, 3, "Three");

    Printer SomePrinter;

    SomePrinter.AddNewJob(something1);
    SomePrinter.AddNewJob(something2);
    SomePrinter.AddNewJob(something3);

    SomePrinter.ProcessJobs();
    return 0;
}