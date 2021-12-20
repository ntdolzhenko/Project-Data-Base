#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
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

    // Показать таблицу
    void showTheTable() {    // чтобы нормально выводилось погуглить setw в iomanip
        cout << endl << "Name: " << tableName << endl;
        for (int i = 0; i < columnsNames.size(); i++) cout << columnsNames[i] << " ";
        cout << endl;
        if (tableBase.size() > 0) {
            for (int i = 0; i < tableBase[0].columnData.size(); i++) {
                for (int j = 0; j < columnsNames.size(); j++) cout << tableBase[j].columnData[i] << " ";
                cout << endl;
            }
        }
        else cout << "\nThe table is empty.\n";
    };

    /*
    * 1) Добавить строку
    * 2) Добавить столбец - не вышло, непонятно почему ошибка
    * 3) Удалить строку
    * 4) Удалить столбец
    * 5) Изменить ячейку данных
    */


    //1) Добавить строку
    void addRow(vector<string> data) {
        for (int i = 0; i < data.size(); i++) tableBase[i].columnData.push_back(data[i]);
        //cout << "1000000000000000";
    }

    /*
    //2) Добавить столбец
    void addColumn(string columnName) {
        vector<string> data;
        for (int i = 0; i < tableBase[0].columnData.size(); i++) {
            data.push_back("-");
        }
        cout << endl << "\t" << tableBase[0].columnData.size() << "\t" << data.size();
        Column col = Column(columnName, data);
        cout << endl << "\t" << tableBase[0].columnData.size() << "\t" << col.columnData.size();
        columnsNames.push_back(col.columnName);
        tableBase.push_back(col);
        cout << endl << "\t" << tableBase[0].columnData.size() << "\t" << tableBase[-1].columnData.size();

        //cout << "1000000000000000";
    }
    */

    //3) Удалить строку
    void deleteRow(){
        cout << "1000000000000000";
    }
    //4) Удалить столбец
    void deleteColumn() {
        cout << "1000000000000000";
    }
    //5) Изменить ячейку данных
    void changeData(string newDataValue, string rIndex = "", string cIndex = "") {
        int rowIndex = stoi(rIndex)-1, columnIndex = stoi(cIndex)-1;

        for (int i = 0; i < tableBase[0].columnData.size(); i++) {

            for (int j = 0; j < columnsNames.size(); j++) {
                if (i == rowIndex && j == columnIndex) {
                    tableBase[j].columnData[i] = newDataValue;
                    break;
                }
                //cout << tableBase[j].columnData[i] << " ";
            }
        }
    }

    // конструктор
    Table(string pathToFile = "", string tableName = "", vector <string> columnsNames = {}, vector <Column> tableBase = { {} }) {
        this -> pathToFile = pathToFile;
        this -> tableName = tableName;
        this -> columnsNames = columnsNames;
        this -> tableBase = tableBase;
    } 
};

////////////////////////////////////GLOBAL VARIABLES/////////////////////////////////////

Table students = Table("table_Students.txt", "Students");
Table courses = Table("table_Courses.txt", "Courses");
Table grades = Table("table_Grades.txt", "Grades");

int idsForStudents = 0;
int idsForCourses = 0;
int idsForGrades = 0;

//////////////////////////////FUNCTIONS////////////////////////////////////


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

