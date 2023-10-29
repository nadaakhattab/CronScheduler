#pragma once
#include <boost/function.hpp>

using namespace std;

class CronJob{
public:
std::chrono::seconds m_interval;
std::chrono::seconds m_frequency;
std::chrono::time_point<std::chrono::system_clock> m_excutionTime;
boost::function<void(void)> m_function;
string m_identifier;

CronJob(int interval, int frequency, boost::function<void(void)> function, string id): 
m_interval{ interval },
m_frequency{ frequency },
m_function{ function },
m_identifier{ id },
m_excutionTime { std::chrono::system_clock::now() }
{

}

};
