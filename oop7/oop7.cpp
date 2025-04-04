#include <cassert>
#include <iostream>

using namespace std;

struct Expression
{
    virtual ~Expression() {}
    virtual double evaluate() const = 0; 
};

struct Number : Expression
{
    Number(double value) : value_(value) {}

    double value() const { return value_; }
    double evaluate() const override { return value_; }

private:
    double value_;
};

struct BinaryOperation : Expression
{
    enum { PLUS = '+', MINUS = '-', DIV = '/', MUL = '*' };

    BinaryOperation(Expression* left, int op, Expression* right)
        : left_(left), op_(op), right_(right)
    {
        assert(left_ && right_);
        assert(right_);
    }

    ~BinaryOperation()
    {
        cout << 5 << endl;
        delete left_; 
        delete right_; 
    }

    double evaluate() const override
    {
        double left = left_->evaluate();
        double right = right_->evaluate();
        switch (op_)
        {
        case PLUS: return left + right;
        case MINUS: return left - right;
        case DIV: return left / right;
        case MUL: return left * right;
        }
        assert(0); 
        return 0.0; 
    }

private:
    Expression* left_; 
    Expression* right_; 
    int op_; 
};

int main()
{
    
      Expression* e1 = new Number(1.234);
      Expression* e2 = new Number(-1.234);
      Expression* e3 = new BinaryOperation(e1,BinaryOperation::DIV, e2);

        cout << e3->evaluate() << endl;

        delete e2;
        delete e1;
        delete e3;
    
    return 0;
}