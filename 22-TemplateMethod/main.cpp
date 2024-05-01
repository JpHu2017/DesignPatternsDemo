#include <iostream>
#include <list>
#include <memory>
#include <string>
class AbstractClass {
public:
    using Ptr = std::shared_ptr<AbstractClass>;
    AbstractClass() {}
    virtual ~AbstractClass() {}
    void TemplateMethod() {
        this->PrimitiveOperation1();
        this->PrimitiveOperation2();
    }
protected:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
};

class ConcreteClassA : public AbstractClass {
public:
    ConcreteClassA() {}
    virtual ~ConcreteClassA() {}
protected:
    void PrimitiveOperation1() override {
        std::cout << "A operation1" << std::endl;
    }
    void PrimitiveOperation2() override {
        std::cout << "A operation2" << std::endl;
    }
};

class ConcreteClassB : public AbstractClass {
public:
    ConcreteClassB() {}
    virtual ~ConcreteClassB() {}
protected:
    void PrimitiveOperation1() override {
        std::cout << "B operation1" << std::endl;
    }
    void PrimitiveOperation2() override {
        std::cout << "B operation2" << std::endl;
    }
};
int main(int argc, char* argv[]) {
    AbstractClass::Ptr absClass(new ConcreteClassA());
    absClass->TemplateMethod();
    absClass.reset(new ConcreteClassB());
    absClass->TemplateMethod();
    return 0;
}