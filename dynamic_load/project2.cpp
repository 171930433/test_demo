#include "dynamic_load/file_load_base.h"
#include <google/protobuf/message.h>

class FileLoader : public IFileLoader
{
  void LoadFromFile() override
  {
    std::cout << "Project2 FileLoader \n";
  }
};

int a = Register("Project2::FileLoader", std::make_shared<FileLoader>());

extern "C" void LoadFromFile(std::string const& filename, std::map<std::string, std::shared_ptr<google::protobuf::Message>>& buffer)
{
    std::cout << "Project2 LoadFromFile func \n";
}