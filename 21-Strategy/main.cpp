#include <iostream>
#include <list>
#include <memory>
#include <string>
class Strategy {
public:
    using Ptr = std::shared_ptr<Strategy>;
    Strategy() {}
    virtual ~Strategy() {}
    virtual void AlgorithmInterface() = 0;
};
class Context {
public:
    Context(Strategy* strategy) : _strategy(strategy) {}
    virtual ~Context() {}
    void ContextInterface() {
        if (_strategy) {
            _strategy->AlgorithmInterface();
        }
    }
    void ChangeStrategy(Strategy* strategy) {
        _strategy = strategy;
    }
protected:
    Strategy* _strategy;
};

class ConcreteStrategyA : public Strategy {
public:
    ConcreteStrategyA() {}
    virtual ~ConcreteStrategyA() {}
    void AlgorithmInterface() override {
        std::cout << "Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    ConcreteStrategyB() {}
    virtual ~ConcreteStrategyB() {}
    void AlgorithmInterface() override {
        std::cout << "Strategy B" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Strategy::Ptr strategyA = std::make_shared<ConcreteStrategyA>();
    Context ctx(strategyA.get());
    ctx.ContextInterface();
    Strategy::Ptr strategyB = std::make_shared<ConcreteStrategyB>();
    // 改变策略
    ctx.ChangeStrategy(strategyB.get());
    ctx.ContextInterface();
    return 0;
}