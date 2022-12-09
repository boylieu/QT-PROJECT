#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("NADINE_DATABASE");//NADINE_DATABASE
db.setUserName("system");//system
db.setPassword("nad123");//nad123

if (db.open())
test=true;
    return  test;
}
