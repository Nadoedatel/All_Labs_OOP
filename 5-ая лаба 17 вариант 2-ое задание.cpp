#include <iostream>
#include <fstream>
#include <cstdlib>  // Для rand и srand
#include <ctime>    // Для time
using namespace std;
const int MIN_VALUE = -50;
const int MAX_VALUE = 50;
const int MAX_POSITIVE = 50;

void generateInputFile(const string& filename) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        cout << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 100; ++i) {
        int num = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
        outfile << num << "\n";
    }
    outfile.close();
}

void processFile(const string& inputFile, const string& outputFile) {
    ifstream infile(inputFile.c_str());
    ofstream outfile(outputFile.c_str());

    if (!infile || !outfile) {
        cout << "Ошибка при открытии файлов!" << endl;
        return;
    }

    int num;
    while (infile >> num) {
        if (num > 0) {
            outfile << MAX_POSITIVE << "\n";
        }
        else {
            outfile << num << "\n";
        }
    }

    infile.close();
    outfile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    string inputFile = "input.txt";
    string outputFile = "output.txt";

    generateInputFile(inputFile);
    processFile(inputFile, outputFile);

    cout << "Файлы успешно созданы и обработаны." << endl;

    return 0;
}
