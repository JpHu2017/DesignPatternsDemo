#include <iostream>
#include <memory>

/// 接口
// 产品A
class AbstractProductA {
public:
    using Ptr = std::shared_ptr<AbstractProductA>;
    AbstractProductA() = default;
    virtual ~AbstractProductA() = default;
    
    virtual void printA() = 0;
};
// 产品B
class AbstractProductB {
public:
    using Ptr = std::shared_ptr<AbstractProductB>;
    AbstractProductB() = default;
    virtual ~AbstractProductB() = default;

    virtual void printB() = 0;
};
// 工厂
class AbstractFactory {
public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;
    
    virtual AbstractProductA::Ptr createProductA() = 0;
    virtual AbstractProductB::Ptr createProductB() = 0;
};

/// 具体类
// 品牌1中的A产品
class ProductA1 : public AbstractProductA {
public:
    ProductA1() = default;
    virtual ~ProductA1() = default;
    
    void printA() override {
        std::cout << "I'm ProductA1" << std::endl;
    }
};
// 品牌2中的A产品
class ProductA2 : public AbstractProductA {
public:
    ProductA2() = default;
    virtual ~ProductA2() = default;
    
    void printA() override {
        std::cout << "I'm ProductA2" << std::endl;
    }
};

// 品牌1中的B产品
class ProductB1 : public AbstractProductB {
public:
    ProductB1() = default;
    virtual ~ProductB1() = default;
    
    void printB() override {
        std::cout << "I'm ProductB1" << std::endl;
    }
};
// 品牌2中的B产品
class ProductB2 : public AbstractProductB {
public:
    ProductB2() = default;
    virtual ~ProductB2() = default;
    
    void printB() override {
        std::cout << "I'm ProductB2" << std::endl;
    }
};

// 生产品牌1产品的工厂
class ConcreteFactory1 : public AbstractFactory {
public:
    ConcreteFactory1() = default;
    virtual ~ConcreteFactory1() = default;
    
    AbstractProductA::Ptr createProductA() override {
        AbstractProductA::Ptr product_ptr;
        product_ptr.reset(new ProductA1());
        return product_ptr;
    }
    AbstractProductB::Ptr createProductB() override {
        AbstractProductB::Ptr product_ptr;
        product_ptr.reset(new ProductB1());
        return product_ptr;
    }
};
// 生产品牌2产品的工厂
class ConcreteFactory2 : public AbstractFactory {
public:
    ConcreteFactory2() = default;
    virtual ~ConcreteFactory2() = default;
    
    AbstractProductA::Ptr createProductA() override {
        AbstractProductA::Ptr product_ptr;
        product_ptr.reset(new ProductA2());
        return product_ptr;
    }
    AbstractProductB::Ptr createProductB() override {
        AbstractProductB::Ptr product_ptr;
        product_ptr.reset(new ProductB2());
        return product_ptr;
    }
};

// use it!
int main(int argc, char* argv[]) {
    AbstractFactory* af = new ConcreteFactory1();
    auto product_a = af->createProductA();
    product_a->printA();
    auto product_b = af->createProductB();
    product_b->printB();
    return 0;
}