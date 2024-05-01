#include <iostream>
#include <list>
#include <memory>
#include <string>

class ConcreteElementA;
class ConcreteElementB;
class Visitor {
public:
    using Ptr = std::shared_ptr<Visitor>;
    Visitor() {}
    virtual ~Visitor() {}
    virtual void VisitorConcreteElementA(ConcreteElementA* elem) = 0;
    virtual void VisitorConcreteElementB(ConcreteElementB* elem) = 0;
};

class Element {
public:
    using Ptr = std::shared_ptr<Element>;
    Element() {}
    virtual ~Element() {}
    virtual void Accept(Visitor* v) = 0;
    virtual std::string Name() = 0;
};

class ConcreteElementA : public Element {
public:
    ConcreteElementA() {}
    virtual ~ConcreteElementA() {}
    void Accept(Visitor* v) override;
    std::string Name() override {
        return "ElementA";
    }
};
class ConcreteElementB : public Element {
public:
    ConcreteElementB() {}
    virtual ~ConcreteElementB() {}
    void Accept(Visitor* v) override;
    std::string Name() override {
        return "ElementB";
    }
};

void ConcreteElementA::Accept(Visitor* v) {
    v->VisitorConcreteElementA(this);
}
void ConcreteElementB::Accept(Visitor* v) {
    v->VisitorConcreteElementB(this);
}

class ConcreteVisitor1 : public Visitor {
public:
    ConcreteVisitor1() {}
    virtual ~ConcreteVisitor1() {}
    void VisitorConcreteElementA(ConcreteElementA* elem) override {
        std::cout << "operation " << elem->Name() << " by visitor1" << std::endl;
    }
    void VisitorConcreteElementB(ConcreteElementB* elem) override {
        std::cout << "operation " << elem->Name() << " by visitor1" << std::endl;
    }
};
class ConcreteVisitor2 : public Visitor {
public:
    ConcreteVisitor2() {}
    virtual ~ConcreteVisitor2() {}
    void VisitorConcreteElementA(ConcreteElementA* elem) override {
        std::cout << "operation " << elem->Name() << " by visitor2" << std::endl;
    }
    void VisitorConcreteElementB(ConcreteElementB* elem) override {
        std::cout << "operation " << elem->Name() << " by visitor2" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Element::Ptr elemA(new ConcreteElementA());
    Element::Ptr elemB(new ConcreteElementB());
    Visitor::Ptr v1(new ConcreteVisitor1());
    elemA->Accept(v1.get());
    elemB->Accept(v1.get());
    Visitor::Ptr v2(new ConcreteVisitor2());
    elemA->Accept(v2.get());
    elemB->Accept(v2.get());
    return 0;
}