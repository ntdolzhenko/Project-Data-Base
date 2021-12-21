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

public:
    string pathToFile;
    string tableName;
    vector <string> columnsNames;
    vector <Column> tableBase;

    // Показать таблицу
    void showTheTable() {    // чтобы нормально выводилось погуглить setw в iomanip
        cout << "Name: " << tableName << "\nData:" << endl;
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

    //1) Добавить строку
    void addRow(vector<string> data) {
        for (int i = 0; i < data.size(); i++) tableBase[i].columnData.push_back(data[i]);
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
    void deleteRow(int rowIndex){
        for (int i = 0; i < columnsNames.size(); i++) {
            auto begin = tableBase[i].columnData.cbegin(); 
            auto end = tableBase[i].columnData.cend();
            tableBase[i].columnData.erase(begin + rowIndex, begin + rowIndex + 1);
        }
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

int idsForStudents, idsForCourses, idsForGrades;

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

void readIDs() {
    ifstream fin;
    string line;

    fin.open("id_for_students.txt");
    getline(fin, line);
    idsForStudents = stoi(line);
    fin.close();

    //ifstream fin;
    fin.open("id_for_courses.txt");
    getline(fin, line);
    idsForCourses = stoi(line);
    fin.close();

    //ifstream fin;
    fin.open("id_for_grades.txt");
    getline(fin, line);
    idsForGrades = stoi(line);
    fin.close();

    //cout << endl << idsForStudents << "\t" << idsForCourses << "\t" << idsForGrades << endl;
}

void updateIDs() {
    //cout << endl << idsForStudents << "\t" << idsForCourses << "\t" << idsForGrades << endl;
    ofstream fout;
    fout.open("id_for_students.txt");
    fout << idsForStudents;
    fout.close();

    fout.open("id_for_courses.txt");
    fout << idsForCourses;
    fout.close();

    fout.open("id_for_grades.txt");
    fout << idsForGrades;
    fout.close();
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

    // 1) Добавить строку (студента, оценку, столбец) - DONE
    if (request == "1") {
        vector<string> data;
        if (workingTable == &students) {
            string id = to_string(idsForStudents + 1), lastName = "", firstName = "", age = "", clas = "";
            idsForStudents += 1;
            cout << "Enter data separated by a space in format : Last_Name, First_Name, Age, Class.\n"; 
            cin >> lastName >> firstName >> age >> clas;
            data.push_back(id);
            data.push_back(lastName);
            data.push_back(firstName);
            data.push_back(age);
            data.push_back(clas);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");
        }
        else if (workingTable == &courses) {
            string id = to_string(idsForCourses + 1), courseName = "";
            idsForCourses += 1;                                           
            cout << "Enter course's name.\n";  
            cin >> courseName;
            data.push_back(id);
            data.push_back(courseName);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");
        }
        else if (workingTable == &grades) {
            string id = to_string(idsForGrades + 1), idStudent = "", idCourse = "", grade = "";
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

    // 3) Удалить строку - DONE
    else if (request == "2") {
        cout << "\nEnter the row's index(!) you would like to delete.\n";
        string ind;
        cin >> ind;
        int rowIndex = stoi(ind);
        
        if (workingTable == &students) {
            string idOfSudent = (*workingTable).tableBase[0].columnData[rowIndex];
            vector<int> indexsToDelete;

            for (int i = 0; i < grades.tableBase[1].columnData.size(); i++) {
                if (grades.tableBase[1].columnData[i] == idOfSudent) indexsToDelete.push_back(i);
            }
            for (int i = 0; i < indexsToDelete.size(); i++) grades.deleteRow(indexsToDelete[i] - 1*i);
        }
        else if (workingTable == &courses) {
            string idOfCourse = (*workingTable).tableBase[0].columnData[rowIndex];
            vector<int> indexsToDelete;

            for (int i = 0; i < grades.tableBase[2].columnData.size(); i++) {
                if (grades.tableBase[2].columnData[i] == idOfCourse) indexsToDelete.push_back(i);
            }
            for (int i = 0; i < indexsToDelete.size(); i++) grades.deleteRow(indexsToDelete[i] - 1 * i);
        }
        (*workingTable).deleteRow(rowIndex);
        updateTheTableFile(workingTable);
    }

    /*
    // 4) Удалить столбец
    else if (request == "4") {
        (*workingTable).deleteColumn();
    }
    */

    // 5) Изменить ячейку данныx - DONE
    else if (request == "3") {
        cout << "\nEnter the row's and column's number(!) of the box you want to change separated by a space (for example: 0 0).\n";
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
    
    cout << "\nPlease, opt for the command you would like to perform and input the number of chosen option (for example: 1).";
    /*
    * 1) Добавить строку
    * 2) Добавить столбец
    * 3) Удалить строку
    * 4) Удалить столбец
    * 5) Изменить ячейку данных
    */
    cout << "\n1) Add row."; // Добавить строку
    //cout << "\n2) Add the column."; // Добавить столбец
    cout << "\n2) Delete row."; // Удалить строку
    //cout << "\n4) Delete the column."; // Удалить столбец
    cout << "\n3) Change data.\n"; // Изменить ячейку данных

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

    cout << "\nPlease, choose what you would like to to do and type the number of chosen option (for example: 1).";
    cout << "\n1) Show table."; // Показать таблицу
    cout << "\n2) Show all tables."; // Показать все таблицы
    cout << "\n3) Get student's GPA."; // получить средний балл ученика
    cout << "\n4) Change table."; // Изменить таблицу
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
        updateIDs();
        cout << endl << "Goodbye!..................\n";
        return false;
    }
}

void getRequest() {
    bool request = true;
    while (request == true) request = offerOptions();
}

void getTables() {  // считываем таблицы в самом начале
    readTheTables(&students);
    readTheTables(&courses);
    readTheTables(&grades);
}

void runProg() {

    // считываем таблицы из файлов
    getTables();
    // считываем id-шники
    readIDs();
    // приветствие
    cout << "Welcome to the Data Base.\n";
    // предлагаем выбор опций
    getRequest();
}

//////////////////////////////////////////////////////////////////

int main()
{
    runProg(); // сделать бесконечный ввод команд
    return 0;
}