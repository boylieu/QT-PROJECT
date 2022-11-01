#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
Connection::Connection()
{

}

bool Connection::createconnect()
{
 db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("projet");
db.setUserName("Soumaya");//inserer nom de l'utilisateur
db.setPassword("soumaya123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection::closeConnection(){db.close();}
