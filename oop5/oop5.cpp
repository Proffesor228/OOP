#include <iostream>
#include <cmath>
using namespace std;

class Triangle
{
private:
	int a;
	int b;
	int c;
public:
	Triangle()
	{
		a = 0;
		b = 0;
		c = 0;
	}
	Triangle(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	void Print() const
	{
		cout << a << " " << b << " " << c;
	}
	int Perimetr() const
	{
		return a+b+c;
	}
	double Square() const
	{
		double p = Perimetr()/2.0;
		double square = sqrt(p*(p-a)*(p-b)*(p-c));
		return square;
	}
	int operator[](unsigned index) const
	{
		switch (index)
		{
		case(0): return a;
		case(1): return b;
		case(2): return c;
		default: { cout << "Ошибка!"; return 0; }
		}
	}

	void operator++() 
	{
		a++;
		b++;
		c++;
	}
	void operator--()
	{
		a--;
		b--;
		c--;
	}
	void operator*(int x)
	{
		a *= x;
		b *= x;
		c *= x;
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
	bool Real() const
	{
		if (a + b <= c || a + c <= b || b + c <= a) return false;
		else return true;
	}
};

int main()
{
	system("chcp 1251");
	Triangle t1(3,4,5);
	t1 * 5;
	t1.Print();
}