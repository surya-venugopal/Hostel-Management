#include "person.h"
#include <bits/stdc++.h>
#include <sqlite3.h>

using namespace std;

class DBHelper
{
    sqlite3 *DB;
    int exit = 0;

    bool createTable()
    {
        string sql = "CREATE TABLE persons(name TEXT, phone TEXT, roll TEXT)";
        char *messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error Create Table" << endl;
            return false;
        }
        else
        {
            cout << "Table created Successfully" << endl;
            return true;
        }
    }

    static int callback(void *data, int argc, char **value, char **colName)
    {
        int i;
        fprintf(stderr, "%s: ", (const char *)data);

        for (i = 0; i < argc; i++)
        {
            printf("%s = %s\n", colName[i], value[i] ? value[i] : "NULL");
        }

        printf("\n");
        return 0;
    }

public:
    DBHelper()
    {
        exit = sqlite3_open("PROC.db", &DB);

        if (exit)
        {
            std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            std::cout << "Opened Database Successfully!" << std::endl;
            if (createTable())
            {
                cout << "-------- SQL READY --------";
            }
        }
    }
    ~DBHelper()
    {
        sqlite3_close(DB);
    }

    bool save(Person person)
    {
        string sql = "INSERT INTO persons VALUES(\'" + person.getName() + "\',\'" + person.getPhone() + "\',\'" + person.getRoll() + "\');";
        char *messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error INSERT" << endl
                 << *messaggeError;
            return false;
        }
        else
        {
            cout << "VALUES INSERTED" << endl;
            return true;
        }
    }

    void load()
    {
        string data("CALLBACK FUNCTION");

        string sql("SELECT * FROM persons;");
        if (exit)
        {
            std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        }
        else
            std::cout << "Opened Database Successfully!" << std::endl;
        int rc = sqlite3_exec(DB, sql.c_str(), callback, (void *)data.c_str(), NULL);
        if (rc != SQLITE_OK)
            cerr << "Error SELECT" << endl;
        else
        {
            cout << "Operation OK!" << endl;
        }
        return;
    }
};