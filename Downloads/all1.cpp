#include <iostream>
using namespace std;

void Srednee(int n, const int a[]) {
    int s = 0;
    for(int i = 0; i < n; ++i) {
        s += a[i];
    }
    int ans = (double)s / n * 10;
    double res = (double)ans / 10;
    cout << res << "\n";
}
void MaxMin(int n, const int a[]) {
    int min = 0;
    int max = 0;
    for(int i = 0; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
        if (a[i] > max) {
            max = a[i];
        }
    }
    cout << min << " " << max << "\n";
}
void Counter(int n, const int a[]) {
    int c = 0;
    for(int i = 0; i < n; ++i) {
        if (a[i] < 0) {
            c += 1;
        }
    }
    cout << c << "\n";
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    Srednee(n, a);
    MaxMin(n, a);
    Counter(n, a);
    delete[] a;
    return 0;
}