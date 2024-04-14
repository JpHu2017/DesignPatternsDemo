#include <iostream>
#include <map>
#include <memory>
#include <string>

// 享元类
class Flyweight {
public:
    using Ptr = std::shared_ptr<Flyweight>;
    Flyweight() {}
    virtual ~Flyweight() {}

    virtual void Operation(const std::string& extrinsicState) const = 0;
};

// 具体享元类
class ConcreteFlyweight : public Flyweight {
public:
    ConcreteFlyweight(const std::string& intrinsicState) 
        : _intrinsicState(intrinsicState) {}
    virtual ~ConcreteFlyweight() {}

    void Operation(const std::string& extrinsicState) const override {
        std::cout << "Flyweight: intrinsicState = " << _intrinsicState
            << ", extrinsicState = " << extrinsicState << std::endl;
    }

private:
    std::string _intrinsicState;
};

// 享元工厂
class FlyweightFactory {
public:
    FlyweightFactory() {}
    virtual ~FlyweightFactory() {}
    Flyweight::Ptr GetFlyweight(const std::string& key) {
        if (_flyweights.find(key) == _flyweights.end()) {
            _flyweights[key] = std::make_shared<ConcreteFlyweight>(key);
        }
        return _flyweights[key];
    }

private:
    std::map<std::string, Flyweight::Ptr> _flyweights;
};

// use it!
int main() {
    FlyweightFactory factory;
    Flyweight::Ptr flyweight1 = factory.GetFlyweight("A");
    flyweight1->Operation("operation1");

    Flyweight::Ptr flyweight2 = factory.GetFlyweight("B");
    flyweight2->Operation("operation2");

    Flyweight::Ptr flyweight3 = factory.GetFlyweight("A");
    flyweight3->Operation("operation3");

    return 0;
}