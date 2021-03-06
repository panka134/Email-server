#ifndef MSGBUF_H
#define MSGBUF_H
#include "inf143137msgtype.h"
#include "inf143137error.h"
#include "inf143137receiversmsg.h"
#include "inf143137sendersmsg.h"
#include "inf143137bool.h"

typedef union Wrapper_data
{
    Error error;
    RcvMsg rcvMsg;
    SndMsg sndMsg;
    Bool isNotification;
    char emptyData;

} Wrapper_data;

typedef struct msgbuf
{
    MsgType mtype;
    Wrapper_data data;

} Wrapper;

#endif // MSGBUF_H
