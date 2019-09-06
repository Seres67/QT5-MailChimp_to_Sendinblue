#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

typedef struct convert {
    const char *base;
    const char *convert;
} convert_t;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void loadFile();
private slots:
    void on_locatebtn_pressed();
    void on_convertbtn_pressed();

};

#endif // MAINWINDOW_HPP
