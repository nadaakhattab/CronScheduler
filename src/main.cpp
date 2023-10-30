#include <iostream>
#include "cronscheduler.hpp"
#include <cronjob.hpp>

void job1P(){
	auto start = std::chrono::system_clock::now();
	auto current = start;
	auto interval = std::chrono::seconds(5);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}
	auto elapsedTime = current - start;
	std::cout << "Exiting Job1 at " << std::chrono::system_clock::to_time_t(current) << "with elapsed time = " << elapsedTime.count() << '\n';		
} 

void job2P(){
	auto start = std::chrono::system_clock::now();
	auto current = start;
	auto interval = std::chrono::seconds(10);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}	
	auto elapsedTime = current - start;
	std::cout << "Exiting Job1 at " << std::chrono::system_clock::to_time_t(current) << "with elapsed time = " << elapsedTime.count() << '\n';		
} 

void job3P(){
	auto start = std::chrono::system_clock::now();
	auto current = start;
	auto interval = std::chrono::seconds(15);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}
	auto elapsedTime = current - start;
	std::cout << "Exiting Job1 at " << std::chrono::system_clock::to_time_t(current) << "with elapsed time = " << elapsedTime.count() << '\n';	
} 

int main()
{
	// Initialize jobs
 	CronJob job1(5, 30, job1P, "Job1");
	CronJob job2(10, 20 , job2P,"Job2");
	CronJob job3(15, 30, job3P,"Job3");

	// Initialize scheduler
	cout << "Will create scheduler: " << endl;
	auto scheduler = CronScheduler::GetInstance();

	// Add jobs to scheduler
	scheduler->AddJob(job1);
	scheduler->AddJob(job2);
	scheduler->AddJob(job3);

	// Run scheduler
	scheduler->Run();
}