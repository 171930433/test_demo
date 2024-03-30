#include <string>
#include <iostream>
#include <boost/serialization/singleton.hpp>
#include <unordered_map>
#include <memory>
#include <google/protobuf/message.h>


using spMessage = std::shared_ptr<google::protobuf::Message>;
using MessageMapBuffer = std::map<std::string,spMessage>;


class IFileLoader
{
public:
  IFileLoader() = default;
  virtual ~IFileLoader() {  std::cout << "IFileLoader delete\n";  }
  virtual void LoadFromFile() = 0;
};

using spIFileLoader = std::shared_ptr<IFileLoader>;

class FileLoaderManager : public boost::serialization::singleton<FileLoaderManager>
{
public:
  ~FileLoaderManager() {}
  std::unordered_map<std::string, spIFileLoader> loaders_;
};


static inline int Register(std::string const& name, spIFileLoader fl)
{
  FileLoaderManager::get_mutable_instance().loaders_[name] = fl;
  return 0;
}
