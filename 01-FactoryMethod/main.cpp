#include <iostream>
#include <memory>

/// 接口
// 产品
class Product {
public:
    using Ptr = std::shared_ptr<Product>;
    Product() = default;
    virtual ~Product() = default;

    virtual void print() = 0;
};
// 工厂
class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;
    virtual Product::Ptr create() = 0;
};

/// 具体类
// A产品
class ProductA : public Product {
public:
    void print() override {
        std::cout << "Product A" << std::endl;
    }
};
// 生产A产品的工厂
class FactoryA : public Factory {
public:
    Product::Ptr create() override {
        Product::Ptr product;
        product.reset(new ProductA());
        return product;
    }
};

// B产品
class ProductB : public Product {
public:
    void print() override {
        std::cout << "Product A" << std::endl;
    }
};
// 生产B产品的工厂
class FactoryB : public Factory {
public:
    Product::Ptr create() override {
        Product::Ptr product;
        product.reset(new ProductB());
        return product;
    }
};

// use it!
int main(int argc, char* argv[]) {
    Factory* f = new FactoryA();
    Product::Ptr p = f->create();
    p->print();
    return 0;
}
