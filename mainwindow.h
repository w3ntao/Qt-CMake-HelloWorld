#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0) :
            QMainWindow(parent),
            ui(new Ui::MainWindow) {
        ui->setupUi(this);
    }

    ~MainWindow() {
        delete ui;
    }

private slots:

    void on_actionExit_triggered() {
        this->close();

    };

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
