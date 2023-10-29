#define BOOST_TEST_MODULE CronSchedulerTest
#include "cronscheduler.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector> 
#include <queue>
#include <chrono>

void job1P(){
	auto current = std::chrono::system_clock::now();
	auto interval = std::chrono::seconds(5);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}
	std::cout << "Exiting Job1 at " << std::chrono::system_clock::to_time_t(current) << '\n';		
} 

void job2P(){
	auto current = std::chrono::system_clock::now();
	auto interval = std::chrono::seconds(10);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}	
	std::cout << "Exiting Job2 at " << std::chrono::system_clock::to_time_t(current) << '\n';	
} 

BOOST_AUTO_TEST_CASE(RemoveJobsTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->AddJob(job1);
    scheduler->AddJob(job2);
    scheduler->RemoveJobs();
    BOOST_CHECK_EQUAL(scheduler->m_jobs.size(), 0);
}

BOOST_AUTO_TEST_CASE(EmptyQueueTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    scheduler->RemoveJobs();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->AddJob(job1);
    scheduler->AddJob(job2);
    scheduler->EmptyQueue();
    BOOST_CHECK_EQUAL(scheduler->m_queue.size(), 0);
}

BOOST_AUTO_TEST_CASE(AddJobTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    scheduler->EmptyQueue();
    scheduler->RemoveJobs();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->AddJob(job1);
    scheduler->AddJob(job2);
    BOOST_CHECK_EQUAL(scheduler->m_jobs.size(), 2);
}

BOOST_AUTO_TEST_CASE(ScheduleJobTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    scheduler->EmptyQueue();
    scheduler->RemoveJobs();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->ScheduleJob(job1);
    scheduler->ScheduleJob(job2);
    BOOST_CHECK_EQUAL(scheduler->m_queue.size(), 2);
}

BOOST_AUTO_TEST_CASE(RunJobTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    scheduler->EmptyQueue();
    scheduler->RemoveJobs();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->ScheduleJob(job1);
    scheduler->ScheduleJob(job2);
    auto job = scheduler->RunJob();

    BOOST_CHECK_EQUAL(scheduler->m_queue.size(), 1);
}

BOOST_AUTO_TEST_CASE(GetNextExecutionTimePointTest) {
    CronScheduler* scheduler = CronScheduler::GetInstance();
    scheduler->EmptyQueue();
    scheduler->RemoveJobs();
    CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
    scheduler->ScheduleJob(job1);
    scheduler->ScheduleJob(job2);
    auto nextExecutionTimePoint = std::chrono::system_clock::to_time_t(scheduler->GetNextExecutionTimePoint());
    auto expectedExecutionTimePoint = std::chrono::system_clock::to_time_t(job1.m_excutionTime);
    BOOST_CHECK_EQUAL(nextExecutionTimePoint, expectedExecutionTimePoint);
}