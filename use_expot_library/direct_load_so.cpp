#include <iostream>
#include <boost/dll.hpp>

int main() {
    try {
        // 加载动态库
        boost::dll::shared_library myLib("/home/gsk/pro/test_demo/install/lib/liblm_core.so");

        // 获取动态库中的函数指针
        auto myFunction = myLib.get<void()>("HelloCore");

        if (myFunction) {
            // 调用动态库中的函数
            myFunction();
        } else {
            std::cerr << "Failed to load symbol 'HelloCore' from the library." << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
