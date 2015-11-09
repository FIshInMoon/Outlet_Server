#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*-------变量初始化----------*/
    ServerIsStart = false;

    /*-------实例化--------------*/
    Server = new Tcpserver();

    /*-------信号槽关联----------*/
    connect(Server,SIGNAL(newconect(QString)),this,SLOT(newconnectWrite2ui(QString)));
    connect(Server,SIGNAL(signal_clientDisconnect()),this,SLOT(clientDisconnect()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newconnectWrite2ui(QString clientName)
{
    ui->LineClientIP->setText(clientName);
}

void MainWindow::clientDisconnect()
{
    ui->LineClientIP->clear();
}

void MainWindow::on_BtnStartListen_clicked()
{
    if(!ServerIsStart)
    {
        //开始监听
        Server->startServer();
        ui->BtnStartListen->setText("停止监听");
        ServerIsStart = true;
    }
    else
    {
        //停止监听
        Server->stopServer();
        ui->BtnStartListen->setText("开始监听");
        ui->LineClientIP->clear();
        ServerIsStart = false;
    }
}


QStringList filenamelist;

void MainWindow::on_BtnAddFile_clicked()
{
    QStringList filelist = QFileDialog::getOpenFileNames(
        this,
        "选择文件",
        "./",
        "Document files ();;ALL file(*.*)");
    filenamelist += filelist;

    int OldTableRowCount = ui->TabelFileList->rowCount();//添加全的行数

    extern UINT32 AllEventCount;
    AllEventCount+=filelist.length();//一个文件一个事件
    ui->TabelFileList->setRowCount(OldTableRowCount + filelist.length());//总行数增加1

    for(int i=0; i<filelist.length();i++)
    {

        QTableWidgetItem *item0 = new QTableWidgetItem (filelist.at(i).mid(filelist.at(i).lastIndexOf("/")+1));
        ui->TabelFileList->setItem(OldTableRowCount+i, 0, item0);
        QTableWidgetItem *item1 = new QTableWidgetItem (filelist.at(i));
        ui->TabelFileList->setItem(OldTableRowCount+i, 1, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem ("删除");
        ui->TabelFileList->setItem(OldTableRowCount+i, 2, item2);

    }

}

void MainWindow::on_TabelFileList_cellClicked(int row, int column)
{
    if(column == 2)
    {
        filenamelist.removeAt(row);

        extern UINT32 AllEventCount;
        AllEventCount--;
        ui->TabelFileList->removeRow(row);
        qDebug()<<AllEventCount;
    }
}
