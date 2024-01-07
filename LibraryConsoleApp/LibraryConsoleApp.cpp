#include <iostream>
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
    int& notAvaibleBooksIndex
)

{
    string line;

    ofstream adminUsernamesFile;
    ofstream adminPasswordsFile;
    ofstream userUsernamesFile;
    ofstream userPasswordsFile;
    ofstream booksFile;
    ofstream notAvaibleBooksFile;

    adminUsernamesFile.open("datas\\01_adminusers_usernames.txt");
    adminPasswordsFile.open("datas\\02_adminusers_passwords.txt");
    userUsernamesFile.open("datas\\03_users_usernames.txt");
    userPasswordsFile.open("datas\\04_users_passwords.txt");
    booksFile.open("datas\\05_books.txt");
    notAvaibleBooksFile.open("datas\\06_not_avaible_books.txt");

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
}

void registerUser(string usernameDatas[], int& usernameDatasIndex, string passwordDatas[], int& passwordDatasIndex, int maksElement) {

    if (usernameDatasIndex >= maksElement) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\nMaksimum kullanıcı sayısına ulaşıldı.";
        SetConsoleTextAttribute(hConsole, 14);
        Sleep(2000);
        return;
    }

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

    usernameDatas[usernameDatasIndex] = username;
    usernameDatasIndex++;

    passwordDatas[passwordDatasIndex] = password;
    passwordDatasIndex++;

    SetConsoleTextAttribute(hConsole, 10);
    cout << "KAYIT BAŞARILI" << endl;
    SetConsoleTextAttribute(hConsole, 14);
    Sleep(2000);
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

void bookPicker(string booksData[], int lastIndex, bool notAvaibleBooksData[], int lastIndex2) {
    SetConsoleTextAttribute(hConsole, 9);
    for (int i = 0; i < lastIndex; i++) {
        cout << i + 1 << ") " << booksData[i] << endl;
    }
    SetConsoleTextAttribute(hConsole, 14);

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
                notAvaibleBooksIndex
            );
        }

        else if (mainMenuChoice == "2") {
            if (loginUser(userUsernames, userPasswords)) {

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

                    if (loginMenuChoice == "2") {
                        bookPicker(books, booksIndex, notAvaibleBooks, notAvaibleBooksIndex);
                    }
                }
            }
        }

        else if (mainMenuChoice == "3") {
            if (loginUser(adminUsernames, adminPasswords)) {

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
                            notAvaibleBooksIndex
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
                            notAvaibleBooksIndex
                        );
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