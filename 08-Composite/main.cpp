#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/// 接口
class Component {
public:
    using Ptr = std::shared_ptr<Component>;
    Component(const std::string& name) : _name(name) {}
    virtual ~Component() {}
    
    virtual void Operation() = 0;
    virtual void Add(Component::Ptr component) {}
    virtual void Remove(Component::Ptr component) {}
    virtual Component* GetChild(int index) {return nullptr;}
protected:
    std::string _name;
};

class Leaf : public Component {
public:
    Leaf(const std::string& name) : Component(name) {}
    virtual ~Leaf() {}
    void Operation() override {
        std::cout << "I'm a leaf: " << _name << "!" << std::endl;
    }
};
class Composite : public Component {
public:
    Composite(const std::string& name) : Component(name) {}
    virtual ~Composite() {}

    void Operation() override {
        std::cout << ">>>" << std::endl;
        std::cout << "I'm a composite: " << _name << "!" << std::endl;
        for (auto& g : _children) {
            g->Operation();
        }
        std::cout << "<<<" << std::endl;
    }
    void Add(Component::Ptr component) override {
        _children.push_back(component);
    }
    void Remove(Component::Ptr component) override {
        auto iter = std::find(_children.begin(), _children.end(), component);
        if (iter == _children.end()) {return;}
        _children.erase(iter);
    }
    Component* GetChild(int index) override {
        if (index < 0 || index >= _children.size()) {return nullptr;}
        return _children[index].get();
    }
private:
    std::vector<Component::Ptr> _children;
};

// use it!
int main(int argc, char* argv[]) {
    std::cout << "---------Add case---------" << std::endl;
    Component::Ptr leaf1(new Leaf("one"));
    Component::Ptr leaf2(new Leaf("two"));
    Component::Ptr composite1(new Composite("cone"));
    composite1->Add(leaf1);
    composite1->Add(leaf2);
    Component::Ptr leaf3(new Leaf("three"));
    Component::Ptr composite2(new Composite("ctwo"));
    composite2->Add(composite1);
    composite2->Add(leaf3);
    composite2->Operation();

    std::cout << "--------Remove case--------" << std::endl;
    composite2->Remove(leaf3);
    composite2->Operation();
    return 0;
}