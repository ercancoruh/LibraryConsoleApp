﻿#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <locale>
#include <codecvt>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool to_bool(string stob) {
    if (stob == "1") {
        return true;
    }
    return false;
}

void readingDatas(
    string adminUsernames[],
    int& adminUsernamesIndex,
    string adminPasswords[],
    int& adminPasswordsIndex,
    string userUsernames[],
    int& userUsernamesIndex,
    string userPasswords[],
    int& userPasswordsIndex,
    string books[],
    int& booksIndex,
    bool notAvaibleBooks[],
    int& notAvaibleBooksIndex
) 

{
    string line;

    ifstream adminUsernamesFile;
    ifstream adminPasswordsFile;
    ifstream userUsernamesFile;
    ifstream userPasswordsFile;
    ifstream booksFile;
    ifstream notAvaibleBooksFile;

    adminUsernamesFile.open("datas\\01_adminusers_usernames.txt");
    adminPasswordsFile.open("datas\\02_adminusers_passwords.txt");
    userUsernamesFile.open("datas\\03_users_usernames.txt");
    userPasswordsFile.open("datas\\04_users_passwords.txt");
    booksFile.open("datas\\05_books.txt");
    notAvaibleBooksFile.open("datas\\06_not_avaible_books.txt");

    while (getline(adminUsernamesFile, line)) {
        adminUsernames[adminUsernamesIndex] = line;
        adminUsernamesIndex++;
    }

    while (getline(adminPasswordsFile, line)) {
        adminPasswords[adminPasswordsIndex] = line;
        adminPasswordsIndex++;
    }

    while (getline(userUsernamesFile, line)) {
        userUsernames[userUsernamesIndex] = line;
        userUsernamesIndex++;
    }

    while (getline(userPasswordsFile, line)) {
        userPasswords[userPasswordsIndex] = line;
        userPasswordsIndex++;
    }

    while (getline(booksFile, line)) {
        books[booksIndex] = line;
        booksIndex++;
    }

    while (getline(notAvaibleBooksFile, line)) {
        notAvaibleBooks[notAvaibleBooksIndex] = to_bool(line);
        notAvaibleBooksIndex++;
    }
}

bool loginUser(string usernameData[], string passwordData[]) {

    string username;
    cout << "Kullanıcı Adı: ";
    cin >> username;
    string password;
    cout << "Şifre:         ";
    cin >> password;

    for (int i = 0; i < 50; i++) {
        if (username == usernameData[i] && password == passwordData[i]) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "GİRİŞ BAŞARILI" << endl;
            SetConsoleTextAttribute(hConsole, 14);
            return true;
            break;
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Kullanıcı Adı veya Şifre Yanlış" << endl;
            SetConsoleTextAttribute(hConsole, 14);
            return false;
        }
    }
    return false;
}

void bookLister(string booksData[], int lastIndex) {
    SetConsoleTextAttribute(hConsole, 9);
    locale::global(locale("tr_TR.UTF-8"));
    for (int i = 0; i < lastIndex; i++) {
        cout << i + 1 << ". " << booksData[i] << endl;
    }
    setlocale(LC_ALL, "Turkish");
    SetConsoleTextAttribute(hConsole, 14);
    cout << endl;
    cout << "Geri gitmek için herhangi bir tuşa basınız." << endl;
    char a = _getch();
}

void bookPicker(string booksData[], int lastIndex, bool notAvaibleBooksData[], int lastIndex2) {
    SetConsoleTextAttribute(hConsole, 9);
    locale::global(locale("tr_TR.UTF-8"));
    for (int i = 0; i < lastIndex; i++) {
        cout << i + 1 << ". " << booksData[i] << endl;
    }
    setlocale(LC_ALL, "Turkish");
    SetConsoleTextAttribute(hConsole, 14);

    cout << "Almak istediğiniz kitabın numarasını giriniz." << endl;
    bool stoiError = false;
    int choiceTest;
    string choice;
    cin >> choice;

    try
    {
        choiceTest = stoi(choice);
    }
    catch (...)
    {
        stoiError = true;
    }

    if (!stoiError) {
        if (stoi(choice) > 0 && stoi(choice) <= lastIndex) {

            if (notAvaibleBooksData[stoi(choice) - 1]) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\nBu kitap başkası tarafından alınmış\nLütfen başka bir kitap Seçiniz." << endl;
                SetConsoleTextAttribute(hConsole, 14);
                Sleep(3000);
                return;
            }

            SetConsoleTextAttribute(hConsole, 10);
            cout << "\n" << choice << ". kitap seçildi." << endl;
            SetConsoleTextAttribute(hConsole, 14);
            Sleep(3000);
            return;
        }
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nLütfen geçerli bir numara girin." << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(3000);
    return;
}

int main() {

    SetConsoleTextAttribute(hConsole, 14);

    string adminUsernames[50];
    int adminUsernamesIndex = 0;

    string adminPasswords[50];
    int adminPasswordsIndex = 0;

    string userUsernames[50];
    int userUsernamesIndex = 0;

    string userPasswords[50];
    int userPasswordsIndex = 0;

    string books[50];
    int booksIndex = 0;

    bool notAvaibleBooks[50];
    int notAvaibleBooksIndex = 0;

    readingDatas(
        adminUsernames,
        adminUsernamesIndex,
        adminPasswords,
        adminPasswordsIndex,
        userUsernames,
        userUsernamesIndex,
        userPasswords,
        userPasswordsIndex,
        books,
        booksIndex,
        notAvaibleBooks,
        notAvaibleBooksIndex
    );

    setlocale(LC_ALL, "Turkish");

    string mainMenuChoice = "default";
    while (mainMenuChoice != "0") {

        system("cls");
        cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
        cout << "#                                         #" << endl;
        cout << "#   A N A   M E N Ü                       #" << endl;
        cout << "#                                         #" << endl;
        cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
        cout << "#                                         #" << endl;
        cout << "#   1. Kayıt Ol                           #" << endl;
        cout << "#   2. Kullanıcı Girişi                   #" << endl;
        cout << "#   3. Yönetici Girişi                    #" << endl;
        cout << "#   4. Kitap Listesi                      #" << endl;
        cout << "#                                         #" << endl;
        cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
        cout << "#                                         #" << endl;
        cout << "#   Programdan çıkmak için 0 giriniz.     #" << endl;
        cout << "#                                         #" << endl;
        cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;


        cout << endl;
        mainMenuChoice = _getch();

        if (mainMenuChoice == "1") {
        }

        else if (mainMenuChoice == "2") {
            if (loginUser(userUsernames, userPasswords)) {
                Sleep(1500);

                string loginMenuChoice = "default";
                while (loginMenuChoice != "0") {

                    system("cls");
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   K U L L A N I C I   M E N Ü S Ü       #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   1. Kitap Listesi                      #" << endl;
                    cout << "#   2. Kitap Al                           #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   Programdan çıkmak için 0 giriniz.     #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;


                    cout << endl;
                    loginMenuChoice = _getch();

                    if (loginMenuChoice == "1") {
                        bookLister(books, booksIndex);
                    }

                    if (loginMenuChoice == "2") {
                        bookPicker(books, booksIndex, notAvaibleBooks, notAvaibleBooksIndex);
                    }
                }
            }
        }

        else if (mainMenuChoice == "3") {
        }

        else if (mainMenuChoice == "4") {
        }
    }

    return 0;
}