#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include "Table.Cl.h"

using namespace std;

// КЛАССЫ
// 1. Столбец
//     Переменные:
//         название
//         (длина столбца)
//         размер поля
//         вектор с данными
//         ссылка на другой похожий столбец в другой таблице
//     (Методы)

// 2. Таблица 
//     Переменные:
//         путь до файла с таблицей
//         название таблицы
//         количество строк
//         список с названиями столбцов таблицы
//         вектор со столбцами


//     Методы: (public)
//         создать (поля - 1, данные - 2)
//         удалить (поля - 3, данные - 6)
//         изменить (поля - 5, данные - 6)
//         добавить столбец - 7
//         удалить столбец - 8
//         показать таблицу - 9  !!!
//         показать средний балл ученика - 10
//     Методы: (private)
// ФУНКЦИИ:
    // Запустить программу
    // Получить request
    // Запросить ввод задания и его выполнение
    // Прекращение работы программы


//////////////////////////CLASSES///////////////////////////////////

// СТОЛБЕЦ
class Column {
public:
    string columnName;
    // int columnSize;
    vector <string> columnData;
    // ссылка на другой столбец

    // конструктор
    Column(string columnName = "", vector <string> columnData = {}) {
        this -> columnName = columnName;
        this -> columnData = columnData;
    }

};

// ТАБЛИЦА
class Table{
private:
//
public:
    string pathToFile;
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
        cout << endl << "Name: " << tableName << endl;
        for (int i = 0; i < columnsNames.size(); i++) cout << columnsNames[i] << " ";
        cout << endl;
        if (tableBase.size() != 0) {
            for (int i = 0; i < tableBase[0].columnData.size(); i++) { 
               for (int j = 0; j < columnsNames.size(); j++) cout << tableBase[j].columnData[i] << " "; 
                cout << endl;
            }
        }
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
    Table(string pathToFile = "", string tableName = "", vector <string> columnsNames = {}, vector <Column> tableBase = { {} }) {
        this -> pathToFile = pathToFile;
        this -> tableName = tableName;
        this -> columnsNames = columnsNames;
        this -> tableBase = tableBase;
    } 

    // void changeColumnName(){};
    //void

};

////////////////////////////////////GLOBAL VARIABLES/////////////////////////////////////

Table students = Table("table_Students.txt", "Students");
Table courses = Table("table_Courses.txt", "Courses");
Table grades = Table("table_Grades.txt", "Grades");


long long idsForStudents = 0;
long long idsForCourses = 0;
long long idsForGrades = 0;

//////////////////////////////FUNCTIONS////////////////////////////////////

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

void splitTheString(vector<string>* list, string line , char separator = ' ') { // функция split по char для string
    string s = "";

    while (line.size() > 0) {
        if (line[0] != separator) s += line[0];
        else {
            (*list).push_back(s);
            s = "";
        }
        line.erase(0, 1);
    }
    if(s.size() > 0) (*list).push_back(s);
}

bool readTheTables(Table* tableN) {

    ifstream fin;
    fin.open((*tableN).pathToFile);

    if (!fin.is_open()) {
        cout << "Eror ><. Please restart the programm." << endl;
        fin.close();
        return 0;
    }

    string line;
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);

    // здесь мы считали названия столбцов, их нужно записать в названия столбцов таблицы и в названия каждому столбцу
    splitTheString(&((*tableN).columnsNames), line, ' ');

    // создаем столбцы
    for (int i = 0; i < ((*tableN).columnsNames).size(); i++) {
        Column col = Column((*tableN).columnsNames[i]);
        (*tableN).tableBase.push_back(col);
    }

    // считываем и записываем данные
    while (!fin.eof()) {
        getline(fin, line);
        vector<string> dataGotten = {};
        splitTheString(&dataGotten, line, ' ');
        for (int i = 0; i < dataGotten.size(); i++) (*tableN).tableBase[i].columnData.push_back(dataGotten[i]);
    }
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
    //cout << "\n6) Show all tables."; // Показать таблицу.


    /* ВРЕМЕННО ЗАКОММЕНТИРОВАНО
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

    cout << "\nPlease, choose what you would like to to do and type the number of chosen option (for example: 1).\n";
    cout << "\n1) Show table."; // Показать таблицу
    cout << "\n2) Show all tables."; // Показать все таблицы
    cout << "\n3) Get the student's GPA."; // получить средний балл ученика
    cout << "\n4) Change the table.\n"; // Изменить таблицу

    string request = "";
    cin >> request;

    // Показать таблицу - DONE
    if (request == "1") {
        cout << "\nPlease, enter the table name: Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;
        if (tableN == "Students") students.showTheTable();
        else if (tableN == "Courses") courses.showTheTable();
        else if (tableN == "Grades") grades.showTheTable();

    }
    // Показать все таблицы - DONE
    else if (request == "2") {
        students.showTheTable();
        cout << endl;
        courses.showTheTable();
        cout << endl;
        grades.showTheTable();
        cout << endl;

        // cout << "\nIf you want to exit, type down the code -1 (for example: -1).";
    }
    // получить средний балл ученика
    else if (request == "3") {
        cout << "\nPlease, enter student's ID and subject's ID separated by a space.\n";
        string studentID = "", subjectID = "";
        cin >> studentID >> subjectID;
        grades.getGPA(studentID, subjectID);
       // cout << "\nIf you want to exit, type down the code -1 (for example: -1).";
    }
    // Изменить таблицу
    else if (request == "4") { 
        cout << "\nPlease, enter the table's name you would like to change:  Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;
        offerOptionsForTable(tableN);
//        if (tableN == "Students") students.showTheTable();
//        else if (tableN == "Courses") courses.showTheTable();
//        else if (tableN == "Grades") grades.showTheTable();
    }
}

void getTables() {  // считываем таблицы в самом начале
    readTheTables(&students);
    readTheTables(&courses);
    readTheTables(&grades);
}

void setTables(){} // записываем таблицы обратно в файл в самом конце
void startOfProg() {

    // считываем таблицы из файлов
    getTables();
    // приветствие
    cout << "Welcome to the Data Base.\n";
    // предлагаем выбор опций
    offerOptions();

}

//////////////////////////////////////////////////////////////////


int main()
{
    startOfProg(); // сделать бесконечный ввод команд

    return 0;
}
