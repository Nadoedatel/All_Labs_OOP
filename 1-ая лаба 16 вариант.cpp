#include <iostream>
#include <map>

using namespace std;

namespace containers {

    template <typename T>
    class SparseArr {
    public:
        SparseArr(size_t size) : logicalSize(size) {}

        void set(size_t index, const T& value) {
            if (index >= logicalSize) {
                throw out_of_range("Индекс вне диапазона");
            }
            if (value != T{}) {
                data[index] = value;
            }
            else {
                data.erase(index);
            }
        }

        T get(size_t index) const {
            if (index >= logicalSize) {
                throw out_of_range("Индекс вне диапазона");
            }
            auto it = data.find(index);
            return it != data.end() ? it->second : T{};
        }

        size_t size() const {
            return logicalSize;
        }

        size_t nonZeroCount() const {
            return data.size();
        }

    private:
        size_t logicalSize;
        map<size_t, T> data;
    };

}

int main() {
    setlocale(LC_ALL, "Russian");
    using namespace containers;

    cout << "Введите размер разреженного массива: ";
    size_t size;
    cin >> size;

    SparseArr<int> sparseArray(size);

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Установить значение\n";
        cout << "2. Получить значение\n";
        cout << "3. Показать логический размер массива\n";
        cout << "4. Показать количество ненулевых элементов\n";
        cout << "5. Выход\n";
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            size_t index;
            int value;
            cout << "Введите индекс: ";
            cin >> index;
            cout << "Введите значение: ";
            cin >> value;
            try {
                sparseArray.set(index, value);
                cout << "Значение установлено.\n";
            }
            catch (const out_of_range& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 2: {
            size_t index;
            cout << "Введите индекс: ";
            cin >> index;
            try {
                int value = sparseArray.get(index);
                cout << "Значение по индексу " << index << ": " << value << endl;
            }
            catch (const out_of_range& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            cout << "Логический размер массива: " << sparseArray.size() << endl;
            break;
        }
        case 4: {
            cout << "Количество ненулевых элементов: " << sparseArray.nonZeroCount() << endl;
            break;
        }
        case 5: {
            cout << "Выход из программы.\n";
            return 0;
        }
        default: {
            cout << "Неверная опция. Попробуйте снова.\n";
            break;
        }
        }
    }

    return 0;
}
