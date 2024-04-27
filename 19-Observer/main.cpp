#include <algorithm>
#include <iostream>
#include <list>
#include <string>

class Observer {
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void Update() = 0;
};

class Subject {
public:
    Subject() {}
    virtual ~Subject() {}

    void Attach(Observer* observer) {
        _observers.push_back(observer);
    }
    void Detach(Observer* observer) {
        _observers.remove(observer);
    }
    void Notify() {
        for (auto observer : _observers) {
            observer->Update();
        }
    }
    virtual std::string GetState() const {
        return _subjectState;
    }
    virtual void SetState(const std::string& state) {
        _subjectState = state;
    }
protected:
    std::list<Observer*> _observers;
    std::string _subjectState;
};

class ConcreteSubject : public Subject {
public:
    ConcreteSubject() {}
    virtual ~ConcreteSubject() {}

    void SetState(const std::string& state) override {
        _subjectState = "concrete subject state <" + state + ">";
    }
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject* subject) : _subject(subject) {}
    virtual ~ConcreteObserver() {}

    void Update() override {
        _observerState = _subject->GetState();
        std::cout << "Observe subject state: " << _observerState << std::endl;
    }
protected:
    Subject* _subject;
    std::string _observerState;
};

int main(int argc, char* argv[]) {
    Subject* subject = new ConcreteSubject();
    Observer* observer = new ConcreteObserver(subject);
    subject->Attach(observer);
    subject->SetState("state 1");
    subject->Notify();
    return 0;
}