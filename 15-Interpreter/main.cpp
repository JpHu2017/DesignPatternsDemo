#include <iostream>
#include <map>
#include <memory>
#include <stack>

class Expression {
public:
    using Ptr = std::shared_ptr<Expression>;
    Expression() {}
    virtual ~Expression() {}
    virtual int Interpreter(std::map<char, int> var) = 0;
};

//变量表达式
class VarExpression : public Expression {
public:
    VarExpression(const char& key) : _key(key) {}
    virtual ~VarExpression() {}
    int Interpreter(std::map<char, int> var) override {
        return var.at(_key);
    }
private:
    char _key;
};

// 符号表达式
class SymbolExpression : public Expression {
public:
    SymbolExpression(Expression::Ptr left, Expression::Ptr right) :
        _left(left), _right(right) {
    }
    virtual ~SymbolExpression() {}
protected:
    Expression::Ptr _left;
    Expression::Ptr _right;
};
//加法运算
class AddExpression : public SymbolExpression {
public:
    AddExpression(Expression::Ptr left, Expression::Ptr right) :
        SymbolExpression(left, right) {
    }
    virtual ~AddExpression() {}
    int Interpreter(std::map<char, int> var) override {
        return _left->Interpreter(var) + _right->Interpreter(var);
    }
};
//减法运算
class SubExpression : public SymbolExpression {

public:
    SubExpression(Expression::Ptr left, Expression::Ptr right) :
        SymbolExpression(left, right) {
    }
    virtual ~SubExpression() {}
    int Interpreter(std::map<char, int> var) override {
        return _left->Interpreter(var) - _right->Interpreter(var);
    }

};

Expression::Ptr analyse(const std::string& expStr) {
    std::stack<Expression::Ptr> expStack;
    Expression::Ptr left = nullptr;
    Expression::Ptr right = nullptr;
    for (int i = 0; i < expStr.size(); i++) {
        switch (expStr[i]) {
        case '+': // 加法运算
            left = expStack.top();
            right.reset(new VarExpression(expStr[++i]));
            expStack.push(std::make_shared<AddExpression>(left, right));
            break;
        case '-': // 减法运算
            left = expStack.top();
            right.reset(new VarExpression(expStr[++i]));
            expStack.push(std::make_shared<SubExpression>(left, right));
            break;
        default: // 变量表达式
            expStack.push(std::make_shared<VarExpression>(expStr[i]));
        }
    }
    Expression::Ptr expression = expStack.top();
    return expression;
}

int main() {
    std::string expStr = "a+b-c+d-e";
    std::map<char, int> var;
    var.insert(std::make_pair('a', 5));
    var.insert(std::make_pair('b', 2));
    var.insert(std::make_pair('c', 1));
    var.insert(std::make_pair('d', 6));
    var.insert(std::make_pair('e', 10));

    Expression::Ptr expression = analyse(expStr);
    int result = expression->Interpreter(var);
    std::cout << result << std::endl;
    return 0;
}