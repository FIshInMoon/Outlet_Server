#include "socketprotocol.h"
#include <QDebug>

UINT32 AllEventCount = 0;
pack onepack;

UINT8  UserCache_Buf[PACK_MAX_LEN];
UINT32 UserCache_Len=0;
UINT32 Pack_Len;


bool Unpacked(UINT8 * buf)
{
    onepack.cmd = buf[4];
    memcpy((char*)(onepack.data),(char *)(buf+5),Pack_Len-5);
    onepack.len = Pack_Len-5;
//        onepack.data[onepack.len-1] = '\0';



    return true;

}

bool getData(UINT8 * buf,UINT32 len)
{
    if(len>=4)//用户缓存空 及有新的包进入,
    {
        Pack_Len = buf[0];
        Pack_Len += buf[1]<<8;
        Pack_Len += buf[2]<<16;
        Pack_Len += buf[3]<<24;
    }
    else
    {
        UserCache_Buf;
        return false;
    }
    //将新包存入用户缓存

    qDebug()<<"Pack_Len"<<Pack_Len;

    if(len<Pack_Len)//被分包了
    {
        return false;
    }
    else
    {
        if(Unpacked(buf))//解析
        {
            return true;
        }
        else
            return false;
    }

}



UINT32 FormCMD(UINT8 cmd,UINT8* data,UINT32 datalen,UINT8 * buf)
{

    UINT32 cmdLen = datalen+5;
    buf[0] = cmdLen&0xff;
    buf[1] = (cmdLen>>8)&0xff;
    buf[2] = (cmdLen>>16)&0xff;
    buf[3] = (cmdLen>>24)&0xff;

    buf[4] = cmd;

    memcpy((char*)(buf+5),(char *)(data),datalen);

    return cmdLen;
}

