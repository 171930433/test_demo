#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/key.hpp>
#include <memory>
#include <iostream>
#include <string>

using namespace boost::multi_index;

// 定义一个简单的Person类
struct Person
{
    std::string name;
    int age;

    // std::string Name() const { return name; }
    // int Age() const { return age; }

    // 构造函数
    Person(const std::string &name, int age) : name(name), age(age) {}
};

// 定义一个智能指针类型，用于存储 Person 对象
using PersonPtr = std::shared_ptr<Person const>;
std::string Name(PersonPtr sp) { return sp->name; }
int Age(PersonPtr sp) { return sp->age; }

// 定义multi_index_container类型
typedef multi_index_container<
    PersonPtr,
    indexed_by<
        // 第一个索引：按照 name 进行唯一性排序
        ordered_unique<key<Name>>,
        // 第二个索引：按照 age 进行非唯一性排序
        ordered_non_unique<key<Age>>,
        //
        random_access<>>
    //
    >
    PersonContainer;

int fun_sp()
{
    // 创建一个 PersonContainer 对象
    PersonContainer persons;

    // 向容器中插入一些数据（使用智能指针）
    persons.insert(std::make_shared<Person>("Alice", 30));
    persons.insert(std::make_shared<Person>("Bob", 25));
    persons.insert(std::make_shared<Person>("Charlie", 35));

    // 按照键值查找元素
    auto itByName = persons.find("Bob");
    if (itByName != persons.end())
    {
        std::cout << "Found by name: " << (*itByName)->name << ", Age: " << (*itByName)->age << std::endl;
    }
    else
    {
        std::cout << "Not found by name" << std::endl;
    }

    return 0;
}
