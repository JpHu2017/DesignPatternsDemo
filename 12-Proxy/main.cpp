#include <iostream>
#include <memory>
#include <string>

// 抽象主题
class Subject {
public:
    Subject() {}
    virtual ~Subject() {}

    virtual void Request() = 0;
};

// 真实主题
class RealSubject : public Subject {
public:
    using Ptr = std::shared_ptr<RealSubject>;
    RealSubject() : Subject() {}
    virtual ~RealSubject() {}
    
    void Request() override {
        std::cout << "Real subject request!" << std::endl;
    }
};

// 代理
class Proxy : public Subject {
public:
    using Ptr = std::shared_ptr<Proxy>;
    Proxy() : Subject() {}
    virtual ~Proxy() {}

    void Request() override {
        if (_realSubject.get() == nullptr) {
            _realSubject.reset(new RealSubject());
        }
        DoProxy();
        _realSubject->Request();
    }

    void DoProxy() {
        std::cout << "I'm doing proxy!" << std::endl;
    }
private:
    RealSubject::Ptr _realSubject = nullptr;
};

// use it!
int main() {
    Proxy::Ptr proxy(new Proxy());
    proxy->Request();
    return 0;
}