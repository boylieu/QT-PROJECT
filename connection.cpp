#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("Seif");
db.setPassword("esprit18");

if (db.open())
test=true;


else throw QString ("Erreur Paramétres"+db.lastError().text());


    return  test;
}
void Connection::closeConnection(){ db.close();}
