#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Column
class Column {
public:
    string columnName;
    // int columnSize;
    vector <string> columnData;
    // ссылка на другой столбец

    // конструктор
    Column(string columnName = "", vector <string> columnData = {}) {
        this->columnName = columnName;
        this->columnData = columnData;
    }

};

// Table
class Table {

public:
    string pathToFile;
    string tableName;
    vector <string> columnsNames;
    vector <Column> tableBase;

    // Показать таблицу
    void showTheTable() {

        // чтобы нормально выводилось погуглить setw в iomanip
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
    void deleteRow(int rowIndex) {
        for (int i = 0; i < columnsNames.size(); i++) {
            auto begin = tableBase[i].columnData.cbegin();
            tableBase[i].columnData.erase(begin + rowIndex, begin + rowIndex + 1);
        }
    }
    //4) Удалить столбец
    void deleteColumn() {
        cout << "1000000000000000";
    }
    //5) Изменить ячейку данных
    void changeData(string newDataValue, string rIndex = "", string cIndex = "") {
        int rowIndex = stoi(rIndex) - 1, columnIndex = stoi(cIndex) - 1;

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
    Table(string pathToFile = "", string tableName = "", vector <string> columnsNames = {}) {
        this->pathToFile = pathToFile;
        this->tableName = tableName;
        this->columnsNames = columnsNames;
        //this -> tableBase = tableBase;
    }
};

////////////////////////////////////GLOBAL VARIABLES/////////////////////////////////////

Table students = Table("table_Students.txt", "Students");
Table courses = Table("table_Courses.txt", "Courses");
Table grades = Table("table_Grades.txt", "Grades");
Table gpa = Table("table_gpa.txt", "GPA");

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
    //cout << endl;
    //for (int i = 0; i < (*tableN).columnsNames.size(); i++) cout << "/" << (*tableN).columnsNames[i] << "/";
    // создаем столбцы
    for (int i = 0; i < ((*tableN).columnsNames).size(); i++) {
        Column col = Column((*tableN).columnsNames[i]);
        //cout << "/" << i << "/";
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
        if(i != (*tableN).tableBase[0].columnData.size() - 1) fout << endl;
    }

    fout.close();
}

float getGPA(string studentID, string coursetID, int removedGrade = 0, int removedCount = 0) { // Добавить проверку есть ли вообще такой студент
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
        float GPA = (sumGrades - removedGrade) / (countGrades - removedCount);
        return GPA;
    }
    //else  cout << "\nThe table is empty.\n";
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

