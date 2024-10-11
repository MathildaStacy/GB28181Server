#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(name, "world", "The name to greet");

int main(int argc, char* argv[]) {
    // 初始化 gflags 和 glog
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    // 使用 glog 输出日志
    LOG(INFO) << "Hello, " << FLAGS_name << "!";
    
    // 关闭 gflags 和 glog
    google::ShutdownGoogleLogging();
    gflags::ShutDownCommandLineFlags();

    return 0;
}
