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

bool checker() {
    string checker;
    cout << endl << "Evet = 1\nHayır = 0" << endl;
    checker = _getch();
    if (checker == "1") {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Devam ediliyor." << endl;
        SetConsoleTextAttribute(hConsole, 14);
        return true;
    }
    else if (checker == "0") {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "İşlem iptal edildi." << endl;
        SetConsoleTextAttribute(hConsole, 14);
        return false;
    }
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Lütfen geçerli bir değer giriniz." << endl;
    SetConsoleTextAttribute(hConsole, 14);
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
    int& notAvaibleBooksIndex,
    string bookUsers[],
    int& bookUsersIndex
) 

{
    string line;

    ifstream adminUsernamesFile;
    ifstream adminPasswordsFile;
    ifstream userUsernamesFile;
    ifstream userPasswordsFile;
    ifstream booksFile;
    ifstream notAvaibleBooksFile;
    ifstream bookUsersFile;

    adminUsernamesFile.open("datas\\01_adminusers_usernames");
    adminPasswordsFile.open("datas\\02_adminusers_passwords");
    userUsernamesFile.open("datas\\03_users_usernames");
    userPasswordsFile.open("datas\\04_users_passwords");
    booksFile.open("datas\\05_books");
    notAvaibleBooksFile.open("datas\\06_not_avaible_books");
    bookUsersFile.open("datas\\07_book_users");

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

    while (getline(bookUsersFile, line)) {
        bookUsers[bookUsersIndex] = line;
        bookUsersIndex++;
    }
}

void writingDatas(
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
    int& notAvaibleBooksIndex,
    string bookUsers[],
    int& bookUsersIndex
)

{
    string line;

    ofstream adminUsernamesFile;
    ofstream adminPasswordsFile;
    ofstream userUsernamesFile;
    ofstream userPasswordsFile;
    ofstream booksFile;
    ofstream notAvaibleBooksFile;
    ofstream bookUsersFile;

    adminUsernamesFile.open("datas\\01_adminusers_usernames");
    adminPasswordsFile.open("datas\\02_adminusers_passwords");
    userUsernamesFile.open("datas\\03_users_usernames");
    userPasswordsFile.open("datas\\04_users_passwords");
    booksFile.open("datas\\05_books");
    notAvaibleBooksFile.open("datas\\06_not_avaible_books");
    bookUsersFile.open("datas\\07_book_users");

    for (int i = 0; i < adminUsernamesIndex; i++) {
        adminUsernamesFile << adminUsernames[i] << endl;
    }

    for (int i = 0; i < adminPasswordsIndex; i++) {
        adminPasswordsFile << adminPasswords[i] << endl;
    }

    for (int i = 0; i < userUsernamesIndex; i++) {
        userUsernamesFile << userUsernames[i] << endl;
    }

    for (int i = 0; i < userPasswordsIndex; i++) {
        userPasswordsFile << userPasswords[i] << endl;
    }

    for (int i = 0; i < booksIndex; i++) {
        booksFile << books[i] << endl;
    }

    for (int i = 0; i < notAvaibleBooksIndex; i++) {
        notAvaibleBooksFile << notAvaibleBooks[i] << endl;
    }

    for (int i = 0; i < bookUsersIndex; i++) {
        bookUsersFile << bookUsers[i] << endl;
    }
}

