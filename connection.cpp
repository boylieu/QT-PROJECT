#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    db = QSqlDatabase :: addDatabase("QODBC");
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projetqt");
db.setUserName("ouss");//inserer nom de l'utilisateur
db.setPassword("ouss");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection :: closeConnect(){db.close();}
