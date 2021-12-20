//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;

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

//class Table {
//private:

//    string tableName;
//    vector <string> columnsNames;
    // vector <Columns> columns;


//public:
//    void createTheBox() {};
//    void createTheData() {};
//    void deleteTheBox() {};
//    void deleteTheData() {};
//    void changeTheBox() {};
//    void changeTheData() {};
//    void addTheColumn() {};
//    void deleteTheColumn() {};
//    void showTheTable() {};
//    void GPA() {};

//};


//////////////////////////////ФУНКЦИИ////////////////////////////////////

//void getRequest() {
    //string request = "";
    // while(request != "Нет. Закрыть Базу Данных."){
    //     cin >> request;
    //     if(request == "1") createTheBox();
    //     else if (request == "2") createTheData();
    //     else if (request == "3") deleteTheBox();
    //     else if (request == "4") deleteTheData();
    //     else if (request == "5") changeTheBox();
    //     else if (request == "6") changeTheData();
    //     else if (request == "7") addTheColumn();
    //     else if (request == "8") deleteTheColumn();
    //     else if (request == "9") showTheTable();
    //     else if (request == "10") GPA();
    // }

//}

//void startOfProg() {
//    setlocale(LC_ALL, "Russian");
//    string request = "";
//    cout << "Добро пожаловать в Базу Данных. Пожалуйста, выберите действие, которое Вы хотели бы выполнить и введите номер выбранного действия.";
//    cout << "\n1) Создать поле.";
//    cout << "\n2) Записать данные.";
//    cout << "\n3) Удалить поле.";
//    cout << "\n4) Удалить данные.";
//    cout << "\n5) Изменить поле.";
//    cout << "\n6) Изменить данные.";
//    cout << "\n7) Добавить столбец.";
//    cout << "\n8) Удалить столбец.";
//    cout << "\n9) Показать таблицу.";
//    cout << "\n10) Получить информацию о среднем балле ученика.";

//    getRequest();
//    cout << "\nBye!";
//}

//////////////////////////////////////////////////////////////////

// Table students = Table();
// Table courses = Table();
// Table grades = Table();


