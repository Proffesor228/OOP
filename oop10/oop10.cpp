#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include <cmath>
#include <algorithm>
#include <locale.h>

using namespace std;

mutex mtx;


void configure_console() {
    SetConsoleOutputCP(CP_UTF8); 
    system("cls"); 
}

int gcd(int x, int y) {
    while (x != y) {
        if (x > y) x -= y;
        else y -= x;
    }
    return x;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (gcd(n, i) != 1) {
            return false;
        }
    }
    return true;
}

void find_primes(int start, int end, vector<int>& primes, int thread_id, int priority) {
    SetThreadPriority(GetCurrentThread(), priority);

    vector<int> local_primes;
    int last_progress = -1; 
    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            local_primes.push_back(num);
        }

        int progress = (num - start) * 50 / (end - start);
        if (progress != last_progress && progress % 5 == 0) { 
            mtx.lock();
            COORD pos = { 0, static_cast<SHORT>(thread_id + 1) };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            cout << u8"Поток " << thread_id << ": [";
            for (int i = 0; i < 50; i++) {
                cout << (i <= progress ? u8"▓" : u8" ");
            }
            cout << "] " << (progress * 2) << u8"%";
            mtx.unlock();
            last_progress = progress;
        }
    }
    lock_guard<mutex> lock(mtx);
    primes.insert(primes.end(), local_primes.begin(), local_primes.end());
}

int main() {
    configure_console(); 

    int range_start, range_end, num_threads;

    cout << u8"Введите начало диапазона: ";
    cin >> range_start;
    cout << u8"Введите конец диапазона: ";
    cin >> range_end;
    cout << u8"Введите количество потоков: ";
    cin >> num_threads;

    vector<thread> threads;
    vector<int> primes;
    vector<int> priorities(num_threads);

    for (int i = 0; i < num_threads; i++) {
        cout << u8"Введите приоритет потока " << i << " (1-низкий, 2-нормальный, 3-высокий): ";
        cin >> priorities[i];
    }

    system("cls");
    cout << u8"Поиск простых чисел в диапазоне " << range_start << u8" - " << range_end << endl;

    int chunk_size = (range_end - range_start + 1) / num_threads;

    for (int i = 0; i < num_threads; i++) {
        int start = range_start + i * chunk_size;
        int end = (i == num_threads - 1) ? range_end : start + chunk_size - 1;

        int sys_priority;
        switch (priorities[i]) {
        case 1: sys_priority = THREAD_PRIORITY_BELOW_NORMAL; break;
        case 2: sys_priority = THREAD_PRIORITY_NORMAL; break;
        case 3: sys_priority = THREAD_PRIORITY_ABOVE_NORMAL; break;
        default: sys_priority = THREAD_PRIORITY_NORMAL;
        }

        threads.emplace_back(find_primes, start, end, ref(primes), i, sys_priority);
    }

    for (auto& t : threads) {
        t.join();
    }

    sort(primes.begin(), primes.end());

    system("cls");
    cout << u8"\nНайдено простых чисел: " << primes.size() << endl;
    cout << u8"Список простых чисел:\n";

    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}