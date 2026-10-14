#include <iostream>
using namespace std;

const int strs = 5;
const int rows = 10;

bool Equal(const char k[], const char l[]) {
    int i = 0;
    while (k[i] != '\0' && l[i] != '\0') {
        if (k[i] != l[i]) return false;
        ++i;
    }
    return k[i] == l[i];
}

void Clear(char (&a)[strs][rows]) {
    for (int i = 0; i < strs; ++i) {
        for (int g = 0; g < rows; ++g) {
            a[i][g] = ' ';
        }
    }
    return;
}

void Put(char (&a)[strs][rows], int x, int y, char c) {
    if (!(0 <= x && x < 10 && 0 <= y && y < 5)) {
        cout << "error\n";
    } else {
        a[y][x] = c;
        return;
    }
}

void Text(char (&a)[strs][rows], int x, int y, char c[]) {
    int lenc = 0;
    for (int i = 0; c[i] != '\0'; ++i) {
        lenc += 1;
    }
    if (!(x >= 0 && 0 <= x + lenc && x + lenc <= rows && 0 <= y && y < 5)) {
        cout << "error\n";
    } else {
        for (int i = 0; c[i] != '\0'; ++i) {
            a[y][x+i] = c[i];
        }
    }
    return;
}

void Print(const char (&a)[strs][rows]) {
    for (int i = 0; i < strs; ++i) {
        for (int g = 0; g < rows; ++g) {
            cout << a[i][g];
        }
        cout << "\n";
    }
}

int main() {
    char a[strs][rows];
    char word[16];
    Clear(a);
    while (cin >> word) {
        if (Equal(word, "quit")) {
            break;
        } 
        else if (Equal(word, "clear")) {
            Clear(a);
        } 
        else if (Equal(word, "print")) {
            Print(a);
        } 
        else if (Equal(word, "put")) {
            int x, y;
            char c;
            cin >> x >> y >> c;
            Put(a, x, y, c);
        } else if (Equal(word, "text")) {
            int x, y;
            char c[16];
            cin >> x >> y >> c;
            Text(a, x, y, c);
        }
    }
}