#ifndef _CURL_NOTIFO
#define _CURL_NOTIFO

#define NOTIFO_MESSAGE_LENGTH 500
#define MAXHOSTNAMELEN 500

#define NOTIFO_API_URL "https://api.notifo.com/v1/send_notification"
#define NOTIFO_LABEL_KEY "label"
#define NOTIFO_TITLE_KEY "title"
#define NOTIFO_MESSAGE_KEY "msg"
#define NOTIFO_URL_KEY "url"

int curl_notifo( const char *username, const char *apiKey, char *label, char *title, char *message, char *url );

#endif
