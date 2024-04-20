#include <iostream>
#include <memory>
#include <string>

class Command {
public:
    using Ptr = std::shared_ptr<Command>;
    Command() {}
    virtual ~Command() {}
    virtual void Execute() = 0;
};

class Receiver {
public:
    Receiver() {}
    virtual ~Receiver() {}
    void Action() {
        std::cout << "Do something!" << std::endl;
    }
};

class ConcreteCommand : public Command {
public:
    ConcreteCommand() : Command() {}
    virtual ~ConcreteCommand() {}
    void Execute() override {
        _rcv.Action();
    }
protected:
    Receiver _rcv;
};

// use it!
int main() {
    Command::Ptr cmd(new ConcreteCommand());
    cmd->Execute();
    return 0;
}