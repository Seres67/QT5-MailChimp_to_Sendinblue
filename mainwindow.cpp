#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <iostream>
#include <fstream>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

static const convert_t CONVERT_TAB[] = {
        {"*|UNSUB|*",            "{{ unsubscribe }}"},
        {"*|ARCHIVE|*",          "{{ mirror }}"},
        {"*|MC:SUBJECT|*",       ""},
        {"*|MC_PREVIEW_TEXT|*",  ""},
        {"*|UPDATE_PROFILE|*",   "{{ update_profile }}"},
        {"*|EMAIL|*",            "{{ contact.EMAIL }}"},
        {"*|LIST:ADDRESSLINE|*", "REDACTED"},
        {"*|REWARDS|*",          ""},
        {"*|ABOUT_LIST|*",       ""},
        {"*|", ""}
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_locatebtn_pressed()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath());
    ui->pathview->setPlainText(file);
}

void MainWindow::on_convertbtn_pressed()
{
    std::string filename(ui->pathview->toPlainText().toStdString());

    if (filename.empty()) {
        ui->pathview->setText("No File Selected");
        return;
    }
    if (filename.find(".html", 5) == std::string::npos) {
        ui->pathview->setText("File is not an html file");
        return;
    }
    std::ifstream file(filename);
    std::ofstream out(filename.substr(0, filename.find('.')) + "_sendinblue.html");
    std::string tmp;
    unsigned long pos;

    while (std::getline(file, tmp)) {
            for (auto convert : CONVERT_TAB)
                if (tmp.find(convert.base) != std::string::npos)
                    while ((pos = tmp.find(convert.base)) != std::string::npos)
                        tmp.replace(pos, strlen(convert.base), convert.convert);
            out << tmp << '\n';
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}
