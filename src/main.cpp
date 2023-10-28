#include <iostream>
#include "cronscheduler.hpp"

int main()
{
	cout << "Will create scheduler: " << endl;
	auto sched = CronScheduler::GetInstance()->Initialize();
}