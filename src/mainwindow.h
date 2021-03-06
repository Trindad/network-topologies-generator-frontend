#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string appPath;

private slots:
    void on_pushButton_clicked();

    void on_fixedRegions_clicked();

    void on_fexibleRegions_clicked();

    void on_measures_clicked();

    void on_help_clicked();

    void openNewWindow();

private:
    Ui::MainWindow *ui;
    About *aboutWindow;
};

#endif // MAINWINDOW_H
