#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <cronjob.hpp>
#include <vector> 
#include <queue>
#include <chrono>
using namespace std;

class CronScheduler{
private:

struct CompareTime
{
    bool operator()(const CronJob& lhs, const CronJob& rhs) const
    {
        return lhs.m_excutionTime > rhs.m_excutionTime;
    }

};

// member variables
static CronScheduler* s_CronScheduler;
boost::asio::thread_pool m_pool;
vector<CronJob> m_jobs;
std::priority_queue<CronJob, vector<CronJob>, CompareTime> m_queue;

CronScheduler(): 
m_pool{},
m_queue{},
m_jobs{}
{
};
~CronScheduler() = default;


public:
void print(){
	std::cout << "Here" << '\n';
} 

// deleting copy constructor
CronScheduler(const CronScheduler& obj) = delete; 

static CronScheduler* GetInstance();

void AddJob(CronJob job);

void ScheduleJob(CronJob job);

CronJob RunJob();

std::chrono::time_point<std::chrono::system_clock> GetNextExecutionTimePoint ();

void Run();
};
