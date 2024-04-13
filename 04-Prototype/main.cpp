#include <memory>
#include <iostream>

/// 接口
class ProtoType {
public:
    using Ptr = std::shared_ptr<ProtoType>;
    ProtoType() = default;
    virtual ~ProtoType() = default;

    virtual ProtoType::Ptr clone() = 0;

    virtual void print() = 0;
};

/// 具体类
class ConcretePrototype1 : public ProtoType {
public:
    ConcretePrototype1() = default;
    virtual ~ConcretePrototype1() = default;

    ProtoType::Ptr clone() override {
        ProtoType::Ptr ptr(new ConcretePrototype1(*this));
        return ptr;
    }
    void print() override {
        std::cout << "ProtoType1" << std::endl;
    }
};
class ConcretePrototype2 : public ProtoType {
public:
    ConcretePrototype2() = default;
    virtual ~ConcretePrototype2() = default;

    ProtoType::Ptr clone() override {
        ProtoType::Ptr ptr(new ConcretePrototype2(*this));
        return ptr;
    }
    void print() override {
        std::cout << "ProtoType2" << std::endl;
    }
};

/// use it
int main(int argc, char* argv[]) {
    ProtoType::Ptr ptr(new ConcretePrototype2());
    ptr->clone()->print();
    return 0;
}