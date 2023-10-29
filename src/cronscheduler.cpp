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
    m_jobs.push_back(job);
}

void CronScheduler::ScheduleJob(CronJob job){
    m_queue.push(job);
}

CronJob CronScheduler::RunJob(){
    auto job = m_queue.top();
    m_queue.pop();
    return job;
}

std::chrono::time_point<std::chrono::system_clock>  CronScheduler::GetNextExecutionTimePoint (){
    return m_queue.top().m_excutionTime;
}

void CronScheduler::Run(){
    for(CronJob job: m_jobs){
        m_queue.push(job);
        auto id = job.m_identifier;
    }
    while(true){
        while(!m_queue.empty()){ 
            auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto nextExecutionTimePoint = GetNextExecutionTimePoint();
            auto nextExecutionTime = std::chrono::system_clock::to_time_t(nextExecutionTimePoint);
            if(currentTime >= nextExecutionTime){
                auto job = RunJob();
                auto f = job.m_function;
                std::cout << "Starting " << job.m_identifier<< " at " << currentTime <<'\n';
                boost::asio::post(m_pool, f);
                job.m_excutionTime = job.m_excutionTime + job.m_interval + job.m_frequency;
                ScheduleJob(job);
            }
            else
            {
                std::this_thread::sleep_until(nextExecutionTimePoint);
            }
        }
    }
};

