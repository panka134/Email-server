#ifndef MAIL_H
#define MAIL_H

#define EMAIL_ADDR_SIZE 30
#define TOPIC_SIZE 50
#define TEXT_SIZE 1500

typedef struct Mail{
  char from[EMAIL_ADDR_SIZE];  //email address or ip
  char to[EMAIL_ADDR_SIZE];
  char topic[TOPIC_SIZE];
  char text[TEXT_SIZE];
} Mail;

#endif // MAIL_H