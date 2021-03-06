#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>

#define MAX 256
#include "../server/config.h"
#include "../server/mail.h"
#include "../server/server_base.c"
#include "../server/user.h"

void create_user(int sockfd)
{

    User user = {.id = 1, .username="", .password=""};
    Feedback feedback;
    char buff_username[MAX];
    char buff_password[MAX];
        bzero(buff_username, sizeof(buff_username));
        bzero(buff_password, sizeof(buff_password));
        printf("Enter the username : ");
        fgets(buff_username, MAX, stdin);
        buff_username[strcspn(buff_username,"\n")] ='\0';
        strcpy(user.username, buff_username);
        printf("Enter the password : ");
        fgets(buff_password, MAX, stdin);
        buff_password[strcspn(buff_password,"\n")] ='\0';
        strcpy(user.password, buff_password);
        send(sockfd, &user, sizeof(user), 0);
          recv(sockfd, &feedback, sizeof(feedback), 0);
          printf("Feedback: %d %s\n", feedback.feedback, feedback.message);
}

void send_message_user(int sockfd,User user)
{

    Mail mail = {.from = "", .to = "", .topic = "", .text = ""};
    Feedback feedback;
    char buff_to[MAX];
    char buff_topic[MAX];
    char buff_text[MAX];
    bzero(buff_to, sizeof(buff_to));
    bzero(buff_topic, sizeof(buff_topic));
    bzero(buff_text, sizeof(buff_text));
    strcpy(mail.from,user.username);
        bzero(buff_to, sizeof(buff_to));
        bzero(buff_topic, sizeof(buff_topic));
        bzero(buff_text, sizeof(buff_text));
        printf("Enter the receiver of mail : ");
        fgets(buff_to, MAX, stdin);
        buff_to[strcspn(buff_to,"\n")] ='\0';
        strcpy(mail.to, buff_to);
        printf("Enter the topic : ");
        fgets(buff_topic, MAX, stdin);
        buff_topic[strcspn(buff_topic,"\n")] ='\0';
        strcpy(mail.topic, buff_topic);
        printf("Enter the text : ");
        fgets(buff_text, MAX, stdin);
        buff_text[strcspn(buff_text,"\n")] ='\0';
        strcpy(mail.text, buff_text);
        send(sockfd, &mail, sizeof(mail), 0);
        recv(sockfd, &feedback, sizeof(feedback), 0);
        printf("Feedback: %d %s\n", feedback.feedback, feedback.message);

}

void get_message_user(int sockfd,User user)
{
        Feedback feedback;
        send(sockfd, &user.username, sizeof(user.username), 0);
            printf("sent\n");
        recv(sockfd, &feedback, sizeof(feedback), 0);
          printf("Feedback %d %s\n", feedback.feedback, feedback.message);
          if (feedback.feedback == 0){
                    Mail mail_rcv;
 		    strcpy(mail_rcv.to,user.username);
                    printf("Reading mails...\n");

                    while(strcmp(mail_rcv.to, "STOP") != 0){
                              if (recv(sockfd, &mail_rcv, sizeof(mail_rcv), 0) > 0 && (strcmp(mail_rcv.to, "STOP") != 0)){
                                printf("Topic: %s\n", mail_rcv.topic);
                                printf("Text: %s\n",mail_rcv.text);
      }
      else{
        printf("Received nothing\n");
      }
    }
    }
    else{
            printf("Nothing\n");
    }

}


void logout_for_user(int sockfd,User user)
{
    Feedback feedback;
    user.id=3;
    send(sockfd, &user, sizeof(user), 0);
    recv(sockfd, &feedback, sizeof(feedback), 0);
    printf("Feedback: %d %s\n", feedback.feedback, feedback.message);
}


void login_for_user(int sockfd, int sckfd,int scfd)
{

    User user = {.id = 2, .username="", .password=""};
    Feedback feedback;
    char buff_username[MAX];
    char buff_password[MAX];
    char mode[MAX];
        bzero(buff_username, sizeof(buff_username));
        bzero(buff_password, sizeof(buff_password));
        printf("Enter the username : ");
        fgets(buff_username, MAX, stdin);
        buff_username[strcspn(buff_username,"\n")] ='\0';
        strcpy(user.username, buff_username);
        printf("Enter the password : ");
        fgets(buff_password, MAX, stdin);
        buff_password[strcspn(buff_password,"\n")] ='\0';
        strcpy(user.password, buff_password);
        send(sockfd, &user, sizeof(user), 0);
          recv(sockfd, &feedback, sizeof(feedback), 0);
          printf("Feedback: %d %s\n", feedback.feedback, feedback.message);
          if (feedback.feedback==0){
          printf("Thank you for login\n");
          for(;;){
          printf("Choose what you want to get\n Send email-mail\n Check your inbox-read\n Logout-logout\n ");
        fgets(mode, MAX, stdin);
        mode[strcspn(mode,"\n")] ='\0';
          if ((strncmp(mode, "mail", 4)) == 0) {
            printf("Give data for mail \n");
            send_message_user(scfd,user);
        }
        else if ((strncmp(mode, "read", 4)) == 0) {
            printf("Getting data \n");
            get_message_user(sckfd,user);
        }
        else if ((strncmp(mode, "logout", 6)) == 0) {
            printf("Loging out \n");
            logout_for_user(sockfd,user);
            break;
        }

          }
          }
          else{
          printf("Try again or choose another option");
          }
          }
