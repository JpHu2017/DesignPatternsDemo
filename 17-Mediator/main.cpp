#include <iostream>
#include <string>

// 中介者
class Colleague;
class Mediator {
public:
    Mediator() {}
    virtual ~Mediator() {}
    virtual void SendMsg(Colleague* colleague, const std::string& msg) = 0;
};

// 同事类
class Colleague {
public:
    Colleague(Mediator* mediator) : _mediator(mediator) {}
    virtual ~Colleague() {}
    virtual void SendMsg(const std::string& msg) = 0;
    virtual void ReceiveMsg(const std::string& msg) = 0;
protected:
    Mediator* _mediator;
};

class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(Mediator* mediator) 
        : Colleague(mediator) {}
    virtual ~ConcreteColleague1() {}
    void SendMsg(const std::string& msg) override {
        _mediator->SendMsg(this, msg);
    }
    void ReceiveMsg(const std::string& msg) override {
        std::cout << "Colleague1 receive msg: " << msg << std::endl;
    }
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(Mediator* mediator)
        : Colleague(mediator) {}
    virtual ~ConcreteColleague2() {}
    void SendMsg(const std::string& msg) override {
        _mediator->SendMsg(this, msg);
    }
    void ReceiveMsg(const std::string& msg) override {
        std::cout << "Colleague2 receive msg: " << msg << std::endl;
    }
};

class ConcreteMediator : public Mediator {
public:
    ConcreteMediator() {}
    virtual ~ConcreteMediator() {}
    void SendMsg(Colleague* colleague, const std::string& msg) override {
        if (colleague == _colleage1) {
            _colleage2->ReceiveMsg(msg);
        } else if (colleague == _colleage2) {
            _colleage1->ReceiveMsg(msg);
        }
    }
    void setColleague1(Colleague* colleague1) {
        _colleage1 = colleague1;
    }
    void setColleague2(Colleague* colleague2) {
        _colleage2 = colleague2;
    }
private:
	Colleague *_colleage1;
	Colleague *_colleage2;
};

int main(int argc, char* argv[]) {
    ConcreteMediator* mediator = new ConcreteMediator();
    Colleague* colleague1 = new ConcreteColleague1(mediator);
    Colleague* colleague2 = new ConcreteColleague2(mediator);
    mediator->setColleague1(colleague1);
    mediator->setColleague2(colleague2);
    colleague1->SendMsg("Hello from colleague1");
    colleague2->SendMsg("Hello from colleague2");
    return 0;
}
