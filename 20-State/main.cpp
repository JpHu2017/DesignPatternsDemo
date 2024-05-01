#include <iostream>
#include <list>
#include <memory>
#include <string>
class Context;
class State {
public:
    using Ptr = std::shared_ptr<State>;
    State() {}
    virtual ~State() {}
    virtual void Handle(Context* ctx) = 0;
protected:
    void ChangeState(Context* ctx, State* state);
};

class Context {
public:
    Context(State* state) : _state(state) {}
    virtual ~Context() {}
    void Request() {
        if (_state) {
            _state->Handle(this);
        }
    }
private:
    void ChangeState(State* state) {
        _state = state;
    }
protected:
    friend class State;
    State* _state;
};

class ConcreteStateA : public State {
public:
    ConcreteStateA() {}
    virtual ~ConcreteStateA() {}
    static State* Instance() {
        static ConcreteStateA s_instance;
        return &s_instance;
    }
    void Handle(Context* ctx) override;
};

class ConcreteStateB : public State {
public:
    ConcreteStateB() {}
    virtual ~ConcreteStateB() {}
    static State* Instance() {
        static ConcreteStateB s_instance;
        return &s_instance;
    }
    void Handle(Context* ctx) override;
};

void State::ChangeState(Context* ctx, State* state) {
    ctx->ChangeState(state);
}

void ConcreteStateA::Handle(Context* ctx) {
    std::cout << "State A" << std::endl;
    if (ctx) {
        this->ChangeState(ctx, ConcreteStateB::Instance());
    }
}

void ConcreteStateB::Handle(Context* ctx) {
    std::cout << "State B" << std::endl;
    if (ctx) {
        this->ChangeState(ctx, ConcreteStateA::Instance());
    }
}

int main(int argc, char* argv[]) {
    Context ctx(ConcreteStateA::Instance());
    ctx.Request();
    ctx.Request();
    return 0;
}