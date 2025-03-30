#include <iostream>
#include <cmath>

using namespace std;

class quadrangle
{
protected:

	int a;
	int b;
	int c;
	int d;

public:

	quadrangle()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
	}
	quadrangle(int a,int b,int c,int d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	void Print() const
	{
		cout << a << " " << b << " " << c << " " << d << endl;
	}


	int Perimetr() const
	{
		int sum = a + b + c + d;
		return sum;
	}

	void SetA(int a)
	{
		this->a = a;
	}
	void SetB(int b)
	{
		this->b = b;
	}
	void SetC(int c)
	{
		this->c = c;
	}
	void SetD(int d)
	{
		this->d = d;
	}

	int GetA() const
	{
		return a;
	}
	int GetB() const
	{
		return b;
	}
	int GetC() const
	{
		return c;
	}
	int GetD() const
	{
		return d;
	}
};

class trapezoid : public quadrangle
{
protected:
	double sredlin;
	double visota;
public:
	trapezoid()
	{
		sredlin = 0;
		visota = 0;
	}
	trapezoid(int a, int b, int c, int d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		sredlin = (a + b) / 2.0;
		visota = sqrt(pow(c, 2) - (pow(a - b, 2) + pow(c, 2) - pow(d, 2)) / (2 * (a - b)));
	}

	double Square() const
	{
		return visota * sredlin;
	}

	int GetSredLin() const
	{
		return sredlin;
	}
	int GetVisota() const
	{
		return visota;
	}
};

class parallelogram : public trapezoid
{
private:
	double angle;
public:
	parallelogram()
	{
		angle = 0;
	}
	parallelogram(int a,int c)
	{
		this->a = a;
		b = a;
		this->c = c;
		d = c;
		angle = 0.7854;
		visota = this->c * sin(angle);
		sredlin = a;
	}
	parallelogram(int a, int c,double angle)
	{
		this->a = a;
		b = a;
		this->c = c;
		d = c;
		this -> angle = angle;
		visota = this->c * sin(this->angle);
		sredlin = a;
	}

	double Square()
	{
		return visota * a;
	}

	int GetAngle() const
	{
		return angle;
	}

	void SetA(int a)
	{
		this->a = a;
		b = a;
	}
	void SetB(int b)
	{
		this->b = b;
		a = b;
	}
	void SetC(int c)
	{
		this->c = c;
		d = c;
	}
	void SetD(int d)
	{
		this->d = d;
		c = d;
	}
};



int main()
{
	system("chcp 1251");

	quadrangle quad1(1,2,3,4);
	quadrangle quad2;
	quad1.Print();
	cout << "Периметр: " << quad1.Perimetr() << endl << endl;

	trapezoid trap1(7, 2, 3, 4);
	trapezoid trap2;
	trap1.Print();
	cout << "Периметр: " << trap1.Perimetr() << endl;
	cout << "Площадь: " << trap1.Square() << endl<<endl;

	parallelogram par1(7, 5);
	parallelogram par2(7, 5, 0.8);
	parallelogram par3;
	par1.Print();
	cout << "Периметр: " << par1.Perimetr() << endl;
	cout << "Площадь: " << par1.Square() << endl;
	cout << par1.GetVisota() << endl;
}