#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Deposit(int& balance) {
    int k;
    cin >> k;
    if (k > 0) {
        balance += k;
    } else {
        cout << "error\n";
    }
}

void Withdraw(int& balance) {
    int k;
    cin >> k;
    if (k > 0 && k <= balance) {
        balance -= k;
    } else {
        cout << "error\n";
    }
}

void Balance(int& balance) {
    cout << balance << "\n";
}

void Reset(int& balance) {
    balance = 0;
}

void Double(int& balance) {
    balance *= 2;
}

int main() {
    int balance = 0;

    vector<pair<string, void (*)(int&)>> table = {
        {"deposit",  Deposit},
        {"withdraw", Withdraw},
        {"balance",  Balance},
        {"reset",    Reset},
        {"double",   Double}
    };

    string cmd;
    while (cin.width(32), cin >> cmd) {
        if (cmd == "stop") {
            break;
        }

        void (*func)(int&) = nullptr;
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[i].first == cmd) {
                func = table[i].second;
                break;
            }
        }

        if (func != nullptr) {
            func(balance);
        } else {
            cout << "error\n";
        }
    }
    return 0;
}