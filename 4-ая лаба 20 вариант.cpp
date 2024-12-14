#include <iostream>
#include "SparseArray.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    try {
        SparseArray<int> sparseArray = { 1, 2, 3, 4 };

        cout << "Размер массива: " << sparseArray.getSize() << endl;

        sparseArray.add(5);
        cout << "Добавлен элемент. Размер: " << sparseArray.getSize() << endl;

        sparseArray.remove(nullptr);

    }
    catch (const CustomException& e) {
        cout << "Исключение: " << e.getMessage() << " (код ошибки: " << e.getErrorCode() << ")" << endl;
    }

    return 0;
}
