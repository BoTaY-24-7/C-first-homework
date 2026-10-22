/*
Программа считывает четырёхмерную матрицу (blocks x layers x rows x cols).
Если полученный элемент не является натуральным числом, ячейка заполняется нулём. 
Выводится полученная матрица. После ввода выполняется быстрая перестановка двух 
слоёв внутри выбранного блока и изменённая матрица также выводится.

Зачем здесь int***:
matrix[b] имеет тип int*** (трёхмерный подмассив).
Чтобы переставить два слоя внутри блока b за время O(1), мы берём указатель
int*** target_block = matrix[b] и меняем местами адреса слоёв (int**). При использовании 
статического массива данная операция обошлась бы в O(n), где n - количество чисел в 
слое (layers * rows * cols).

Зачем здесь void*:
Используется для считывания элемента, тип которого мы заранее не знаем (в этой задаче 
проверяется только int или char, но можно было так же проверять, является ли double).
Перед записью в матрицу void* приводится через static_cast<int*> (после проверки, 
что это правда int) и разыменовывается.
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int blocks, layers, rows, cols;
    cin >> blocks >> layers >> rows >> cols;
    if (blocks <= 0 || layers <= 0 || rows <= 0 || cols <= 0) {
        cout << "Ошибка, некорректные размеры\n";
        return 0;
    }

    int**** matrix = new int***[blocks];
    for (int b = 0; b < blocks; ++b) {
        matrix[b] = new int**[layers];
        for (int k = 0; k < layers; ++k) {
            matrix[b][k] = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                matrix[b][k][i] = new int[cols];
            }
        }
    }

    for (int b = 0; b < blocks; ++b) {
        for (int k = 0; k < layers; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    string elmt;
                    cin >> elmt;

                    bool IsNumber = true;
                    if (elmt.empty() || elmt[0] == '0') {
                        IsNumber = false;
                    } else {
                        for (size_t p = 0; p < elmt.length(); ++p) {
                            if (elmt[p] < '0' || elmt[p] > '9') {
                                IsNumber = false;
                                break;
                            }
                        }
                    }

                    void* ptr = nullptr;
                    bool PtrIsInt = false;

                    if (IsNumber) {
                        ptr = new int(stoi(elmt));
                        PtrIsInt = true;
                    } else {
                        ptr = new string(elmt);
                        PtrIsInt = false;
                    }

                    if (PtrIsInt) {
                        int* int_ptr = static_cast<int*>(ptr);
                        matrix[b][k][i][j] = *int_ptr;
                        delete int_ptr;
                    } else {
                        matrix[b][k][i][j] = 0;
                    }
                }
            }
        }
    }

    int target_block_num, layer1, layer2;
    if (cin >> target_block_num >> layer1 >> layer2) {
        int b = target_block_num - 1;
        int l1 = layer1 - 1;
        int l2 = layer2 - 1;

        if (b >= 0 && b < blocks && l1 >= 0 && l1 < layers && l2 >= 0 && l2 < layers) {
            int*** target_block = matrix[b];
            int** temp = target_block[l1];
            target_block[l1] = target_block[l2];
            target_block[l2] = temp;
        } else {
            cout << "Некорректные индексы\n";
        }
    }

    for (int b = 0; b < blocks; ++b) {
        cout << "=== Блок " << b + 1 << " ===\n";
        for (int k = 0; k < layers; ++k) {
            cout << "--- Слой " << k + 1 << " ---\n";
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    cout << matrix[b][k][i][j] << "\t";
                }
                cout << "\n";
            }
        }
    }

    for (int b = 0; b < blocks; ++b) {
        for (int k = 0; k < layers; ++k) {
            for (int i = 0; i < rows; ++i) {
                delete[] matrix[b][k][i];
            }
            delete[] matrix[b][k];
        }
        delete[] matrix[b];
    }
    delete[] matrix;
    return 0;
}
