#include <iostream>
#include <memory>
#include <string>

// 抽象句柄
class Handler {
public:
    using Ptr = std::shared_ptr<Handler>;
    Handler(Handler* successor) : _successor(successor) {}
    virtual ~Handler() {}
    virtual void HandleRequest() {
        if (_successor) {
            _successor->HandleRequest();
        }
    }
protected:
    // 后继者
    Handler* _successor = nullptr;
};

// 具体句柄
class ConcreteHandler1 : public Handler {
public:
    ConcreteHandler1(Handler* successor) : Handler(successor) {}
    virtual ~ConcreteHandler1() {}
    void HandleRequest() override {
        std::cout << "ConcreteHandler1 handle request!" << std::endl;
        Handler::HandleRequest();
    }
};

class ConcreteHandler2 : public Handler {
public:
    ConcreteHandler2(Handler* successor) : Handler(successor) {}
    virtual ~ConcreteHandler2() {}
    void HandleRequest() override {
        std::cout << "ConcreteHandler2 handle request!" << std::endl;
        Handler::HandleRequest();
    }
};

// use it!
int main() {
    Handler::Ptr handler1(new ConcreteHandler1(nullptr));
    Handler::Ptr handler2(new ConcreteHandler2(handler1.get()));
    handler2->HandleRequest();
    return 0;
}