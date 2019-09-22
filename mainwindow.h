#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QPair>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString VT;
    QString VN;
    QString VN_first;
    int max_len;
    int min_len;
    QVector<QPair<QString, QString>> all_rule;
    bool rigthD;
    QString str_lab2;
    bool good_str;

public:
    void init();
    void show_all_rule();
    void fn(QString str);
    void fn2(QString str);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_reload_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_clear_clicked();

    void on_spinBox_max_valueChanged(int arg1);

    void on_spinBox_min_valueChanged(int arg1);

    void on_radioButton_rigth_clicked();

    void on_radioButton_left_clicked();

    void on_pushButton_clear_2_clicked();

    void on_pushButton_run_clicked();

    void on_pushButton_go_lab2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
