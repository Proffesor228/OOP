#include <cassert>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
// Задача 1
struct Expression
{
public:
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
// Задача 2
struct FunctionCall : Expression
{

    FunctionCall(string name,Expression* arg)
    {
        this->namen = name;
        this->argn = arg;
    }
    double evaluate() const override
    {
        double arg = argn->evaluate();
        if (name() == "abs") return abs(arg);
        if (name() == "sqrt") return sqrt(arg);
        return 0.0;
    }
    std::string const& name() const
    {
        return namen;
    }
    Expression const* arg() const
    {
        return argn;
    }
    ~FunctionCall() { 
        delete argn;
    }
private:
    string namen;
    Expression* argn;
};


// Задача 3
class Coordinate {
public:
    virtual ~Coordinate() {}
    virtual void Print() const = 0; 
    virtual void toSpherical(double& r, double& theta, double& phi) const = 0;
    virtual void toCylindrical(double& r, double& theta, double& zCoord) const = 0;
    virtual void toCartesian(double& x, double& y, double& z) const = 0;
};

class CartesianCoordinate : public Coordinate {
private:
    double x, y, z; 

public:
    CartesianCoordinate(double x, double y, double z) : x(x), y(y), z(z) {}

    void Print() const override {
        cout << "Декартовы координаты: (" << x << " " << y << " " << z << ")" << endl;
    }

    void toSpherical(double& r, double& theta, double& phi) const override {
        r = sqrt(x * x + y * y + z * z);
        theta = atan2(y, x);
        phi = acos(z / r);
    }

    void toCylindrical(double& r, double& theta, double& zCoord) const override {
        r = sqrt(x * x + y * y);
        theta = atan2(y, x);
        zCoord = z;
    }

    void toCartesian(double& x, double& y, double& z) const override
    {
        x = this->x;
        y = this->y;
        z = this->z;
    }
};

class SphericalCoordinate : public Coordinate {
private:
    double r, theta, phi; 

public:
    SphericalCoordinate(double r, double theta, double phi) : r(r), theta(theta), phi(phi) {}

    void Print() const override {
        cout << "Сферические координаты: (r: " << r << ", theta: " << theta << ", phi: " << phi << ")" << endl;
    }
    void toSpherical(double& r, double& theta, double& phi) const override {
        r = this->r;
        theta = this->theta;
        phi = this->phi;
    }

    void toCartesian(double& x, double& y, double& z) const override {
        x = r * sin(phi) * cos(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(phi);
    }
    void toCylindrical(double& r, double& theta, double& zCoord) const override {
        r = this->r * sin(phi);
        theta = this->theta;
        zCoord = this->r * cos(phi);
    }
};

class CylindricalCoordinate : public Coordinate {
private:
    double r, theta, z; 

public:
    CylindricalCoordinate(double r, double theta, double z) : r(r), theta(theta), z(z) {}

    void Print() const override {
        std::cout << "Цилиндрические координаты: (r: " << r << ", theta: " << theta << ", z: " << z << ")" << endl;
    }
    void toCylindrical(double& r, double& theta, double& z) const override {
        r = this->r;
        theta = this->theta;
        z = this->z;
    }

    void toCartesian(double& x, double& y, double& z) const override{
        x = r * cos(theta);
        y = r * sin(theta);
        z = this->z;
    }
    void toSpherical(double& r, double& theta, double& phi) const override {
        r = sqrt(this->r * this->r + z * z);
        theta = this->theta;
        phi = atan2(z, this->r);
    }
};



int main()
{
    system("chcp 1251");

    int num;
    cout << "Введите задачу для проверки: "; cin >> num;

    switch (num)
    {
    case 1: 
    {
        Expression* e1 = new Number(1.234);
        Expression* e2 = new Number(-1.234);
        Expression* e3 = new BinaryOperation(e1,

            BinaryOperation::DIV, e2);

        cout << e3->evaluate() << endl;

        delete e1;
        delete e2;
        delete e3;
        break;
    }
    case 2:
    {
        Expression* n32 = new Number(32.0);
        Expression* n16 = new Number(16.0);
        Expression* minus = new BinaryOperation(n32, BinaryOperation::MINUS, n16);
        Expression* callSqrt = new FunctionCall("sqrt", minus);
        Expression* n2 = new Number(2.0);
        Expression* mult = new BinaryOperation(n2, BinaryOperation::MUL, callSqrt);
        Expression* callAbs = new FunctionCall("abs", mult);
        cout << callAbs->evaluate() << endl;

        delete n32;
        delete n16;
        delete minus;
        delete callSqrt;
        delete n2;
        delete mult;
        delete callAbs;

        break;
    }
    default: return 0;
    }
    return 0;
}