/*
 * Copyright (c) Wouter van Bommel <wouter@vanbommelonline.nl>
 *
 *
 */

/* #define DEBUG */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include <unistd.h>
#include <curl/curl.h>
#include "curl_notifo.h"

#define PAM_SM_SESSION

#include <security/pam_modules.h>
#include <security/_pam_macros.h>

typedef struct _pns
{
  int debug;
  char *notifo_user;
  char *notifo_api_key;
  char *notifo_to;
} pam_notifo_s;

static void
parse_args (int argc, const char **argv, pam_notifo_s * pns)
{
  int i;

  /* step through arguments */
  for (i = 0; i < argc; i++)
    {
      const char *opt = argv[i];


      if (strcmp (opt, "debug") == 0)
	{
	  pns->debug = 1;
	};
      if (strncmp (opt, "notifo_user=", 12) == 0)
	{
	  if (pns->notifo_user)
	    free (pns->notifo_user);
	  pns->notifo_user = strdup (&opt[12]);
	};
      if (strncmp (opt, "notifo_api_key=", 15) == 0)
	{
	  if (pns->notifo_api_key)
	    free (pns->notifo_api_key);
	  pns->notifo_api_key = strdup (&opt[15]);
	};
      if (strncmp (opt, "notifo_to=", 10) == 0)
	{
	  if (pns->notifo_to)
	    free (pns->notifo_to);
	  pns->notifo_to = strdup (&opt[10]);
	};

    }
}

static pam_notifo_s *
pns_create ()
{
  return (calloc (1, sizeof (pam_notifo_s)));
}

int
pam_sm_open_session (pam_handle_t * pamh, int flags,
		     int argc, const char **argv)
{
  pam_notifo_s *pns = pns_create ();
  const char *pam_user = NULL;
  char *pam_service = NULL;
  char *pam_tty = NULL;
  char *pam_rhost = NULL;
  char hostname[MAXHOSTNAMELEN];
  char notifoMessage[NOTIFO_MESSAGE_LENGTH];

  parse_args (argc, argv, pns);

  pam_get_user (pamh, &pam_user, NULL);
  pam_get_item (pamh, PAM_SERVICE, (const void **) &pam_service);
  pam_get_item (pamh, PAM_TTY, (const void **) &pam_tty);
  pam_get_item (pamh, PAM_RHOST, (const void **) &pam_rhost);
  gethostname ((char *) &hostname, MAXHOSTNAMELEN);

  // Build message
  snprintf (notifoMessage, NOTIFO_MESSAGE_LENGTH,
	    "User: %s, Source: %s, Service: %s", pam_user,
	    (pam_tty !=
	     NULL ? pam_tty : (pam_rhost != NULL ? pam_rhost : "unknown")),
	    pam_service);

  // Send Notifo notification
  curl_notifo (pns->notifo_user, pns->notifo_api_key, pns->notifo_to,
	       hostname, "User Logged In", notifoMessage, NULL);

  return (PAM_SUCCESS);

};

int
pam_sm_close_session (pam_handle_t * pamh, int flags,
		      int argc, const char **argv)
{
  return (PAM_SUCCESS);
};
