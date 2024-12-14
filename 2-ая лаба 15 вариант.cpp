#include <iostream>
#include <cmath>
#include <exception>
#include <string>

using namespace std;

// Класс исключений CustomException
class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getCode() const {
        return errorCode;
    }
};

// Функция для вычисления Z1
double calculateZ1(double& x, double& y) {
    if (x < 0 || y < 0) {
        throw CustomException("Ошибка: отрицательное значение под корнем", (x < 0 ? x : y), 1);
    }

    double numerator = (x - 1) * sqrt(x) - (y - 1) * sqrt(y);
    double denominator = sqrt(pow(x, 3) * y + x * y + pow(x, 2) - x);

    if (denominator == 0) {
        throw CustomException("Ошибка: деление на ноль в Z1", denominator, 2);
    }

    return numerator / denominator;
}

// Функция для вычисления Z2
double calculateZ2(double& x, double& y) {
    if (x < 0 || y < 0) {
        throw CustomException("Ошибка: отрицательное значение под корнем", (x < 0 ? x : y), 1);
    }

    double numerator = sqrt(x) - sqrt(y);

    if (x == 0) {
        throw CustomException("Ошибка: деление на ноль в Z2", x, 2);
    }

    return numerator / x;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double x, y;

    cout << "Введите значение x: ";
    cin >> x;
    cout << "Введите значение y: ";
    cin >> y;

    try {
        double z1 = calculateZ1(x, y);
        double z2 = calculateZ2(x, y);

        cout << "Z1 = " << z1 << endl;
        cout << "Z2 = " << z2 << endl;

        if (abs(z1 - z2) < 1e-6) {
            cout << "Z1 и Z2 примерно равны.\n";
        }
        else {
            cout << "Z1 и Z2 не равны.\n";
        }
    }
    catch (const CustomException& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        cerr << "Значение: " << e.getValue() << endl;
        cerr << "Код ошибки: " << e.getCode() << endl;
    }

    return 0;
}
