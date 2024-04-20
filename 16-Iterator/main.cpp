#include <iostream>
#include <vector>

// 迭代器
template<class Item>
class Iterator {
public:
    Iterator() {}
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual Item* CurrentItem() = 0;
};
// 聚合类接口
template <class Item>
class Aggregate {
public:
    Aggregate() {}
    virtual ~Aggregate() {}
    virtual int GetSize() = 0;
    virtual void Push(Item item) = 0;
    virtual Item* At(int index) = 0;
    virtual Iterator<Item>* CreateIterator() = 0;
};

// 具体迭代器声明
template <class Item>
class ConcreteIterator : public Iterator<Item> {
public:
    ConcreteIterator(Aggregate<Item>* aggregate) 
        : _aggregate(aggregate), _current(0) {}
    virtual ~ConcreteIterator() {}
    void First() override;
    void Next() override;
    bool IsDone() override;
    Item* CurrentItem() override;
private:
    Aggregate<Item>* _aggregate;
    int _current;
};
// 具体聚合类
template <class Item>
class ConcreteAggregate : public Aggregate<Item> {
public:
    ConcreteAggregate() {}
    virtual ~ConcreteAggregate() {}
    int GetSize() override {
        return _data.size();
    }
    void Push(Item item) override {
        _data.push_back(item);
    }
    Item* At(int index) override {
        return &_data[index];
    }
    Iterator<Item>* CreateIterator() override {
        return new ConcreteIterator<Item>(this);
    }
private:
    std::vector<Item> _data;
};

template <class Item>
void ConcreteIterator<Item>::First()  {
    _current = 0;
}
template <class Item>
void ConcreteIterator<Item>::Next() {
    if (_current < _aggregate->GetSize()) {
        ++_current;
    }
}
template <class Item>
bool ConcreteIterator<Item>::IsDone() {
    return _current >= _aggregate->GetSize();
}
template <class Item>
Item* ConcreteIterator<Item>::CurrentItem() {
    if (_current < _aggregate->GetSize()) {
        return _aggregate->At(_current);
    } else {
        return nullptr;
    }
}

int main(int argc, char* argv[]) {
    Aggregate<float>* aggregate = new ConcreteAggregate<float>();
    aggregate->Push(1.0);
    aggregate->Push(3.0);
    aggregate->Push(5.0);
    Iterator<float>* iter = aggregate->CreateIterator();
    for (iter->First(); !iter->IsDone(); iter->Next()) {
        std::cout << *(iter->CurrentItem()) << std::endl;
    }
    return 0;
}