            // gpa работает
            vector<string> dataForGPA(gpa.columnsNames.size(), "0");
            string studentName = firstName + "_" + lastName[0] + ".";
            dataForGPA[0] = studentName;
            gpa.addRow(dataForGPA);

        }
        else if (workingTable == &courses) { // gpa  работает 
            string id = to_string(idsForCourses + 1), courseName = "";
            idsForCourses += 1;                                           
            cout << "Enter course's name.\n";  
            cin >> courseName;
            data.push_back(id);
            data.push_back(courseName);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");

            // добавить в названия колонок gpa название предмета
            gpa.columnsNames.push_back(courseName);
            // создаем вектор с нулями
            vector<string> dataForGPA(gpa.tableBase[0].columnData.size());
            for (int i = 0; i < dataForGPA.size(); i++) dataForGPA[i] = "0";
            // создаем колонку с вектором
            Column col = Column(courseName, dataForGPA);
            gpa.tableBase.push_back(col);

        }
        else if (workingTable == &grades) { // gpa работает
            string id = to_string(idsForGrades + 1), idStudent = "", idCourse = "", grade = "";
            idsForGrades++;
            cout << "Enter data separated by a space in format : id_Student, id_Course, Grade.\n";   
            cin >> idStudent >> idCourse >> grade;
            data.push_back(id);
            data.push_back(idStudent);
            data.push_back(idCourse);
            data.push_back(grade);
            for (int i = data.size(); i < (*workingTable).columnsNames.size(); i++) data.push_back("-");

            // Пересчитываем gpa
            float newGPA = getGPA(idStudent, idCourse, -stoi(grade), -1);

            //получили имя студента у которого удалится оценка 
            string studentFullName[2];
            string studentName;
            for (int i = 0; i < students.tableBase[0].columnData.size(); i++) {
                if (students.tableBase[0].columnData[i] == idStudent) {
                    studentFullName[0] = students.tableBase[1].columnData[i];
                    studentFullName[1] = students.tableBase[2].columnData[i];
                    break;
                }
            }
            studentName = studentFullName[0] + "_" + studentFullName[1][0] + ".";

            // ищем предмет и потом его название
            string courseName = "";
            for (int i = 0; i < courses.tableBase[1].columnData.size(); i++) {
                if (courses.tableBase[0].columnData[i] == idCourse) {
                    courseName = courses.tableBase[1].columnData[i];
                    break;
                }
            }

            // перезаписываем средний балл
            for (int i = 0; i < gpa.tableBase[0].columnData.size(); i++) {
                for (int j = 0; j < gpa.columnsNames.size(); j++) {
                    if (gpa.tableBase[0].columnData[i] == studentName && gpa.columnsNames[j] == courseName) {
                        gpa.tableBase[j].columnData[i] = to_string(ceil(newGPA * 100) / 100).substr(0,4);
                        break;
                    }
                }
            }
        }

        (*workingTable).addRow(data);
        updateTheTableFile(workingTable);
        updateTheTableFile(&gpa);
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
        
        if (workingTable == &students) {        // GPA работает
            string idOfSudent = (*workingTable).tableBase[0].columnData[rowIndex];
            vector<int> indexsToDelete;

            for (int i = 0; i < grades.tableBase[1].columnData.size(); i++) {
                if (grades.tableBase[1].columnData[i] == idOfSudent) indexsToDelete.push_back(i);
            }
            for (int i = 0; i < indexsToDelete.size(); i++) grades.deleteRow(indexsToDelete[i] - 1*i);


            string studentID = (*workingTable).tableBase[0].columnData[rowIndex];
            string studentName = (*workingTable).tableBase[1].columnData[rowIndex] + "_" + (*workingTable).tableBase[2].columnData[rowIndex][0] + ".";

            for (int i = 0; i < gpa.tableBase[0].columnData.size(); i++) {
                if (gpa.tableBase[0].columnData[i] == studentName) {
                    for (int j = 0; j < gpa.columnsNames.size(); j++) {
                        auto begin = gpa.tableBase[j].columnData.cbegin();
                        gpa.tableBase[j].columnData.erase(begin + i, begin + i + 1);
                        break;
                    }
                }
            }

        }
        else if (workingTable == &courses) {       // GPA работает
            string idOfCourse = (*workingTable).tableBase[0].columnData[rowIndex];
            vector<int> indexsToDelete;

            for (int i = 0; i < grades.tableBase[2].columnData.size(); i++) {
                if (grades.tableBase[2].columnData[i] == idOfCourse) indexsToDelete.push_back(i);
            }
            for (int i = 0; i < indexsToDelete.size(); i++) grades.deleteRow(indexsToDelete[i] - 1 * i);

            // обновляем таблицу с gpa
            string courseName = (*workingTable).tableBase[1].columnData[rowIndex];
            int courseIndex;

            for (int i = 0; i < gpa.columnsNames.size(); i++) {
                if (gpa.columnsNames[i] == courseName) {
                    courseIndex = i;
                    break;
                }
            }

            auto begin = gpa.columnsNames.cbegin();
            gpa.columnsNames.erase(begin + courseIndex, begin + courseIndex + 1);
            auto begin_1 = gpa.tableBase.cbegin();
            gpa.tableBase.erase(begin_1 + courseIndex, begin_1 + courseIndex + 1);
        }
        else if (workingTable == &grades) {  // GPA работает
            //получили оценку, которая удалится
            string grade = (*workingTable).tableBase[3].columnData[rowIndex];

            //получили имя студента у которого удалится оценка 
            string studentID = (*workingTable).tableBase[1].columnData[rowIndex];
            string studentFullName[2];
            string studentName;
            for (int i = 0; i < students.tableBase[0].columnData.size(); i++) {
                if (students.tableBase[0].columnData[i] == studentID) {
                    studentFullName[0] = students.tableBase[1].columnData[i];
                    studentFullName[1] = students.tableBase[2].columnData[i];
                    break;
                }
            }
            studentName = studentFullName[0] + "_" + studentFullName[1][0] + ".";

            // ищем предмет и потом его название
            string courseID = (*workingTable).tableBase[2].columnData[rowIndex];
            string courseName = "";

            for (int i = 0; i < courses.tableBase[1].columnData.size(); i++) {
                if (courses.tableBase[0].columnData[i] == courseID) {
                    courseName = courses.tableBase[1].columnData[i];
                    break;
                }
            }

            float newGPA = getGPA(studentID, courseID, stoi(grade), 1);

            // нужно пересчитать средний балл
            for (int i = 0; i < gpa.tableBase[0].columnData.size(); i++) {
                for (int j = 0; j < gpa.columnsNames.size(); j++) {
                    if (gpa.tableBase[0].columnData[i] == studentName && gpa.columnsNames[j] == courseName) {
                        gpa.tableBase[j].columnData[i] = to_string(ceil(newGPA * 100) / 100).substr(0, 4);
                        break;
                    }
                }
            }
        }
        (*workingTable).deleteRow(rowIndex);
        updateTheTableFile(workingTable);
        updateTheTableFile(&gpa);
    }

    /*
    // 4) Удалить столбец
    else if (request == "4") {
        (*workingTable).deleteColumn();
    }
    */

    // 5) Изменить ячейку данныx - DONE - добавить GPA
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
    bool x = false;
    while (!x) {
        if (request == "1" || request == "2" || request == "3") x = true;
        else{
            cout << "\nPlease, try again and input correct value.\n";
            cin >> request;
        }
    }

    performRequest(workingTable, request);
}

