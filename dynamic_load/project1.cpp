#include "dynamic_load/file_load_base.h"
#include <google/protobuf/message.h>

class FileLoader : public IFileLoader
{
public:
  void LoadFromFile() override
  {
    std::cout << "Project1 FileLoader \n";
  }
};


extern "C" void LoadFromFile(std::string const& filename, std::map<std::string, std::shared_ptr<google::protobuf::Message>>& buffer)
{
    std::cout << "Project1 LoadFromFile func \n";
}

int a = Register("Project1::FileLoader", std::make_shared<FileLoader>());
