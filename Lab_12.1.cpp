#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

// ������� ��� ��������� �������� ����� � �������
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
        fout.write((char*)&num, sizeof(num)); // �������� ����� � ������� ����
        cout << "Do you want to continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    fout.close();
}

// ������� ��� ���������� ���������� ������������� ��'����� �� �������� ����� � �������� ����
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

    // �������� ������ ����������� � ������������ ������� ����
    fout.write((char*)&avgPos, sizeof(avgPos));
    fout.write((char*)&avgNeg, sizeof(avgNeg));

    fout.close();
}

// ������� ��� ��������� ����� �������� ����� (�������� ������ ��������)
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

    // ��������� �������� ����� � �������
    CreateBinaryFile(fname);

    // ������� �������� �����, ���������� ���������� ������������� �� ����� ����������
    cout << "Enter the name of the result binary file: ";
    cin >> resultFile;
    ProcessBinaryFile(fname, resultFile);

    // ��������� ����������
    cout << "Content of result file (averages): " << endl;
    PrintBinaryFile(resultFile);

    return 0;
}
