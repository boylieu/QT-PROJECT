#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rdv.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_ajouter_clicked();

    void on_le_num_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_rdv_supp_clicked();

    void on_bt_aff_clicked();

    void on_bt_mod_clicked();

    void on_confirmer_clicked();

private:
    Ui::MainWindow *ui;
    Rdv R;
};
#endif // MAINWINDOW_H
