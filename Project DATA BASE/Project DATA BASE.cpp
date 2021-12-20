#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include "Table.Cl.h"

using namespace std;

// СТРУКТУРЫ: 
// 1. Столбец
//     Переменные:
//         название
//         (длина столбца)
//         размер поля
//         вектор с данными
//         ссылка на другой похожий столбец в другой таблице
//     (Методы)


// КЛАССЫ:
// 1. Таблица 
//     Переменные:
//         название таблицы
//         список с названиями столбцов таблицы
//         вектор со столбцами

//     Методы: (public)
//         создать (поля - 1, данные - 2)
//         удалить (поля - 3, данные - 6)
//         изменить (поля - 5, данные - 6)
//         добавить столбец - 7
//         удалить столбец - 8
//         показать таблицу - 9
//         показать средний балл ученика - 10
//     Методы: (private)
// ФУНКЦИИ:
    // Запустить программу
    // Получить request
    // Запросить ввод задания и его выполнение
    // Прекращение работы программы


//////////////////////////КЛАССЫ///////////////////////////////////

// Столбец
class Column {
public:
    string ColumnName;
    // int columnSize;
    vector <string> columnData;
    int columnSize = columnData.size();
    // ссылка на другой столбец

};



class Table{
private:

//    string tableName;
//    vector <string> columnsNames;
    // vector <Columns> columns;


public:
    string tableName;
    vector <string> columnsNames;
    vector <Column> tableBase;

    //void createTheBox() {};
    void createTheData() { // создать новую строку
        cout << "1000000";
    };
    //void deleteTheBox() {};
    void deleteTheData() {
        cout << "1000000";
    };
    //void changeTheBox() {};
    void changeTheData() {
        cout << "1000000";
    };
    void addTheColumn() {
        cout << "1000000";
    };
    void deleteTheColumn() {
        cout << "1000000";
    };
    void showTheTable() {
        cout << "1000000";
    };

    void getGPA(string studentID, string subjectID) {
        /*
        int sumOtenka = 0; countOtenka = 0;

        for (int i = 0; i < stolbezSize; i++) {
            if (idYchenika[i] == nujniy_id_ychenika) {
                if (idPredmeta[i] == nujniy_id_predmeta) {
                    sumOtenka += otsenka;
                    countOtsenka++;
                }
            }
        }
        int gpa =
    */
    }

    // конструктор
    Table(string tableName = "", vector <string> columnsNames = {}, vector <Column> tableBase = {}) {         // конструктор
        this -> tableName = tableName;
        this -> columnsNames = columnsNames;
        this -> tableBase = tableBase;
    } 


    // void changeColumnName(){};
    //void

};

/////////////////////////////////////////////////////////////////////////

Table students = Table();
Table courses = Table();
Table grades = Table();

//////////////////////////////ФУНКЦИИ////////////////////////////////////

void getRequest() {
    /* 
    string request = "";
     while(request != "Нет. Закрыть Базу Данных."){
         cin >> request;
         if(request == "1") createTheBox();
         else if (request == "2") createTheData();
         else if (request == "3") deleteTheBox();
         else if (request == "4") deleteTheData();
         else if (request == "5") changeTheBox();
         else if (request == "6") changeTheData();
         else if (request == "7") addTheColumn();
         else if (request == "8") deleteTheColumn();
         else if (request == "9") showTheTable();
         else if (request == "10") GPA();
     }
     */
}


//////////////////////////////ФУНКЦИИ////////////////////////////////////

void readTheTables() {

}

void offerOptionsForTable(string tableN = "") {
    /* 
    Table* workingTable;

    if (tableN == "Students") workingTable = &students;
    else if (tableN == "Courses") workingTable = &courses;
    else if (tableN == "Grades") workingTable = &grades;
    */

    cout << "\nPlease, opt for the command you would like to perform and input the number of chosen option (for example: 1).\n";

    cout << "\n1) Create or write the data."; // Записать данные
    cout << "\n2) Delete the data."; // Удалить данные
    cout << "\n3) Change the data."; // Изменить данные
    cout << "\n4) Add the column."; // Добавить столбец
    cout << "\n5) Delete the column.\n"; // Удалить столбец
    //cout << "\n6) Show the table."; // Показать таблицу.


    /*
    string request = "";
    cin >> request;
    if (request == "1") (*workingTable).createTheData();
    else if (request == "2") (*workingTable).deleteTheData();
    else if (request == "3") (*workingTable).changeTheData();
    else if (request == "4") (*workingTable).addTheColumn();
    else if (request == "5") (*workingTable).deleteTheColumn();
    //else if (request == "6") (*workingTable).showTheTable();
    */
}

void offerOptions() {

    cout << "\nPlease, choose what you would like to to do and input the number of chosen option (for example: 1).\n";
    cout << "\n1) Show table."; // Показать таблицу
    //cout << "\n2) Show tables.";
    cout << "\n2) Get the student's GPA."; // получить средний балл ученика
    cout << "\n3) Change the table.\n"; // Изменить таблицу

    string request = "";
    cin >> request;

    if (request == "1") { // Показать таблицу
        cout << "\nPlease, enter the table name: Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;
        if (tableN == "Students") students.showTheTable();
        else if (tableN == "Courses") courses.showTheTable();
        else if (tableN == "Grades") grades.showTheTable();

    }
    else if (request == "2") { // получить средний балл ученика
        cout << "\nPlease, enter student's ID and subject's ID separated by a space.\n";
        string studentID = "", subjectID = "";
        cin >> studentID >> subjectID;
        grades.getGPA(studentID, subjectID);
       // cout << "\nIf you want to exit, type down the code -1 (for example: -1).";
    }
    else if (request == "3") {   // Изменить таблицу
        cout << "\nPlease, enter the table's name you would like to change:  Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;
        offerOptionsForTable(tableN);
//        if (tableN == "Students") students.showTheTable();
//        else if (tableN == "Courses") courses.showTheTable();
//        else if (tableN == "Grades") grades.showTheTable();
    }
}

void greeting() {
    //setlocale(LC_ALL, "Russian");
    //cout << "Добро пожаловать в Базу Данных. Пожалуйста, выберите действие, которое Вы хотели бы выполнить и введите номер выбранного действия.";
    //cout << "Welcome to the Data Base.\nPlease, opt for the option you would like to perform and input the number of chosen option (for example: 1).\n";
    cout << "Welcome to the Data Base.\n";
}

void startOfProg() {

    // считываем таблицы из файлов
    readTheTables();
    // приветствие
    greeting();
    // предлагаем выбор опций
    offerOptions();

}

//////////////////////////////////////////////////////////////////


int main()
{

    startOfProg();

    return 0;
}
