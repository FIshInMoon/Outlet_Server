#include "tcpserver.h"
#include "tcpsocket.h"
#include <QThread>

Tcpserver::Tcpserver(QObject *parent) :
    QTcpServer(parent)
{
}

Tcpserver::~Tcpserver()
{
    close();
}

void Tcpserver::startServer()
{
    listen(QHostAddress::Any, 8080);
    qDebug() << "Server started on port 0.0.0.0:5234";
}

void Tcpserver::stopServer()
{
    close();
}

void Tcpserver::incomingConnection(int handle)
{
    QThread *newThread = new QThread();
    tcpSocket* client = new tcpSocket(handle, this);

    client->moveToThread(newThread);


    connect(client,SIGNAL(disconnected()),newThread,SLOT(quit()));
    connect(client,SIGNAL(disconnected()),this,SIGNAL(signal_clientDisconnect()));

    newThread->start();

    emit newconect(client->peerAddress().toString());
}