void registerUser(string usernameDatas[], int& usernameDatasIndex, string passwordDatas[], int& passwordDatasIndex, int maksElement) {

    if (usernameDatasIndex >= maksElement) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\nMaksimum kullanıcı sayısına ulaşıldı.";
        SetConsoleTextAttribute(hConsole, 14);
        Sleep(2000);
        return;
    }

    string registerCheck;
    string username;
    string password;
    cout << "Bir kullanıcı adı giriniz: ";
    cin >> username;

    for (int i = 0; i < usernameDatasIndex; i++) {
        if (username == usernameDatas[i]) {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\nBu kullanıcı zaten mevcut\nLütfen başka bir kullanıcı adı seçiniz.";
            SetConsoleTextAttribute(hConsole, 14);
            Sleep(2000);
            return;
            break;
        }
    }

    cout << "Bir şifre giriniz:         ";
    cin >> password;

    cout << "\nAşağıdaki hesap bilgilerini onaylıyor musunuz?" << endl;
    setlocale(LC_ALL, "C");
    SetConsoleTextAttribute(hConsole, 9);
    cout << endl << username << "\n" << password << endl;
    SetConsoleTextAttribute(hConsole, 14);
    setlocale(LC_ALL, "Turkish");

    if (checker()) {
        usernameDatas[usernameDatasIndex] = username;
        usernameDatasIndex++;

        passwordDatas[passwordDatasIndex] = password;
        passwordDatasIndex++;

        SetConsoleTextAttribute(hConsole, 10);
        cout << "KAYIT BAŞARILI" << endl;
        SetConsoleTextAttribute(hConsole, 14);
        Sleep(2000);
        return;
    }

    SetConsoleTextAttribute(hConsole, 10);
    cout << "KAYIT BAŞARISIZ" << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(2000);
    return;
}

bool loginUser(string usernameData[], string passwordData[], string& loggedUsername) {

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
            loggedUsername = usernameData[i];
            Sleep(2000);
            return true;
            break;
        }
    }
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Kullanıcı Adı veya Şifre Yanlış" << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(2000);
    return false;
}

void bookPicker(string booksData[], int lastIndex, bool notAvaibleBooksData[], int lastIndex2, string loggedUsername, string bookUsersData[], int maksElement) {

    for (int i = 0; i < maksElement; i++) {
        if (bookUsersData[i] == loggedUsername) {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Zaten aldığınız bir kitap var.\nLütfen önce onu iade ediniz." << endl;
            SetConsoleTextAttribute(hConsole, 14);
            Sleep(2000);
            return;
        }
    }

    setlocale(LC_ALL, "C");
    SetConsoleTextAttribute(hConsole, 9);
    for (int i = 0; i < lastIndex; i++) {
        cout << i + 1 << ") " << booksData[i] << endl;
    }
    SetConsoleTextAttribute(hConsole, 14);
    setlocale(LC_ALL, "Turkish");

    cout << endl;
    cout << "Almak istediğiniz kitabın numarasını giriniz: ";
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

            setlocale(LC_ALL, "C");
            SetConsoleTextAttribute(hConsole, 9);
            cout << "\n" << booksData[stoi(choice) - 1];
            SetConsoleTextAttribute(hConsole, 14);
            setlocale(LC_ALL, "Turkish");
            cout << " isimli kitap seçildi.\Onaylıyor musunuz?" << endl;

            if (checker()) {
                bookUsersData[stoi(choice) - 1] = loggedUsername;
                notAvaibleBooksData[stoi(choice) - 1] = 1;
                SetConsoleTextAttribute(hConsole, 10);
                cout << "KİTAP ALINDI" << endl;
                SetConsoleTextAttribute(hConsole, 14);
                Sleep(2000);
                return;
            }

            SetConsoleTextAttribute(hConsole, 12);
            cout << "KİTAP ALINAMADI" << endl;
            SetConsoleTextAttribute(hConsole, 14);
            Sleep(2000);
            return;
            Sleep(2000);
            return;
        }
    }

    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nLütfen geçerli bir numara girin." << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(3000);
    return;
}

void dataLister(string datas[], int datasIndex) {
    setlocale(LC_ALL, "C");
    SetConsoleTextAttribute(hConsole, 9);
    for (int i = 0; i < datasIndex; i++) {
        cout << i + 1 << ") " << datas[i] << endl;
    }
    SetConsoleTextAttribute(hConsole, 14);
    cout << endl;
    setlocale(LC_ALL, "Turkish");
    cout << "Geri gitmek için herhangi bir tuşa basınız." << endl;
    char a = _getch();
}

void addBook(string bookDatas[], int& bookDatasIndex, int maksElement) {

    if (bookDatasIndex >= maksElement) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\nMaksimum kitap sayısına ulaşıldı.";
        SetConsoleTextAttribute(hConsole, 14);
        Sleep(2000);
        return;
    }

    string bookName;
    cout << "Yeni kitabın Adını Giriniz: ";
    getline(cin >> ws, bookName);

    bookDatas[bookDatasIndex] = bookName;
    bookDatasIndex++;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "KAYIT BAŞARILI" << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(2000);
    return;
}

