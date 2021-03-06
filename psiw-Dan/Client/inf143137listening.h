#ifndef LISTENING_H
#define LISTENING_H
#include "inf143137client.h"
#include "inf143137bool.h"
#include <gdk/gdk.h>


typedef struct ListeningThreadsInfo
{
    guint notificationThread;
    guint messageThread;

    volatile Bool stopNotThread;
    volatile Bool stopMessageThread;

} ListeningThreadsInfo;

int listening_notification(void *arg);
int listening_message(void *arg);

extern ListeningThreadsInfo listeningThreads;

#endif // LISTENING_H
