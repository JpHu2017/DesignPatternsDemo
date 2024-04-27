#include <iostream>
#include <string>
#include <vector>

// 备忘录
class Originator;
class Memento {
public:
    virtual ~Memento() {}
    std::string GetState() const {
        return _state;
    }
    void SetState(const std::string& state) {
        _state = state;
    }
private:
    friend class Originator;
    Memento(const std::string& state) : _state(state) {}
private:
    std::string _state;
};

// 原发器
class Originator {
public:
    Originator() {}
    virtual ~Originator() {}

    std::string GetState() const {
        return _state;
    }
    void SetState(const std::string& state) {
        _state = state;
    }
    void PrintState() {
        std::cout << "State: " << _state << std::endl;
    }
    void SetMemento(Memento* memento) {
        _state = memento->GetState();
    }
    Memento* CreateMemento() {
        return new Memento(_state);
    }

protected:
    std::string _state;
};

class Caretaker {
public:
    Caretaker() {}
    virtual ~Caretaker() {}
    int MementoCount() const {
        return _mementos.size();
    }
    void AddMemento(Memento* memento) {
        _mementos.push_back(memento);
    }
    Memento* GetMemento(int index) const {
        return _mementos[index];
    }
private:
    std::vector<Memento*> _mementos;
};

int main(int argc, char* argv[]) {
    Caretaker* caretaker = new Caretaker();
    Originator* originator = new Originator();
    originator->SetState("First State");
    originator->PrintState();
    caretaker->AddMemento(originator->CreateMemento());

    originator->SetState("Second State");
    originator->PrintState();
    caretaker->AddMemento(originator->CreateMemento());

    originator->SetState("Third State");
    originator->PrintState();
    caretaker->AddMemento(originator->CreateMemento());

    originator->SetMemento(caretaker->GetMemento(0));
    originator->PrintState();
    return 0;
}