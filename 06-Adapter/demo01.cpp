#include <iostream>

// 接口
class Target {
public:
    Target() {}
    virtual ~Target() {}
    virtual void Request() = 0;
};
// 被适配类
class Adaptee {
public:
    Adaptee() {}
    virtual ~Adaptee() {}
    void SpecificRequest() {
        std::cout << "Do something!" << std::endl;
    }
};
// 适配器
class Adapter : public Target, public Adaptee {
public:
    Adapter() : Target(), Adaptee() {}
    virtual ~Adapter() {}
    void Request() override {
        SpecificRequest();
    }
};

// use it!
int main(int argc, char* argv[]) {
    Target* t = new  Adapter();
    t->Request();
    return 0;
}