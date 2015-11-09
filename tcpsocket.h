#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include "socketprotocol.h"

class tcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit tcpSocket(int h, QObject *parent = 0);


    void sendEOF();
    void fileSize(qint64 size);

signals:

public slots:

    void displaySocketError(QAbstractSocket::SocketError e);
    void on_socket_readyRead();
    void socket_disconnected();



private:
    bool mkNewFile(QString socket_getSaveFileName);
    bool getFileSize();
    bool getFileData();
    void getFileEOF();
    void sendEventNum(UINT16 eventNum);
    void sendFile();

    UINT32 talFileSize;
    QFile file;
    QString fileName;


    UINT8 TxBuffer[PACK_MAX_LEN];
};

#endif // TCPSOCKET_H
