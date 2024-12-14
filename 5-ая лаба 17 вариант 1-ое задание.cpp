#include <iostream>
using namespace std;
class StringManipulator {
private:
    string str;

public:
    friend istream& operator>>(istream& is, StringManipulator& obj) {
        is >> obj.str;
        return is;
    }

    friend ostream& operator<<(ostream& os, const StringManipulator& obj) {
        for (char c : obj.str) {
            if (c >= 'a' && c <= 'z') {
                os << static_cast<char>(c - 32);
            }
            else if (c >= '0' && c <= '9') {
                os << hex << static_cast<int>(c - '0'); 
            }
            else {
                os << c; 
            }
        }
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    StringManipulator sm;
    cout << "Введите строку: ";
    cin >> sm;

    cout << "Результат: " << sm << endl;
    return 0;
}
