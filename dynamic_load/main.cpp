#include "dynamic_load/file_load_base.h"
#include <boost/dll.hpp>

int main()
{

  std::cout << FileLoaderManager::get_mutable_instance().loaders_.size() << "\n";

  try
  {
    // 加载动态库
    boost::dll::shared_library myLib("/home/gsk/pro/test_demo/build/dynamic_load/libproject1.so");
    boost::dll::shared_library myLib2("/home/gsk/pro/test_demo/build/dynamic_load/libproject2.so");

    // 1. 通过基类指针实现动态加载
    for (auto [name, loader] : FileLoaderManager::get_mutable_instance().loaders_)
    {
      loader->LoadFromFile();
    }

    MessageMapBuffer buffer;

    // 2. 通过导出的函数名称调用
    if (auto* func_ptr = myLib.get<void(std::string const&, MessageMapBuffer&)>("LoadFromFile"); func_ptr)
    {
      func_ptr("123", buffer);
    }
    else
    {
      std::cerr << "Failed to load symbol 'LoadFromFile' from the library." << std::endl;
    }

    std::cout << FileLoaderManager::get_mutable_instance().loaders_.size() << "\n";
    FileLoaderManager::get_mutable_instance().loaders_.clear(); // 必须在这里析构,因为shared_library析构后,全局FileLoaderManager在析构时,已经找不到库里面的实际对象的析构函数
  }
  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << " done\n";

  return 0;
}