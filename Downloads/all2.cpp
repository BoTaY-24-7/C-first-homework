#include <iostream>
using namespace std;

bool Equal(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        ++i;
    }
    return a[i] == b[i];
}

bool Deposit(long long& balance) {
    long long k;
    cin >> k;
    if (k > 0) {
        balance += k;
    } else {
        cout << "error\n";
    }
    return true;
}

bool Withdraw(long long& balance) {
    long long k;
    cin >> k;
    if (k > 0 && k <= balance) {
        balance -= k;
    } else {
        cout << "error\n";
    }
    return true;
}

bool Balance(long long& balance) {
    cout << balance << "\n";
    return true;
}

bool Reset(long long& balance) {
    balance = 0;
    return true;
}

bool Double(long long& balance) {
    balance *= 2;
    return true;
}

bool Stop(long long&) {
    return false;
}

typedef bool (*ActionFunc)(long long&);

struct Command {
    const char* name;
    ActionFunc action;
};

int main() {
    long long balance = 0;
    const int COMMANDS_COUNT = 6;
    const Command table[COMMANDS_COUNT] = {
        {"deposit",  Deposit},
        {"withdraw", Withdraw},
        {"balance",  Balance},
        {"reset",    Reset},
        {"double",   Double},
        {"stop",     Stop}
    };

    char cmd[32];
    while (cin >> cmd) {
        bool found = false;
        bool should_continue = true;
        
        for (int i = 0; i < COMMANDS_COUNT; ++i) {
            if (Equal(cmd, table[i].name)) {
                should_continue = table[i].action(balance);
                found = true;
                break;
            }
        }

        if (!should_continue) {
            break;
        }

        if (!found) {
            cout << "error\n";
        }
    }
    return 0;
}