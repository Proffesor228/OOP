#include <iostream>

using namespace std;

class MemoryErrorException {
public:
    const char* what() const {
        return "Недостаточно памяти для выделения";
    }
};

void allocateMemory(size_t size) {
    int* memory = nullptr;
    try {
        memory = new int[size];

        for (size_t i = 0; i < size; ++i) {
            memory[i] = 0;
        }

        cout << "Память выделена успешно!" << endl;

        delete[] memory;
    }
    catch (...) {
        throw MemoryErrorException();
    }
}

int main() {
    system("chcp 1251");
    try {

        size_t size = 1000000; 
        cout << "Выделение памяти..." << endl;
        allocateMemory(size);
    }
    catch (const MemoryErrorException& ex) {
        cout << "Произошло исключение: " << ex.what() << endl;
    }

    return 0;
}