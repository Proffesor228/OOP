#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct WORKER {
	double SALARY=0;
	int YEAR=0;
	string NAME;
	string POS;
};

static void dlina()
{
	string s1; bool cmp = 0;
	cout << "\nЕсли захотите завершить программу, запишите в конце строки слово quit\n";
	while (cmp != 1)
	{
		cout << "\nВедите строку: "; getline(cin, s1);
		cout << "Длина строки: " << s1.length();
		if (s1.length() >= 4) if (s1[s1.length() - 4] == 'q')
		{
			if (s1[s1.length() - 3] == 'u' && s1[s1.length() - 2] == 'i' && s1[s1.length() - 1] == 't') cmp = 1;
		}
	}
	return;
}
static void task2()
{
	ifstream file("stroki.txt");
	ofstream nfile("nstroki.txt");
	if (!file) { cout << "Ошибка!"; return; }
	cout << "Файлы успешно открыты\n";
	string ss;
	while (getline(file, ss)) {
		string s2;
		for (size_t i = 0; i <= ss.length(); i++)
		{
			if (ss[i] == '!') s2 += '?';
			s2 += ss[i];
		}
		nfile << s2 << "\n";
	}
	cout << "Перед каждым ! поставлен знак ? (смотрите в nstroki.txt)";
	file.close();
	nfile.close();
	return;
}
static void task3()
{

	struct WORKER tabl[10];
	int stazh, kolvo = 0;

	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << ".\n";
		cout << "  Оклад: "; cin >> tabl[i].SALARY;
		cout << "  Год поступления: "; cin >> tabl[i].YEAR;
		cout << "  ФИО: "; cin >> tabl[i].NAME;
		cout << "  Занимаемая должность: "; cin >> tabl[i].POS;
	}

	cout << "\nПоиск по стажу больше чем: "; cin >> stazh;
	for (int d = 0; d < 10; d++)
	{
		if (2025 - tabl[d].YEAR > stazh)
		{
			cout << "\n" << d + 1 << ".\n";
			cout << "  Оклад: " << tabl[d].SALARY;
			cout << "\n  Год поступления: " << tabl[d].YEAR;
			cout << "\n  ФИО: " << tabl[d].NAME;
			cout << "\n  Занимаемая должность: " << tabl[d].POS;
			kolvo = 1;
		}
	}
	if (kolvo == 0) cout << "\nТаких работников не найдено.\n";
}

void main()
{
	system("chcp 1251");
	dlina();
	cout << "\n\n";
	task2();
	cout << "\n\n";
	task3();
}