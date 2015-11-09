#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "tcpserver.h"
#include "windows.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newconnectWrite2ui(QString clientName);
    void clientDisconnect();

    void on_BtnStartListen_clicked();

    void on_BtnAddFile_clicked();

    void on_TabelFileList_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    bool ServerIsStart;
    Tcpserver *Server;
};

#endif // MAINWINDOW_H
