#include "database_helper.h"

int main(){

    DBHelper db;
    Person *p1 = new Person("surya","7010450504","12");

    db.save(*p1);

    db.load();

    return 1;
}