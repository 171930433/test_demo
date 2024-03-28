#pragma once

extern "C" void HelloCore();


// 定义 YourClass 类型
class YourClass {
public:
    void yourFunction() {
        std::cout << "Hello from YourClass::yourFunction()" << std::endl;
    }
};


// 定义 createObject() 函数，用于创建 YourClass 类的实例并返回指针
extern "C" inline YourClass* createObject() {
    return new YourClass();
}

// 定义 destroyObject() 函数，用于销毁 YourClass 类的实例
extern "C" inline void destroyObject(YourClass* obj) {
    delete obj;
}