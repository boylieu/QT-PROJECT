#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "affaire.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
       Ui::MainWindow *ui;
private slots :
    void on_ajouter_clicked();



    void on_suprimer_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_modifier_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();
    void makePlot_Type();
    QVector<double> Statistique_Type();


    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:

    affaire aff;
};
#endif // MAINWINDOW_H
