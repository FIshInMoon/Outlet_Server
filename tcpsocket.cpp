#include "tcpsocket.h"
#include <QDebug>


extern pack onepack;
extern UINT32 AllEventCount;


tcpSocket::tcpSocket(int h,QObject *parent) :
    QTcpSocket(parent)
{
    setSocketDescriptor(h);

    connect(this, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
    connect(this, SIGNAL(readyRead()), this, SLOT(on_socket_readyRead()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displaySocketError(QAbstractSocket::SocketError)));
}


void tcpSocket::displaySocketError(QAbstractSocket::SocketError e)
{
    qDebug() << "Error: " << e << "\n\t" << errorString();

}

bool tcpSocket::mkNewFile(QString socket_getSaveFileName)
{
    fileName = QString::fromUtf8((const char*)onepack.data,onepack.len);

    QString newFileName = fileName;

    qDebug()<<"get file name:"<<newFileName;

    while(file.exists(socket_getSaveFileName))
    {

        file.remove(fileName);
    }

    file.setFileName(socket_getSaveFileName);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<file.errorString();
        qDebug() << "Can not open file " << file.fileName() << ".";
//        throw 2;
        return false;
    }

    return true;

}

bool tcpSocket::getFileSize()
{

    talFileSize = onepack.data[0];
    talFileSize += onepack.data[1]<<8;
    talFileSize += onepack.data[2]<<16;
    talFileSize += onepack.data[3]<<24;

}

void tcpSocket::getFileEOF()
{
    qDebug()<<"file finish";
    file.close();
    disconnectFromHost();
}

bool tcpSocket::getFileData()
{

    if(file.isOpen())
    {
        file.write((const char *)onepack.data,onepack.len);
        file.flush();

        return true;

    }
    else
        return false;

}

void tcpSocket::sendEventNum(UINT16 eventNum)
{
    UINT8 data[2];

    data[0] = eventNum&0xff;
    data[1] = (eventNum>>8)&0xff;
    UINT64 len = FormCMD(SOCKET_CMD_EVENT_NUM,data,2,TxBuffer);

    write((const char *)TxBuffer,len);
}

extern UINT32 AllEventCount;

extern QStringList filenamelist;
enum{

