#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>



class Tcpserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit Tcpserver(QObject *parent = 0);
    ~Tcpserver();

    void startServer();
    void stopServer();
protected:
    void incomingConnection(int handle);
signals:
    void newconect(QString ip);
    void signal_clientDisconnect();
public slots:

};

#endif // TCPSERVER_H
