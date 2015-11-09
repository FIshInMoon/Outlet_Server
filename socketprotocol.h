/**********************************************
应用层自定义协议分成两级，事件和帧

Event
一个事件包含n个帧,例如发送文件为一个事件
            SOCKET_CMD_FILENAME
            SOCKET_CMD_FILE_SIZE
            SOCKET_CMD_FILE_DATA
                    .
                    .
                    .
            SOCKET_CMD_FILE_DATA
            SOCKET_CMD_FILE_EOF

Frame
一个帧包包含，len,cmd,data
       len：帧的总长len（4字节）+cmd（1）+data(n)
       cmd：命令字节，用下列枚举
       data：依据帧的类型自行填充或解析
       |             |                       |             |
       |  len        | cmd                   | data        |   ->   16进制序列，数字低位在前
       |  0x00000000 | 0x00                  | 0x0...      |

       |  0x0000000d | SOCKET_CMD_FILENAME   | "test.bin"  |   ->   0b 00 00 00 01 74 65 73 74 2e 62 69 6e
       |  0x00000009 | SOCKET_CMD_FILE_SIZE  | 53432 Bytes |   ->   09 00 00 00 02 b8 d0 00 00
       |  0x???????? | SOCKET_CMD_FILE_DATA  | 0x??..      |   ->   ?? ?? ?? ?? 03 ?? ?? ?? ??...
       |  0x00000005 | SOCKET_CMD_FILE_EOF   |             |   ->   05 00 00 00 04
                                .
                                .
                                .



------------一个访问过程-------------------
client->server
    SOCKET_CMD_IMHERE

server->client
    SOCKET_CMD_EVENT_NUM      如果事件数量为0，则客户端可自行断开连接
                              如果事件数不为0，则继续发送事件的帧（目前只有送文件事件）

    送文件事件1
    SOCKET_CMD_FILENAME
    SOCKET_CMD_FILE_SIZE
    SOCKET_CMD_FILE_DATA
            .
            .
            .
    SOCKET_CMD_FILE_DATA
    SOCKET_CMD_FILE_EOF

    送文件事件2
    SOCKET_CMD_FILENAME
    SOCKET_CMD_FILE_SIZE
    SOCKET_CMD_FILE_DATA
            .
            .
            .
    SOCKET_CMD_FILE_DATA
    SOCKET_CMD_FILE_EOF
            .
            .
            .
            直到所有事件完成

**********************************************/

#ifndef SOCKETPROTOCOL_H
#define SOCKETPROTOCOL_H
#include "windows.h"

#define PACK_LEN_LEN 4
#define PACK_CMD_LEN 1
#define PACK_MAX_LEN 2048


enum
{
    //server -> client
    SOCKET_CMD_FILENAME = 0x01, //发送文件名
    SOCKET_CMD_FILE_SIZE,       //发送文件大小
    SOCKET_CMD_FILE_DATA,       //发送文件数据
    SOCKET_CMD_FILE_EOF,        //文件发送完成
    SOCKET_CMD_EVENT_NUM,       //服务器端存在n个事件要和客户端处理

    //client -> server
    SOCKET_CMD_IMHERE,          //客户端定时访问包,即问服务器有没有事件要处理，诺返回的SOCKET_CMD_EVENT_NUM包有数据，则请保持连接
    SOCKET_CMD_INFO,

};

typedef struct {
    UINT32 len;
    UINT8 cmd;
    UINT8  data[PACK_MAX_LEN];
}pack;




bool getData(UINT8 * buf, UINT32 len);

UINT32 FormCMD(UINT8 cmd,UINT8* data,UINT32 datalen,UINT8 * buf);






#endif // SOCKETPROTOCOL_H