void readTheTables(Table* tableN) {

    ifstream fin;
    fin.open((*tableN).pathToFile);

    if (!fin.is_open()) {
        cout << "Eror ><. Please restart the programm." << endl;
        fin.close();
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
    //(*tableN).showTheTable();
    fin.close();
}

void updateTheTableFile(Table* tableN) {
    ofstream fout;
    fout.open((*tableN).pathToFile);

    fout << "Name: " << (*tableN).tableName;
    fout << "\nData:\n";

    for (int i = 0; i < (*tableN).columnsNames.size(); i++) fout << (*tableN).columnsNames[i] << " ";
    fout << endl;
    //if ((*tableN).tableBase.size() != 0) {
    //cout << endl << (*tableN).tableBase[0].columnData.size() << endl;
    //cout << endl << (*tableN).columnsNames.size() << endl;

    for (int i = 0; i < (*tableN).tableBase[0].columnData.size(); i++) {
        for (int j = 0; j < (*tableN).columnsNames.size(); j++) {
            //cout << endl << i << "\t" << j << "\t" << (*tableN).tableBase[j].columnData[i];
            fout << (*tableN).tableBase[j].columnData[i] << " ";
        }
        fout << endl;
    }

    fout.close();
}

void performRequest(Table* workingTable, string request) {

    /*
    if (tableN == "Students") workingTable = &students;
    else if (tableN == "Courses") workingTable = &courses;
    else if (tableN == "Grades") workingTable = &grades;
    */

    // 1) Добавить строку (студента, оценку, столбец) - DONE
    if (request == "1") {
        vector<string> data;
        // пока непонятно как вводить что то кроме данных базовых столбцов
        if (workingTable == &students) {
            //id Last_Name First_Name Age Class
            string id = to_string(idsForStudents), lastName = "", firstName = "", age = "", clas = "";
            idsForStudents += 1;
            cout << "Enter data separated by a space in format : Last_Name, First_Name, Age, Class.\n"; 
            //for (int i = 0; i < (*workingTable).columnsNames.size(); i++) cout << (*workingTable).columnsNames[i] << " ";
            cin >> lastName >> firstName >> age >> clas;
            data.push_back(id);
            data.push_back(lastName);
            data.push_back(firstName);
            data.push_back(age);
            data.push_back(clas);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");
        }
        else if (workingTable == &courses) {
            // id Course_name
            string id = to_string(idsForCourses), courseName = "";
            idsForCourses += 1;                                           // возможно пробдема с id до того момента пока не сделаю бесконечный запрос
            cout << "Enter course's name.\n";  
            //for (int i = 0; i < (*workingTable).columnsNames.size(); i++) cout << (*workingTable).columnsNames[i] << " ";
            cin >> courseName;
            data.push_back(id);
            data.push_back(courseName);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");
        }
        else if (workingTable == &grades) {
            //id id_Student id_Course Grade
            string id = to_string(idsForGrades), idStudent = "", idCourse = "", grade = "";
            idsForGrades++;
            cout << "Enter data separated by a space in format : id_Student, id_Course, Grade.\n";   
            cin >> idStudent >> idCourse >> grade;
            data.push_back(id);
            data.push_back(idStudent);
            data.push_back(idCourse);
            data.push_back(grade);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");
        }

        (*workingTable).addRow(data);
        updateTheTableFile(workingTable);
        //(*workingTable).showTheTable();
    }

    /*
    // 2) Добавить столбец 
    else if (request == "2") {
        cout << "\nEnter column name.\n";
        string columnName;
        cin >> columnName;
        cout << (*workingTable).tableBase[0].columnData.size() << "\t" << (*workingTable).tableBase[(*workingTable).tableBase.size()-1].columnData.size() << endl;
        //(*workingTable).showTheTable();
        (*workingTable).addColumn(columnName);
        cout << (*workingTable).tableBase[0].columnData.size() << "\t" << (*workingTable).tableBase[(*workingTable).tableBase.size() - 1].columnData.size() << endl;
        (*workingTable).showTheTable();
        updateTheTableFile(workingTable);
        (*workingTable).showTheTable();
    }
    */

    // 3) Удалить строку
    else if (request == "3") {
        (*workingTable).deleteRow();
    }
    // 4) Удалить столбец
    else if (request == "4") {
        (*workingTable).deleteColumn();
    }
    // 5) Изменить ячейку данныx - DONE
    else if (request == "5") {
        cout << "\nEnter the row's and column's number of the box you want to change separated by a space (for example: 0 0).\n";
        string rowIndex = "", columnIndex = "";
        cin >> rowIndex >> columnIndex;
        cout << "\nEnter new data value.\n";
        string newDataValue = "";
        cin >> newDataValue;
        (*workingTable).changeData(newDataValue, rowIndex, columnIndex);
        updateTheTableFile(workingTable);
    }
}

void offerOptionsForTable(string tableN = "") {

    Table* workingTable = 0;
    if (tableN == "Students") workingTable = &students;
    else if (tableN == "Courses") workingTable = &courses;
    else if (tableN == "Grades") workingTable = &grades;
    
    cout << "\nPlease, opt for the command you would like to perform and input the number of chosen option (for example: 1).\n";
    /*
    * 1) Добавить строку
    * 2) Добавить столбец
    * 3) Удалить строку
    * 4) Удалить столбец
    * 5) Изменить ячейку данных
    */
    cout << "\n1) Add the row."; // Добавить строку
    //cout << "\n2) Add the column."; // Добавить столбец
    cout << "\n3) Delete the row."; // Удалить строку
    cout << "\n4) Delete the column."; // Удалить столбец
    cout << "\n5) Change the data.\n"; // Изменить ячейку данных

    string request = "";
    cin >> request;
    performRequest(workingTable, request);
}

void getGPA(string studentID, string coursetID) { // Добавить проверку есть ли вообще такой студент
    int indexIdStudent = 0, indexIdCourse = 0, indexGrade = 0;
    for (int i = 0; i < grades.columnsNames.size(); i++) {
        if (grades.columnsNames[i] == "id_Student") indexIdStudent = i;
        else if (grades.columnsNames[i] == "id_Course") indexIdCourse = i;
        else if (grades.columnsNames[i] == "Grade") indexGrade = i;
    }

    float sumGrades = 0, countGrades = 0;
    if (grades.tableBase.size() > 0) {
        for (int i = 0; i < grades.tableBase[0].columnData.size(); i++) {
            if (grades.tableBase[indexIdStudent].columnData[i] == studentID
                && grades.tableBase[indexIdCourse].columnData[i] == coursetID) {  // по хорошему добавить инфу про то, что у нас поле с оценкой не пустое
                sumGrades += stoi(grades.tableBase[indexGrade].columnData[i]);
                countGrades += 1;
            }
        }
        float GPA = sumGrades / countGrades;
        cout << endl << setprecision(3) << GPA << endl;

    }
    else  cout << "\nThe table is empty.\n";
}

bool offerOptions() {

    cout << "\nPlease, choose what you would like to to do and type the number of chosen option (for example: 1).\n";
    cout << "\n1) Show table."; // Показать таблицу
    cout << "\n2) Show all tables."; // Показать все таблицы
    cout << "\n3) Get the student's GPA."; // получить средний балл ученика
    cout << "\n4) Change the table."; // Изменить таблицу
    cout << "\n5) Finish work and exit.\n"; // Завершить работу программы

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
        return true;
    }
    // Показать все таблицы - DONE
    else if (request == "2") {
        students.showTheTable();
        cout << endl;
        courses.showTheTable();
        cout << endl;
        grades.showTheTable();
        cout << endl;
        return true;
        // cout << "\nIf you want to exit, type down the code -1 (for example: -1).";
    }
    // получить средний балл ученика - DONE
    else if (request == "3") {
        cout << "\nPlease, enter student's ID and subject's ID separated by a space.\n";
        string studentID = "", subjectID = "";
        cin >> studentID >> subjectID;
        getGPA(studentID, subjectID);
        return true;
        // cout << "\nIf you want to exit, type down the code -1 (for example: -1).";
    }
    // Изменить таблицу
    else if (request == "4") {
        cout << "\nPlease, enter the table's name you would like to change:  Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;
        offerOptionsForTable(tableN);
        return true;
        //        if (tableN == "Students") students.showTheTable();
        //        else if (tableN == "Courses") courses.showTheTable();
        //        else if (tableN == "Grades") grades.showTheTable();
    }
    else if (request == "5") {
        cout << endl << "Goodbye!..................\n";
        return false;
    }
}

/*ヾ(-_- )ゞ
* [¬º-°]¬
* 👋🏻
* (⊃｡•́‿•̀｡)⊃
*/

void getRequest() {
    bool request = true;
    while (request == true) request = offerOptions();
}

void getTables() {  // считываем таблицы в самом начале
    readTheTables(&students);
    readTheTables(&courses);
    readTheTables(&grades);
}

//void setTables(){} // записываем таблицы обратно в файл в самом конце

void startOfProg() {

    // считываем таблицы из файлов
    getTables();
    // приветствие
    cout << "Welcome to the Data Base.\n";
    // предлагаем выбор опций
    getRequest();
}

//////////////////////////////////////////////////////////////////


int main()
{
    startOfProg(); // сделать бесконечный ввод команд

    return 0;
}