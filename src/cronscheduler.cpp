#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include "cronscheduler.hpp"
#include <boost/asio/thread_pool.hpp>

using namespace std;

CronScheduler* CronScheduler::s_CronScheduler = nullptr;

CronScheduler* CronScheduler::GetInstance()
{
    if(!s_CronScheduler){
        s_CronScheduler = new CronScheduler(); 
		cout << "Scheduler initialized successfully " << endl;
    }
    return s_CronScheduler;
};

void CronScheduler::AddJob(CronJob job){
    std::cout << "Adding " << job.m_identifier<< " to scheduler" <<'\n';
    m_jobs.push_back(job);
}

void CronScheduler::ScheduleJob(CronJob job){
    std::cout << "Scheduling " << job.m_identifier << " with execution time = " << std::chrono::system_clock::to_time_t(job.m_excutionTime) <<'\n';
    m_queue.push(job);
}

CronJob CronScheduler::GetHighestPriorityJob(){
    auto job = m_queue.top();
    m_queue.pop();
    return job;
}

std::chrono::time_point<std::chrono::system_clock>  CronScheduler::GetNextExecutionTimePoint (){
    return m_queue.top().m_excutionTime;
}

void CronScheduler::EmptyQueue (){
    while(!m_queue.empty()){
        m_queue.pop();
    }
}

void CronScheduler::RemoveJobs (){
    m_jobs.clear();
}

void CronScheduler::Run(){
    // Loop over jobs and schedule them
    for(CronJob job: m_jobs){
        ScheduleJob(job);
    }
    while(true){
        while(!m_queue.empty()){ 
            // Get current
            auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            // Get execution time for highest priority job in priority queue
            auto nextExecutionTimePoint = GetNextExecutionTimePoint();
            auto nextExecutionTime = std::chrono::system_clock::to_time_t(nextExecutionTimePoint);

            // Check if highest priority job should start executing
            if(currentTime >= nextExecutionTime){

                // Get highest priority job
                auto job = GetHighestPriorityJob();
                auto f = job.m_function;
                std::cout << "Starting " << job.m_identifier<< " at " << currentTime <<'\n';

                // Run highest priority job in threadpool
                boost::asio::post(m_pool, f);

                // Check if we should reschedule
                if(job.m_frequency > std::chrono::seconds(0)){

                    // Calculate next job execution time and schedule it
                    job.m_excutionTime = job.m_excutionTime + job.m_interval + job.m_frequency;
                    ScheduleJob(job);
                }              
            }
            else
            {
                // Sleep until it's time to execute upcoming job
                std::this_thread::sleep_until(nextExecutionTimePoint);
            }
        }
    }
};

