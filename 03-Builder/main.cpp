#include <iostream>
#include <string>

/// 接口
//建造者
class Builder {
public:
    Builder() = default;
    virtual ~Builder() = default;
  
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
};

/// 具体建造者
class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() = default;
    virtual ~ConcreteBuilder() = default;
    struct Product {
        std::string parta;
        std::string partb;
        std::string partc;
        void print() {
            std::cout << parta << ", " << partb << ", " << partc << std::endl;
        }
    };
    void buildPartA() override {
        _product.parta = "Part A";
    }
    void buildPartB() override {
        _product.partb = "Part B";
    }
    void buildPartC() override {
        _product.partc = "Part C";
    }
    const Product& getProduct() const {
        return _product;
    }
private:
    Product _product;
};

// 指导者
class Director { 
public:
    Director(Builder* builder) : _builder(builder) {}
    virtual ~Director() = default;
    void construct() {
        _builder->buildPartA();
        _builder->buildPartB();
        _builder->buildPartC();
    }
private:
    Builder* _builder = nullptr;
};

// use it!
int main(int argc, char* argv[]) {
    ConcreteBuilder* builder = new ConcreteBuilder();
    Director* dircetor = new Director(builder);
    dircetor->construct();
    ConcreteBuilder::Product product = builder->getProduct();
    product.print();
    return 0;
}