#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
#include <cstddef>


template <typename T>
class AArray
{ private:
    T* myArray;
    size_t n;
public:
    // Список операций:
    explicit AArray(size_t size, const T& value = T())
    {  
        n = size;
        if (n > 0)
        {
            myArray = new T[size];

            for (int i = 0; i < size; i++)
            {
                myArray[i] = value;
            }
        }
        else myArray = nullptr;
    }
    AArray(const AArray& mas)  
    {
        this->n = mas.n;
        if (n > 0)
        {
            this->myArray = new T[n];

            for (int i = 0; i < mas.n; i++)
            {
                this->myArray[i] = mas.myArray[i];
            }
        }
        else myArray = nullptr;
    }
    ~AArray()
    {
        delete[] myArray;
    }
    AArray& operator=(const AArray& mas)
    {
        delete[] myArray;
        this->n = mas.n;
        for (int i = 0; i < mas.n; i++)
        {
            this->myArray[i] = mas.myArray[i];
        }
    }
    T& operator[](size_t idx)
    {
        return myArray[idx];
    }
    const T& operator[](size_t idx) const
    {
        return myArray[idx];
    }
    size_t size() const { return n; }
};

template <typename T>
class Array {
private:
    T* myArray;  
    size_t n;

public:
    
    explicit Array(size_t size = 0, const T& value = T()) : n(size) {
        if (n > 0) {
            myArray = static_cast<T*>(::operator new(n * sizeof(T)));  
            for (size_t i = 0; i < n; i++) {
                new (&myArray[i]) T(value);  
            }
        }
        else {
            myArray = nullptr;
        }
    }

    Array(const Array& other) : n(other.n) {
        if (n > 0) {
            myArray = static_cast<T*>(::operator new(n * sizeof(T)));
            for (size_t i = 0; i < n; ++i) {
                new (&myArray[i]) T(other.myArray[i]); 
            }
        }
        else {
            myArray = nullptr;
        }
    }

 
    ~Array() {
        if (myArray) {
            for (size_t i = 0; i < n; i++) {
                myArray[i].~T();  
            }
            ::operator delete(myArray);  
        }
    }

    Array& operator=(Array other) {
        swap(other);
        return *this;
    }

    void swap(Array& other) noexcept {
        swap(myArray, other.myArray);
        swap(n, other.n);
    }

    T& operator[](size_t idx) {
        return myArray[idx];
    }

    const T& operator[](size_t idx) const {
        return myArray[idx];
    }

    size_t size() const {
        return n;
    }
};

class Student
{
private:
    string name;
    int nomer;
public:
    Student()
    {
        name = "-";
        nomer = 0;
    }
    Student(string name, int nomer)
    {
        this->name = name;
        this->nomer = nomer;
    }
    Student(const Student& other) : name(other.name), nomer(other.nomer) {}
    void Print() const
    {
        cout << "Student: " << name << "\tNumber: " << nomer << endl;
    }
    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            nomer = other.nomer;
        }
        return *this;
    }

};

struct ICloneable {
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() {}
};

template <typename T>
struct ValueHolder : public ICloneable {

    T data_;  

    ValueHolder(const T& value) : data_(value) {}
    ICloneable* clone() const override {
        return new ValueHolder(data_);
    }

    ~ValueHolder() override = default;
};

template <typename T, typename U>
void copy_nn(T* mas1, const U* mas2, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        mas1[i] = static_cast<T>(mas2[i]);
    }
}

bool lesss(int a, int b)
{
    return a < b;
}

struct Greater {
    bool operator()(int a, int b) const { return b < a; }
};

template <typename T, typename Comparator>
T minimum(const Array<T>& array, Comparator comp) {
    if (array.size() == 0) {
        throw invalid_argument("Empty array");
    }

    T min_elem = array[0];
    for (size_t i = 1; i < array.size(); ++i) {
        if (comp(array[i], min_elem)) {
            min_elem = array[i];
        }
    }
    return min_elem;
}

template <typename T>
void flatten_i(const T& elem, ostream& out) {
    out << elem << " ";
}

