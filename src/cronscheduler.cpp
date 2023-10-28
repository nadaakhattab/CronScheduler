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
    }
    return s_CronScheduler;
};

bool CronScheduler::Initialize(){
	try
	{
		auto threads = GetNumberOfThreads();
		m_pool = std::make_shared<boost::asio::thread_pool>(threads);
		cout << "Scheduler initialized successfully " << endl;
		return true;
	}
	catch(...)
	{
		cout << "Initialization exception " << endl;
		return false;
	}

	
}

int CronScheduler::GetNumberOfThreads(){
	auto n_threads = std::thread::hardware_concurrency();
	return n_threads == 0 ? 4 : n_threads;
}