    FILENAME,
    FILESIZE,
    FILEDATA,
    FILEEOF,
};
int nowfileno = -1;
int sta = FILENAME;
QFile file;
QDataStream in;
int allfilesize;
int nowfilesize;
void tcpSocket::sendFile()
{
    UINT8 data[PACK_MAX_LEN];
    char * data2;
    UINT32 datalen;



#if 0
    for(int i=0; i<AllEventCount;i++)
    {
        QFile file(filenamelist.at(i));
        if(!file.open(QIODevice::ReadOnly))
        {
         qDebug()<<"打开文件错误";
         return ;
        }

        QByteArray ba =  filenamelist.at(i).mid(filenamelist.at(i).lastIndexOf("/")+1).toLatin1();
        data2 = ba.data();

        datalen = filenamelist.at(i).length()-(filenamelist.at(i).lastIndexOf("/")+1);
        UINT32 TxLen = FormCMD(SOCKET_CMD_FILENAME,(UINT8*)data2,datalen,TxBuffer);
        write((const char*)TxBuffer,TxLen);


        data[0] = file.size()&0xff;
        data[1] = (file.size()>>8)&0xff;
        data[2] = (file.size()>>16)&0xff;
        data[3] = (file.size()>>24)&0xff;
        TxLen = FormCMD(SOCKET_CMD_FILE_SIZE,(UINT8*)data,4,TxBuffer);
        write((const char*)TxBuffer,TxLen);

        QDataStream in(&file);
        UINT32 filesize = file.size();

        for(UINT32 cnt = 0,l =0;cnt<filesize;cnt++,l++)
        {
            in>>data[l];
            if(l == 2000 || cnt == (filesize-1))
            {
                TxLen = FormCMD(SOCKET_CMD_FILE_DATA,(UINT8*)data,l+1,TxBuffer);
                write((const char*)TxBuffer,TxLen);
                l=0;
            }
        }

        TxLen = FormCMD(SOCKET_CMD_FILE_EOF,(UINT8*)data,0,TxBuffer);
        write((const char*)TxBuffer,TxLen);
        qDebug()<<"SOCKET_CMD_FILE_EOF";

    }
#else

    int l=0;
    QByteArray ba;
    UINT32 TxLen;

    if(nowfileno>=AllEventCount||AllEventCount==0||nowfileno<0)
    {
        qDebug()<<"文件发送完了,或者没有文件";
        return;
    }

    switch (sta)
    {
    case FILENAME:
        qDebug()<<"FILENAME";
        file.setFileName(filenamelist.at(nowfileno));
        if(!file.open(QIODevice::ReadOnly))
        {
         qDebug()<<"打开文件错误";
         return ;
        }

        ba =  filenamelist.at(nowfileno).mid(filenamelist.at(nowfileno).lastIndexOf("/")+1).toLatin1();
        data2 = ba.data();
        datalen = filenamelist.at(nowfileno).length()-(filenamelist.at(nowfileno).lastIndexOf("/")+1);
        TxLen = FormCMD(SOCKET_CMD_FILENAME,(UINT8*)data2,datalen,TxBuffer);
        write((const char*)TxBuffer,TxLen);
        sta = FILESIZE;
        break;
    case FILESIZE:
        qDebug()<<"FILESIZE";

        data[0] = file.size()&0xff;
        data[1] = (file.size()>>8)&0xff;
        data[2] = (file.size()>>16)&0xff;
        data[3] = (file.size()>>24)&0xff;
        TxLen = FormCMD(SOCKET_CMD_FILE_SIZE,(UINT8*)data,4,TxBuffer);
        write((const char*)TxBuffer,TxLen);

        in.setDevice(&file);
        allfilesize = file.size();
        nowfilesize = 0;

        sta = FILEDATA;
        break;
    case FILEDATA:
        qDebug()<<"FILEDATA";

        if(allfilesize-nowfilesize>1000)
        {
            for(l=0;l<1000;l++)
            {
                in>>data[l];
            }
            nowfilesize+=1000;
            TxLen = FormCMD(SOCKET_CMD_FILE_DATA,(UINT8*)data,l+1,TxBuffer);
            write((const char*)TxBuffer,TxLen);
        }
        else
        {
            for(l=0;l<allfilesize-nowfilesize;l++)
            {
                in>>data[l];
            }
            nowfilesize+=allfilesize-nowfilesize;
            TxLen = FormCMD(SOCKET_CMD_FILE_DATA,(UINT8*)data,l+1,TxBuffer);
            write((const char*)TxBuffer,TxLen);
            sta = FILEEOF;
        }
        break;
    case FILEEOF:
        qDebug()<<"FILEEOF";

        file.close();
        nowfileno++;

        TxLen = FormCMD(SOCKET_CMD_FILE_EOF,(UINT8*)data,0,TxBuffer);
        write((const char*)TxBuffer,TxLen);

        sta = FILENAME;

        break;
    }

#endif
}

QByteArray lastBuf;//分包的剩余留在外面了，下次做到socketprotpcol里
int lastlen = 0;

void tcpSocket::on_socket_readyRead()
{
    int len = bytesAvailable();
    len +=lastlen;
    int getlen = 0;





    QByteArray data = readAll();
    qDebug()<<"TCPdata->"<<data.toHex();
    data.insert(0,lastBuf);
    char* dat = data.data();

    while(1)
    {


        if(getData((UINT8 *)(dat+getlen),len))
        {
            getlen += onepack.len+PACK_LEN_LEN+PACK_CMD_LEN;
            len -= onepack.len+PACK_LEN_LEN+PACK_CMD_LEN;
            switch (onepack.cmd) {
            case SOCKET_CMD_FILENAME:
                mkNewFile(".\download.bin");
                break;

            case SOCKET_CMD_FILE_SIZE:
                getFileSize();
                break;

            case SOCKET_CMD_FILE_DATA:
                getFileData();
                break;
            case SOCKET_CMD_FILE_EOF:
                getFileEOF();
                break;
            case SOCKET_CMD_IMHERE:
                sendEventNum(AllEventCount);
                if(AllEventCount>0)
                    nowfileno = 0;//初始化已发文件数目
                break;
            case SOCKET_CMD_GET:
                sendFile();
                break;
            }
        }
        else
            break;

    }

    lastlen = len;
    lastBuf = data.remove(0,getlen);


}

void tcpSocket::socket_disconnected()
{

    close();
}




