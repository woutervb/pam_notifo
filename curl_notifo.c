/*
 * Copyright (c) Wouter van Bommel <wouter@vanbommelonline.nl>
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <curl/curl.h>
#include <syslog.h>
#include "curl_notifo.h"

/**
 * Receives the response from CURL (and silently ignores it).
 */
int __notifo_response( void *ptr, size_t size, size_t nmemb, void *userdata){
    return size * nmemb;
}

/**
 * Sends a Notifo notification.
 */
int curl_notifo( const char *username, const char *apiKey, char *to, char *label, char *title, char *message, char *url ){

    char userApi[500];
    int ret;
    CURL *curl;                             // The request object
    CURLcode res;                           // Responses from curl functions
    struct curl_httppost *formpost=NULL;    // Contains POST data
    struct curl_httppost *lastptr=NULL;     // Linked list for POST data

    if( username == NULL || apiKey == NULL ){
        return 2;
    } else {
        ret = snprintf( userApi, 500, "%s:%s", username, apiKey );
        if( ret < 0 ){ return 3; }
        if( ret >= 500 ){ return 4; }
    }
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);             // No progress meter
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __notifo_response);  // Receive response here
        curl_easy_setopt(curl, CURLOPT_URL, NOTIFO_API_URL);        // The Notifo API URL
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);   // Use http basic authentication
        curl_easy_setopt(curl, CURLOPT_USERPWD, userApi);           // Set the username and API key

        // Set up the POST data with the Notifo notification information
        if( to ){
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, NOTIFO_TO_KEY, CURLFORM_COPYCONTENTS, to, CURLFORM_END);
        }
        if( label ){
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, NOTIFO_LABEL_KEY, CURLFORM_COPYCONTENTS, label, CURLFORM_END);
        }
        if( title ){
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, NOTIFO_TITLE_KEY, CURLFORM_COPYCONTENTS, title, CURLFORM_END);
        }
        if( message ){
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, NOTIFO_MESSAGE_KEY, CURLFORM_COPYCONTENTS, message, CURLFORM_END);
        }
        if( url ){
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, NOTIFO_URL_KEY, CURLFORM_COPYCONTENTS, url, CURLFORM_END);
        }

        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        // Perform the remote POST
        res = curl_easy_perform(curl);

        // Always clean up
        curl_easy_cleanup(curl);

        return res;
    } else {
        return -1; // CURL not inited properly
    }
}

