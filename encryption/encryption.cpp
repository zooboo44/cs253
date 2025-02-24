// encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int getNewKey(int& key, vector<int> vec) {
    return key + vec.size();
}


vector<int> encode(const string& filePath) {
    vector<int> asciiVector;
    ifstream file(filePath, ios::in);

    if (!file) {
        cerr << "Error opening file" << filePath << endl;
        return asciiVector;
    }

    char ch;
    while (file.get(ch)) {
        asciiVector.push_back(static_cast<int>(ch));
    }

    file.close();
    return asciiVector;
}

vector<char> decode(vector<int> encoded) {
    vector<char> decoded;
    for (int value : encoded) {
        decoded.push_back(static_cast<char>(value));
    }
    return decoded;
}

vector<int> encrypt(const vector<int>& asciiVector, int key) {
    vector<int> encrypted;
    for (int value : asciiVector) {
        encrypted.push_back(value + key);
    }
    return encrypted;
}

vector<int> decrypt(string filePath, int key) {
    vector<int> encrypted;
    ifstream file(filePath, ios::in);
    if (!file) {
        cerr << "Error opening file" << filePath << endl;
    }

    int num;

    while (file >> num) {
        encrypted.push_back(num);
    }

    int newKey = getNewKey(key, encrypted);

    vector<int> decrypted;
    for (int value : encrypted) {
        decrypted.push_back(value - newKey);
    }
    return decrypted;
}

void writeEncodedToFile(const vector<int>& encrypted, string filePath) {
    ofstream file(filePath, ios::out);

    if (!file) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    for (int value : encrypted) {
        file << value << " ";
    }
}

void writeDecodedToFile(vector<char>& decodedVector, string filePath) {
    ofstream file(filePath, ios::out);

    if (!file) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    file.write(decodedVector.data(), decodedVector.size());
    file.close();
}
int main()
{
    string originalFileName, encryptedFileName, decryptedFileName;
    string input;
    vector<int> asciiVector;
    vector<int> decryptedVector;
    vector<char> decodedVector;
    vector<int> encrypted;
    int key = 0;
    int newKey;
    cout << "Enter a number 1-2 for the following selections: \n";
    cout << "1. Encrypt file" << endl;
    cout << "2. Decrypt file" << endl;
    cin >> input;

    if (input == "1") {
        cout << "Enter file to encrypt: ";
        cin >> originalFileName;
        cout << "Enter key(integer): ";
        cin >> key;
        cout << "Name the encrypted file: ";
        cin >> encryptedFileName;
        asciiVector = encode(originalFileName);
        newKey = getNewKey(key, asciiVector);
        encrypted = encrypt(asciiVector, newKey);
        writeEncodedToFile(encrypted, encryptedFileName);
    }
    if (input == "2") {
        cout << "Enter encrypted filename to decrypt: ";
        cin >> encryptedFileName;
        cout << "Enter key(integer): ";
        cin >> key;
        cout << "Name the decrypted file: ";
        cin >> decryptedFileName;
        decryptedVector = decrypt(encryptedFileName, key);
        decodedVector = decode(decryptedVector);
        writeDecodedToFile(decodedVector, decryptedFileName);
    }
    if (input == "exit") {
        cout << "goodbye" << endl;
        exit(1);
    }
    else {
        cout << "Please rerun the program and enter a valid option" << endl;
    }
}
