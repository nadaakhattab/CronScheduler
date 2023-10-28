#include <boost/asio/thread_pool.hpp>
using namespace std;

class CronScheduler{
private:

// member variables
static CronScheduler* s_CronScheduler;
std::shared_ptr<boost::asio::thread_pool> m_pool;

CronScheduler() = default;
~CronScheduler() = default;


public:

// deleting copy constructor
CronScheduler(const CronScheduler& obj) = delete; 

static CronScheduler* GetInstance();

bool Initialize();

static int GetNumberOfThreads();
};
