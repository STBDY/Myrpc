#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H
#include<string>
//日志模块
/*
日志分级别LoginLevel：Debug、Info、Error
日志内容LogEvent：文件名、行号、MsgNO、进程id、Thread id、日期、时间（精确到ms）、自定义消息
打印到文件，支持日期命名 :Logger                      
日志滚动
C格式化风格
线程安全
日志格式：[level][%y-%m-%d %H:%M:%s,%ms]\t[m_pid:thread_id]\t[file_name:line][%msg]

*/


namespace rocket{

template<typename... Args>
std::string formatString(const char* str,Args&&... args){
    int size = snprintf(nullptr,0,str,args);//依据str格式化输入args，并把结果放入str，返回字符串长度
    std::string result;
    if(size > 0){
        result.resize(size);
        snprintf(&result[0],size+1,str,args...);
    }
    return result;
}
enum LogLevel{
    Debug = 1,
    Info = 2,
    Error = 3
};

std::string LogLevelToString(LogLevel level);

class LogEvent{
    public:
    std::string getFileName() const {
        return m_file_line;
    }
        LogLevel getLogLevel() const{
            return m_level;
        }
    std::string toString();
    private:
        std::string m_file_name;//文件名
        std::string m_file_line;//行号
        int m_pid;//进程号
        int m_thread_id;
        LogLevel m_level;//日志级别 


        
};
//打印日志类
class Logger{
public:
    
private:
    LogLevel m_set_level;
}
}

#endif