#include <gflags/gflags.h>
#include <glog/logging.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <signal.h>

using namespace std;

#define LOG_FILE_NAME "SipServer.log"
#define LOG_DIR ""

class SetGlogLevel {
public:
    SetGlogLevel(const int type) {
        // 将日志重定向到指定文件中
        google::InitGoogleLogging(LOG_FILE_NAME);
        // 初始化Google的日志库，并设置日志文件的基本名称为LOG_FILE_NAME。
        // 这会生成以LOG_FILE_NAME为前缀的日志文件。

        // 设置输出到控制台的Log等级
        FLAGS_stderrthreshold = type;
        // 设置日志输出到标准错误输出（stderr）的最低级别。这里的`type`应该是一个表示日志级别的变量。
        // 例如：0为INFO，1为WARNING，2为ERROR，3为FATAL。低于这个级别的日志不会输出到stderr。

        FLAGS_colorlogtostderr = true;
        // 设置为true时，启用彩色日志输出到标准错误输出（stderr），以便更容易区分不同级别的日志。

        FLAGS_logbufsecs = 0;
        // 设置日志刷新到文件的时间间隔为0秒，意味着日志将立即被刷新到文件中，而不是在缓冲区中停留。

        FLAGS_log_dir = LOG_DIR;
        // 设置日志文件的存储目录为LOG_DIR。日志文件将被写入到这个目录中。

        FLAGS_max_log_size = 4;
        // 设置单个日志文件的最大大小为4MB。当日志文件超过这个大小时，会创建一个新的日志文件。

        google::SetLogDestination(google::GLOG_WARNING, "");
        // 设置GLOG_WARNING级别日志的输出目的地为空字符串。
        // 这将禁用GLOG_WARNING级别日志的文件输出，只输出到stderr。

        google::SetLogDestination(google::GLOG_ERROR, "");
        // 设置GLOG_ERROR级别日志的输出目的地为空字符串。
        // 这将禁用GLOG_ERROR级别日志的文件输出，只输出到stderr。

        signal(SIGPIPE, SIG_IGN);
        // 忽略SIGPIPE信号。SIGPIPE信号通常在向一个已关闭的管道或socket写入数据时被触发。
        // 忽略这个信号可以防止程序在这种情况下意外终止。


    }

    ~SetGlogLevel() {
        google::ShutdownGoogleLogging();
    }

};

int main(int argc, char* argv[]) {
   
   SetGlogLevel glog(0);

   LOG(INFO) << "11111111111111";
   LOG(WARNING) << "222222222222";
   LOG(ERROR) << "3333333333";


    return 0;
}
