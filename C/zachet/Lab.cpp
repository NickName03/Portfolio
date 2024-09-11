
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include ".\sql3\sqlite3.h"

void query(sqlite3_stmt* stmt, const char* title) {
    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    sqlite3_bind_text(stmt, 1, title, strlen(title), NULL);
    int step = sqlite3_step(stmt);
    int count = 0;
    while (step == SQLITE_ROW) {
        step = sqlite3_step(stmt);
        count++;
    }
    sqlite3_reset(stmt);
    for (int i = 0; i < count; i++) {
        step = sqlite3_step(stmt);
        char* c1 = (char*)sqlite3_column_text(stmt, 0);
        char* c2 = (char*)sqlite3_column_text(stmt, 1);
        printf("%c %c", c1[0], c2[0]);
    }
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    int rc = sqlite3_open("movies.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    const char* sql_query = "select Actor.act_fname, movie_cast.role "
        "From Actor, movie, movie_cast "
        "Where movie.mov_id = movie_cast.mov_id and movie_cast.act_id = Actor.act_id and movie.mov_title = ?; ";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);
    query(stmt, "Vertigo");
    if (rc != SQLITE_OK) {
        fprintf(stderr, "\n%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 2;
    }
    else { fprintf(stderr, "\nSQLITE_OK\n"); }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}


// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
