#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init()
{
    rigthD = true;

    VN = ui->lineEdit_VN->text();
    VT = ui->lineEdit_VT->text();

    max_len = ui->spinBox_max->value();
    min_len = ui->spinBox_min->value();

    ui->label_VN->setText(VN);
    ui->label_VT->setText(VT);

    QRegExp VNreg("^[A-Z,]+$");
    QRegExp VTreg("^[a-z,0-9]+$");
    //QRegExp lab2("^[" + VT.split(',', QString::SkipEmptyParts).join("") + "]+$");

    //QRegExpValidator *lab2regVal = new QRegExpValidator(lab2, this);
    //ui->lineEdit_inptG_lab2->setValidator(lab2regVal);


    QRegExp Preg("^[" + VN.split(',', QString::SkipEmptyParts).join("") + "]$");
    QRegExp rule_rigth_reg("^[" + VT.split(',', QString::SkipEmptyParts).join("") + "]*[" + VN.split(',', QString::SkipEmptyParts).join("") + "]?$");

    QRegExpValidator *RuleregVal = new QRegExpValidator(rule_rigth_reg, this);
    QRegExpValidator *PregVal = new QRegExpValidator(Preg, this);

    QRegExpValidator *VTregVal = new QRegExpValidator(VTreg, this);
    QRegExpValidator *VNregVal = new QRegExpValidator(VNreg, this);

    ui->lineEdit_VT->setValidator(VTregVal);
    ui->lineEdit_VN->setValidator(VNregVal);
    ui->lineEdit_Rule->setValidator(RuleregVal);
    ui->lineEdit_P->setValidator(PregVal);
    ui->lineEdit_Rule->clear();
    ui->lineEdit_P->clear();
}

void MainWindow::show_all_rule()
{
    ui->textEdit_AllRule->clear();
    for (QVector<QPair<QString, QString>>::iterator it = all_rule.begin(); it != all_rule.end(); it++) {
        ui->textEdit_AllRule->append(it->first + " -> " + it->second);
    }
}

void MainWindow::fn(QString str)
{
    if(rigthD) {
        if (str.length() <= max_len) {
            if (str.length() >= min_len && str.length() <= max_len)
                if(VN.split(',', QString::SkipEmptyParts).join("").indexOf(str.right(1)) == -1)
                    ui->textEdit_result->append(str);
            for (QVector<QPair<QString, QString>>::iterator iv = all_rule.begin(); iv != all_rule.end(); iv++) {
                if (iv->first == str.right(1)) {
                    fn(QString(str).replace(str.length() - 1, 1, iv->second));
                }
            }
        }
    } else {
        if (str.length() <= max_len) {
            if (str.length() >= min_len && str.length() <= max_len)
                if(VN.split(',', QString::SkipEmptyParts).join("").indexOf(str.left(1)) == -1)
                    ui->textEdit_result->append(str);
            for (QVector<QPair<QString, QString>>::iterator iv = all_rule.begin(); iv != all_rule.end(); iv++) {
                if (iv->first == str.left(1)) {
                    fn(QString(str).replace(0, 1, iv->second));
                }
            }
        }
    }
}

void MainWindow::fn2(QString str)
{
    //qDebug() << str;
    if (rigthD) {
        if (str != VN_first) {
            for (QVector<QPair<QString, QString>>::iterator iv = all_rule.begin(); iv != all_rule.end(); iv++) {
                //qDebug() << str.indexOf(iv->second) << iv->second << str.length();
                //qDebug() << str.lastIndexOf(iv->second) << iv->second << str.length();
                if (str.lastIndexOf(iv->second) == str.length() - iv->second.length()) {
                    fn2(QString(str).replace(str.lastIndexOf(iv->second), iv->second.length(), iv->first));
                }
            }
        } else {
            good_str = true;
            QMessageBox msg;
            msg.setWindowTitle("lab2");
            msg.setText("good!");
            msg.exec();
        }
    } else {
        if (str != VN_first) {
            for (QVector<QPair<QString, QString>>::iterator iv = all_rule.begin(); iv != all_rule.end(); iv++) {
                //qDebug() << str.indexOf(iv->second) << iv->second << str.length();
                //qDebug() << str.lastIndexOf(iv->second) << iv->second << str.length();
                if (str.indexOf(iv->second) == 0) {
                    fn2(QString(str).replace(0, iv->second.length(), iv->first));
                }
            }
        } else {
            good_str = true;
            QMessageBox msg;
            msg.setWindowTitle("lab2");
            msg.setText("good!");
            msg.exec();
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_VT->setText("0,1,a,b,c");
    ui->lineEdit_VN->setText("S,T");

    ui->spinBox_max->setValue(8);
    ui->spinBox_min->setValue(6);

    VN_first = "S";

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_reload_clicked()
{
    init();
}

void MainWindow::on_pushButton_Add_clicked()
{
    all_rule.push_back(QPair<QString, QString>(ui->lineEdit_P->text(), ui->lineEdit_Rule->text()));
    ui->lineEdit_P->clear();
    ui->lineEdit_Rule->clear();
    show_all_rule();
}

void MainWindow::on_pushButton_clear_clicked()
{
    all_rule.clear();
    ui->textEdit_AllRule->clear();
    ui->lineEdit_P->clear();
    ui->lineEdit_Rule->clear();
}

void MainWindow::on_spinBox_max_valueChanged(int arg1)
{
    max_len = arg1;
    if (max_len < min_len) {
        min_len = max_len;
        ui->spinBox_min->setValue(min_len);
    }
}

void MainWindow::on_spinBox_min_valueChanged(int arg1)
{
    min_len = arg1;
    if (max_len < min_len) {
        max_len = min_len;
        ui->spinBox_max->setValue(max_len);
    }
}


void MainWindow::on_radioButton_rigth_clicked()
{
    rigthD = true;
    ui->lineEdit_Rule->clear();
    QRegExp rule_rigth_reg("^[" + VT.split(',', QString::SkipEmptyParts).join("") + "]*[" + VN.split(',', QString::SkipEmptyParts).join("") + "]?$");
    QRegExpValidator *RuleregVal = new QRegExpValidator(rule_rigth_reg, this);
    ui->lineEdit_Rule->setValidator(RuleregVal);
}

void MainWindow::on_radioButton_left_clicked()
{
    rigthD = false;
    ui->lineEdit_Rule->clear();
    QRegExp rule_left_reg("^[" + VN.split(',', QString::SkipEmptyParts).join("") + "]?[" + VT.split(',', QString::SkipEmptyParts).join("") + "]*$");
    QRegExpValidator *RuleregVal = new QRegExpValidator(rule_left_reg, this);
    ui->lineEdit_Rule->setValidator(RuleregVal);
}

void MainWindow::on_pushButton_clear_2_clicked()
{
    ui->textEdit_result->clear();
}

void MainWindow::on_pushButton_run_clicked()
{
    fn(VN_first);

}

void MainWindow::on_pushButton_go_lab2_clicked()
{
    good_str = false;
    str_lab2 = ui->lineEdit_inptG_lab2->text();
    bool test = true;
    for (int i(0); i < str_lab2.length(); i++)
        if ((VT.split(',', QString::SkipEmptyParts).join("").indexOf(str_lab2.at(i))) == -1)
            test = false;

    if (test)
        fn2(str_lab2);
    else {
        good_str = true;
        QMessageBox msg;
        msg.setWindowTitle("lab2");
        msg.setText("invalid character!");
        msg.exec();
    }
    if (!good_str) {
        QMessageBox msg;
        msg.setWindowTitle("lab2");
        msg.setText("bad!");
        msg.exec();
    }
}