bool offerOptions() {

    cout << "\nPlease, choose what you would like to to do and type the number of chosen option (for example: 1).";
    cout << "\n1) Show table."; // Показать таблицу
    cout << "\n2) Show all tables."; // Показать все таблицы
    cout << "\n3) Get GPA-info."; // получить средний балл ученика
    cout << "\n4) Change table."; // Изменить таблицу
    cout << "\n5) Finish work and exit.\n"; // Завершить работу программы

    string request = "";
    cin >> request;
    bool x = false;
    while (!x) {
        if (request == "1" || request == "2" || request == "3" || request == "4" || request == "5") x = true;
        else {
            cout << "\nPlease, try again and input correct value.\n";
            cin >> request;
        }
    }

    // Показать таблицу - DONE
    if (request == "1") {
        cout << "\nPlease, enter the table name: Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;

        bool x = false;
        while (!x) {
            if (tableN == "Students" || tableN == "Courses" || tableN == "Grades") x = true;
            else {
                cout << "\nPlease, try again and input correct value.\n";
                cin >> request;
            }
        }

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
    }
    // получить средний балл ученика - DONE
    else if (request == "3") {
        gpa.showTheTable();
        return true;
    }
    // Изменить таблицу
    else if (request == "4") {
        cout << "\nPlease, enter the table's name you would like to change:  Students, Courses or Grades.\n";
        string tableN = "";
        cin >> tableN;

        bool x = false;
        while (!x) {
            if (tableN == "Students" || tableN == "Courses" || tableN == "Grades") x = true;
            else {
                cout << "\nPlease, try again and input correct value.\n";
                cin >> request;
            }
        }

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
    readTheTables(&gpa);
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