template <typename T>
void flatten_i(const Array<T>& arr, ostream& out) {
    for (size_t i = 0; i < arr.size(); ++i) {
        flatten_i(arr[i], out);  
    }
}

template <typename T>
void flatten(const Array<T>& arr, ostream& out = cout) {
    flatten_i(arr, out);
    out << std::endl;  
}

class Any {
private:
    ICloneable* holder; 

public:
    Any() : holder(nullptr) {}

    template <typename T>
    Any(const T& value) : holder(new ValueHolder<T>(value)) {}

    Any(const Any& other) : holder(other.holder ? other.holder->clone() : nullptr) {}

    ~Any() {
        delete holder;
    }

    Any& operator=(const Any& other) {
        if (this != &other) {
            delete holder;
            holder = other.holder ? other.holder->clone() : nullptr;
        }
        return *this;
    }

    template <typename T>
    Any& operator=(const T& value) {
        delete holder;
        holder = new ValueHolder<T>(value);
        return *this;
    }

    template <typename T>
    T* cast() {
        if (!holder) return nullptr;
        ValueHolder<T>* s_holder = dynamic_cast<ValueHolder<T>*>(holder);
        return s_holder ? &s_holder->data_ : nullptr;
    }

    template <typename T>
    const T* cast() const {
        if (!holder) return nullptr;
        const ValueHolder<T>* s_holder = dynamic_cast<const ValueHolder<T>*>(holder);
        return s_holder ? &s_holder->data_ : nullptr;
    }
};

template <typename T, typename U>
struct SameType {
    static const bool value = false;
};

template <typename T>
struct SameType<T, T> {
    static const bool value = true;
};

template <typename T, size_t N>
size_t array_size(T(&array)[N]) {
    return N;
}

void analyzeCode(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    string line;
    int lineN = 0;
    bool foundForLoop = false;

    regex forReg(R"(\bfor\s*\()");

    while (getline(file, line))
    {
        lineN++;

        if (regex_search(line, forReg))
        {
            foundForLoop = true;
            cout << "Цикл for найден на строке " << lineN << ": " << line << endl;
        }
    }

    if (!foundForLoop) {
        cout << "Циклы for не найдены." << endl;
    }

    file.close();
}


int main() {

    system("chcp 1251");


    // 1
    /*string filename;
    cout << "Введите имя файла для анализа: ";
    cin >> filename;
    analyzeCode(filename);*/


    //2
    //Student anton("Anokhin", 895123);
    //anton.Print();

    //Array<Student> a(5, anton);
    //Student b = a[3];
    //b.Print();

    //4
    //int ints[] = { 1, 2, 3, 4 };
    //double doubles[4] = {};
    //copy_nn(doubles, ints, 4);
    //cout << doubles[2]/2;

    //5
    //Array<int> ints(3);
    //ints[0] = 10;
    //ints[1] = 2;
    //ints[2] = 15;

    //int min = minimum(ints, lesss);          // вернет 2
    //int max = minimum(ints, Greater());     // вернет 15

    //cout << min << max << endl;

    //6
   /* Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints);

    Array<Array<int>> array_of_ints(2, ints);
    flatten(array_of_ints); */

    //7
   /* Any a(10);                 
    Any b = std::string("test"); 
    Any c = a;                

    int* i = a.cast<int>();    
    std::string* s = b.cast<std::string>(); 

    a = 3.14;                 
    double* d = a.cast<double>(); */

    //8
 /*   struct Dummy {};
    typedef int type;

    std::cout << SameType<int, int>::value;           
    std::cout << SameType<int, type>::value;          
    std::cout << SameType<int, int&>::value;          
    std::cout << SameType<Dummy, Dummy>::value;       
    std::cout << SameType<int, const int>::value;*/

    //9
    //int ints[] = { 1, 2, 3, 4 };
    //int* iptr = ints;
    //double doubles[] = { 3.14 };
    //cout << array_size(ints); // вернет 4
    //cout << array_size(doubles); // вернет 1



}