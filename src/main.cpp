#include <iostream>
#include "cronscheduler.hpp"
#include <cronjob.hpp>

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

void job3P(){
	auto current = std::chrono::system_clock::now();
	auto interval = std::chrono::seconds(15);
	auto end = current + interval;
	while(current < end){
		current = std::chrono::system_clock::now();
	}
	std::cout << "Exiting Job3 at " << std::chrono::system_clock::to_time_t(current) << '\n';	
} 

int main()
{
	cout << "Will create scheduler: " << endl;
	CronJob job1(5, 30, 0, job1P, "Job1");
	CronJob job2(10, 20 , 0, job2P,"Job2");
	CronJob job3(15, 30, 0, job3P,"Job3");
	auto scheduler = CronScheduler::GetInstance();
	scheduler->AddJob(job1);
	scheduler->AddJob(job2);
	scheduler->AddJob(job3);
	scheduler->Run();
}