#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

// Функції для тестування
void CreateBinaryFile(const char* fname) {
    ofstream fout(fname, ios::binary);
    int num = 10;  // Додаємо тестове значення
    fout.write((char*)&num, sizeof(num));
    num = -5;  // Додаємо тестове значення
    fout.write((char*)&num, sizeof(num));
    num = 15;  // Додаємо тестове значення
    fout.write((char*)&num, sizeof(num));
    fout.close();
}

void ProcessBinaryFile(const char* fname, const char* resultFile) {
    ifstream fin(fname, ios::binary);
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
    double avgPos = 0, avgNeg = 0;
    if (countPos > 0) {
        avgPos = static_cast<double>(sumPos) / countPos;
    }
    if (countNeg > 0) {
        avgNeg = static_cast<double>(sumNeg) / countNeg;
    }

    fout.write((char*)&avgPos, sizeof(avgPos));
    fout.write((char*)&avgNeg, sizeof(avgNeg));
    fout.close();
}

void PrintBinaryFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    double avgPos, avgNeg;
    fin.read((char*)&avgPos, sizeof(avgPos));
    fin.read((char*)&avgNeg, sizeof(avgNeg));
    fin.close();

    cout << "Average of positive numbers: " << avgPos << endl;
    cout << "Average of negative numbers: " << avgNeg << endl;
}

// Тести
namespace UnitTest
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(CreateFileTest) {
            const char* fname = "test.bin";
            CreateBinaryFile(fname);

            // Перевіримо, чи файл було створено
            ifstream fin(fname, ios::binary);
            Assert::IsTrue(fin.is_open(), L"File should be created");

            // Перевіряємо кількість чисел у файлі
            int count = 0;
            int num;
            while (fin.read((char*)&num, sizeof(num))) {
                count++;
            }
            fin.close();
            Assert::AreEqual(count, 3, L"File should contain 3 numbers");
        }

        TEST_METHOD(ProcessFileTest) {
            const char* fname = "test.bin";
            const char* resultFile = "result.bin";
            CreateBinaryFile(fname);  // Спочатку створюємо файл

            ProcessBinaryFile(fname, resultFile);  // Обробляємо файл

            // Тепер перевіряємо, чи файл результату містить середні значення
            ifstream fin(resultFile, ios::binary);
            Assert::IsTrue(fin.is_open(), L"Result file should be created");

            double avgPos, avgNeg;
            fin.read((char*)&avgPos, sizeof(avgPos));
            fin.read((char*)&avgNeg, sizeof(avgNeg));
            fin.close();

            // Перевіримо значення середнього арифметичного
            Assert::AreEqual(avgPos, 12.5, L"Average of positive numbers should be 12.5");
            Assert::AreEqual(avgNeg, -5.0, L"Average of negative numbers should be -5.0");
        }

        TEST_METHOD(PrintFileTest) {
            const char* resultFile = "result.bin";
            const char* fname = "test.bin";
            CreateBinaryFile(fname);  // Спочатку створюємо файл

            ProcessBinaryFile(fname, resultFile);  // Обробляємо файл

            // Перевірка виведення (у цьому випадку ми просто перевіряємо, що файл зчитується без помилок)
            // Ви можете також налаштувати тест для порівняння виведення через RedirectOutput
            PrintBinaryFile(resultFile);  // Виведення в консоль (буде показано в тестовому виконанні)
        }
    };
}
