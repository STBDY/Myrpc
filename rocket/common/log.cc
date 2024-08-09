#include<sys/time.h>
#include "rocket/common/log.h"
#include "rocket/common/util.h"
namespace rocket{
    std::string LogEvent::LogLevelToString(LogLevel level){
        switch (level)
        {
        case Debug:
            return "DEBUG";
        case Info:
            return "INFO";
        case  Error:
            return "ERROR";
        
        default:
            return "UNKNOWN";
        }
    }
    std::string LogEvent::toString{
        struct timeval now_time;
        gettimeofday(&now_time,nullptr);//获取时间
        struct tm now_time_t;
        localtime_r(&(now_time.tv_sec),&now_time_t);
        char buf[128];
        strftime(&buf[0],128,"%y-%m-%d %H:%M:%S",&now_time_t);
        std::string time_str(buf);
        int ms=now_time.tv_sec/1000;
        time_str=time_str+"."+std::to_string(ms);

        m_pid = getPid();
        m_thread_id = getThreadId();

        std::stringstream ss;
        ss<<"["<< LogLevelToString(m_level) <<"]\t"
        <<"[" << time_str << "]\t"
        <<"[" << std::string(__FILE__) << __LINE__ << "]\t";
        return ss.str();

    }
    void Logger::log(LogEvent event){
        if(event.getLoglevel()<m_set_level){
            return;
        }
    }
}