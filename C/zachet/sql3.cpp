#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include ".\sql3\sqlite3.h"

/*
Структура должна описывать результат запроса.
В ней должны находиться поля, которые возвращает запрос.
*/
struct Result {
    char* first_name;
    char* last_name;
    char* id_position;
    char* date;
    char* department_name;
};

/*
Функция выводит массив с результатами запроса в виде:
{имя, фамилия, id должности, дата приёма на работу, название отдела}
{имя, фамилия, id должности, дата приёма на работу, название отдела}
{имя, фамилия, id должности, дата приёма на работу, название отдела}
...
*/
void show_result(struct Result* result, int size) {
    if (size == 0) {
        printf("There is no data for this request");
    }
    for (int i = 0; i < size; i++) {
        printf("{%10s %15s %12s %11s %25s}\n",
            result[i].first_name,
            result[i].last_name,
            result[i].id_position,
            result[i].date,
            result[i].department_name);
    }
}


/*
Реализовать функцию, выполняющую параметрический запрос, описанный в функции main.
Функция должна выполнять подготовленный запрос, переданный во втором параметре;
в третьем и четвёртом параметре передаётся диапазон дат, который задаёт интересующий период найма сотрудника.
Функция не должна выводить что-то на терминал, результат должен записываться в массив dest,
память для которого выделяется в этой же функции. Функция возвращает размер массива dest (количество элементов)
или 0 в случае ошибки.
*/
int get_result(struct Result** dest, sqlite3_stmt* stmt, const char* lo_hire_date, const char* hi_hire_date) {
    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    sqlite3_bind_text(stmt, 1, lo_hire_date, strlen(lo_hire_date), NULL);
    sqlite3_bind_text(stmt, 2, hi_hire_date, strlen(hi_hire_date), NULL);
    int count = 0;
    int step = sqlite3_step(stmt);
    // находим кол-во строк в полученной выборке
    while (step == SQLITE_ROW) {
        step = sqlite3_step(stmt);
        count++;
    }
    //Вот тут нам известно сколько элементов будет в массиве. Выделяем память под count элементов
    (*dest) = (struct Result*)malloc(count * sizeof(struct Result));
    //И нужно сбросить выполнение запроса в начало, затем повторить выполнение, чтобы выбрать сами данные
    sqlite3_reset(stmt);
    for (int i = 0; i < count; i++) {
        step = sqlite3_step(stmt);
        char* c = (char*)sqlite3_column_text(stmt, 0);
        int size = sizeof(char*) * strlen(c);
        (*dest)[i].first_name = (char*)malloc(size);
        strcpy_s((*dest)[i].first_name, size, c);
        c = (char*)sqlite3_column_text(stmt, 1);
        size = sizeof(char*) * strlen(c);
        (*dest)[i].last_name = (char*)malloc(size);
        strcpy_s((*dest)[i].last_name, size, c);
        c = (char*)sqlite3_column_text(stmt, 2);
        size = sizeof(char*) * strlen(c);
        (*dest)[i].id_position = (char*)malloc(size);
        strcpy_s((*dest)[i].id_position, size, c);
        c = (char*)sqlite3_column_text(stmt, 3);
        size = sizeof(char*) * strlen(c);
        (*dest)[i].date = (char*)malloc(size);
        strcpy_s((*dest)[i].date, size, c);
        c = (char*)sqlite3_column_text(stmt, 4);
        size = sizeof(char*) * strlen(c);
        (*dest)[i].department_name = (char*)malloc(size);
        strcpy_s((*dest)[i].department_name, size, c);
    }
    return count;
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    int rc = sqlite3_open("hr.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /*
    Строка sql_query должна содержать запрос, который возвращает информацию о сотрудниках,
    которые были наняты в определённый период. Диапазон дат должен задаваться параметрами.
    Запрос должен возвращать имя, фамилию сотрудника, id должности, дату приёма на работу,
    название отдела, где работает сотрудник.
    */
    const char* sql_query = "Select employees.first_name, employees.last_name, "
        "employees.job_id, employees.hire_date, departments.department_name "
        "From employees, departments "
        "Where employees.department_id = departments.department_id and employees.hire_date between ? and ?;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 2;
    }

    //Код для проверки
    struct Result* result;
    int result_size = get_result(&result, stmt, "2007-11-05", "2009-07-05");
    printf("first query:\n");
    show_result(result, result_size);
    if (result_size > 0) {
        free(result);
    }

    result_size = get_result(&result, stmt, "2002-01-10", "2005-10-15");
    printf("\nsecond query:\n");
    show_result(result, result_size);
    if (result_size > 0) {
        free(result);
    }

    result_size = get_result(&result, stmt, "2006-11-05", "2008-07-30");
    printf("\nthird query:\n");
    show_result(result, result_size);
    if (result_size > 0) {
        free(result);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
