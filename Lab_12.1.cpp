#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

// Функція для створення бінарного файлу з числами
void CreateBinaryFile(const char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    int num;
    char cont;
    do {
        cout << "Enter a number: ";
        cin >> num;
        fout.write((char*)&num, sizeof(num)); // Записуємо число в бінарний файл
        cout << "Do you want to continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    fout.close();
}

// Функція для обчислення середнього арифметичного від'ємних та додатних чисел у бінарному файлі
void ProcessBinaryFile(const char* fname, const char* resultFile) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    int num;
    int sumPos = 0, countPos = 0, sumNeg = 0, countNeg = 0;

    while (fin.read((char*)&num, sizeof(num))) {
        if (num > 0) {
            sumPos += num;
            countPos++;
        }
        else if (num < 0) {
            sumNeg += num;
            countNeg++;
        }
    }
    fin.close();

    ofstream fout(resultFile, ios::binary);
    if (!fout) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    double avgPos = 0, avgNeg = 0;
    if (countPos > 0) {
        avgPos = static_cast<double>(sumPos) / countPos;
    }
    if (countNeg > 0) {
        avgNeg = static_cast<double>(sumNeg) / countNeg;
    }

    // Записуємо середнє арифметичне в результатний бінарний файл
    fout.write((char*)&avgPos, sizeof(avgPos));
    fout.write((char*)&avgNeg, sizeof(avgNeg));

    fout.close();
}

// Функція для виведення вмісту бінарного файлу (виводимо середні значення)
void PrintBinaryFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    double avgPos, avgNeg;
    fin.read((char*)&avgPos, sizeof(avgPos));
    fin.read((char*)&avgNeg, sizeof(avgNeg));

    cout << "Average of positive numbers: " << avgPos << endl;
    cout << "Average of negative numbers: " << avgNeg << endl;

    fin.close();
}

int main() {
    char fname[100], resultFile[100];

    cout << "Enter the name of the binary file with numbers: ";
    cin >> fname;

    // Створення бінарного файлу з числами
    CreateBinaryFile(fname);

    // Обробка бінарного файлу, обчислення середнього арифметичного та запис результату
    cout << "Enter the name of the result binary file: ";
    cin >> resultFile;
    ProcessBinaryFile(fname, resultFile);

    // Виведення результату
    cout << "Content of result file (averages): " << endl;
    PrintBinaryFile(resultFile);

    return 0;
}
