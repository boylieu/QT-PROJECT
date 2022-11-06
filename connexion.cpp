#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("NADINE_DATABASE");
db.setUserName("SYSTEM");
db.setPassword("nad123");

if (db.open())
test=true;
    return  test;
}