int main() {

    SetConsoleTextAttribute(hConsole, 14);

    const int maksElement = 100;

    string adminUsernames[maksElement];
    int adminUsernamesIndex = 0;

    string adminPasswords[maksElement];
    int adminPasswordsIndex = 0;

    string userUsernames[maksElement];
    int userUsernamesIndex = 0;

    string userPasswords[maksElement];
    int userPasswordsIndex = 0;

    string books[maksElement];
    int booksIndex = 0;

    bool notAvaibleBooks[maksElement];
    int notAvaibleBooksIndex = 0;

    string bookUsers[maksElement];
    int bookUsersIndex = 0;

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
        notAvaibleBooksIndex,
        bookUsers,
        bookUsersIndex
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
            registerUser(
                userUsernames,
                userUsernamesIndex,
                userPasswords,
                userPasswordsIndex,
                maksElement
            );

            writingDatas(
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
                notAvaibleBooksIndex,
                bookUsers,
                bookUsersIndex
            );
        }

        else if (mainMenuChoice == "2") {
            string loggedUsername = "";
            if (loginUser(userUsernames, userPasswords, loggedUsername)) {

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
                    cout << "#   Geri gitmek için 0 giriniz.           #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;


                    cout << endl;
                    loginMenuChoice = _getch();

                    if (loginMenuChoice == "1") {
                        dataLister(books, booksIndex);
                    }

                    else if (loginMenuChoice == "2") {
                        bookPicker(books, booksIndex, notAvaibleBooks, notAvaibleBooksIndex, loggedUsername, bookUsers, maksElement);

                        writingDatas(
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
                            notAvaibleBooksIndex,
                            bookUsers,
                            bookUsersIndex
                        );
                    }

                    else if (loginMenuChoice == "0") {
                        loggedUsername = "";
                    }
                }
            }
        }

        else if (mainMenuChoice == "3") {
            string loggedUsername = "";
            if (loginUser(adminUsernames, adminPasswords, loggedUsername)) {

                string adminMenuChoice = "default";
                while (adminMenuChoice != "0") {

                    system("cls");
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   Y Ö N E T İ C İ   M E N Ü S Ü         #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   1. Kitap Listesi                      #" << endl;
                    cout << "#   2. Yönetici Ekle                      #" << endl;
                    cout << "#   3. Kullanıcı Listesi                  #" << endl;
                    cout << "#   4. Yönetici Listesi                   #" << endl;
                    cout << "#   5. Yeni Kitap Ekle                    #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "#   Geri gitmek için 0 giriniz.           #" << endl;
                    cout << "#                                         #" << endl;
                    cout << "# # # # # # # # # # # # # # # # # # # # # #" << endl;


                    cout << endl;
                    adminMenuChoice = _getch();

                    if (adminMenuChoice == "1") {
                        dataLister(books, booksIndex);
                    }

                    else if (adminMenuChoice == "2") {
                        registerUser(
                            adminUsernames,
                            adminUsernamesIndex,
                            adminPasswords,
                            adminPasswordsIndex,
                            maksElement
                        );

                        writingDatas(
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
                            notAvaibleBooksIndex,
                            bookUsers,
                            bookUsersIndex
                        );
                    }

                    else if (adminMenuChoice == "3") {
                        dataLister(userUsernames, userUsernamesIndex);
                    }

                    else if (adminMenuChoice == "4") {
                        dataLister(adminUsernames, adminUsernamesIndex);
                    }

                    else if (adminMenuChoice == "5") {
                        addBook(books, booksIndex, maksElement);

                        writingDatas(
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
                            notAvaibleBooksIndex,
                            bookUsers,
                            bookUsersIndex
                        );
                    }

                    else if (adminMenuChoice == "0") {
                        loggedUsername = "";
                    }
                }
            }
        }

        else if (mainMenuChoice == "4") {
            dataLister(books, booksIndex);
        }

        else if (mainMenuChoice == "5") {
        }
    }

    return 0;
}