#include <iostream>
#include <cstdlib>  // Для функции exit()

using namespace std;

template <typename T>
class IPtrArr {
private:
    T* ptr;
    unsigned int* ref_count;
    size_t size;

    void addRef() {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete[] ptr;
            delete ref_count;
        }
    }

public:
    IPtrArr() : ptr(nullptr), ref_count(new unsigned int(0)), size(0) {}

    IPtrArr(size_t sz) : ptr(new T[sz]), ref_count(new unsigned int(1)), size(sz) {}

    IPtrArr(const IPtrArr<T>& other) : ptr(other.ptr), ref_count(other.ref_count), size(other.size) {
        addRef();
    }

    IPtrArr<T>& operator=(const IPtrArr<T>& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            size = other.size;
            addRef();
        }
        return *this;
    }

    ~IPtrArr() {
        release();
    }

    T& operator[](size_t index) {
        if (index >= size) {
            cerr << "Ошибка: Индекс выходит за границы массива!" << endl;
            exit(1);
        }
        return ptr[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            cerr << "Ошибка: Индекс выходит за границы массива!" << endl;
            exit(1);
        }
        return ptr[index];
    }

    size_t getSize() const {
        return size;
    }

    unsigned int getRefCount() const {
        return *ref_count;
    }
};

int main() {
    setlocale(0, "ru");
    size_t n;
    cout << "Введите размер массива: ";
    cin >> n;

    IPtrArr<int> arr(n);

    for (size_t i = 0; i < arr.getSize(); ++i) {
        cout << "Введите элемент " << i << ": ";
        cin >> arr[i];
    }

    cout << "Элементы массива: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    IPtrArr<int> arr_copy = arr;
    cout << "Копия массива: ";
    for (size_t i = 0; i < arr_copy.getSize(); ++i) {
        cout << arr_copy[i] << " ";
    }
    cout << endl;

    cout << "Счетчик ссылок: " << arr.getRefCount() << endl;

    return 0;
}
