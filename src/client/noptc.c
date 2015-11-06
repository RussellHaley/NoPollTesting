#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <nopoll.h>
#include "noptc.h"

int connection_close_count = 0;
noPollCtx      * ctx = NULL;

int main (int argsc, char *argsv[])
{
  
  bool enough_args;
  enough_args = checkargs(argsc);
  
  if(!enough_args)
  {
    return false;
  }
  
  
  ctx = nopoll_ctx_new ();
  
  if (! ctx) {
    // error some handling code here
  }

  // call to create a connection 
  noPollConn * conn = nopoll_conn_new (ctx, argsv[1], argsv[2], NULL, NULL, NULL, NULL);
  
  if (! nopoll_conn_is_ok (conn)) {
    // some error handling here
  }
  
  if (! nopoll_conn_wait_until_connection_ready (conn, 5)) {
    // some error handling
  }
  
  char input[100];
  
  while(true)
  {
    //User input needed for sorting.    
    fputs("Enter a message: ", stdout);
    fflush(stdout);
    fgets(input, 100, stdin);
    //fputs(input, stdout);
    //printf("you wrote %s",input);
    
    if(strcmp(input,"q\n")!=0)
    {
        if (nopoll_conn_send_text (conn, input, 27) != 27) {
    // send a message
	printf("error batman");
	}
    }
    else
    {
      // do some WebSocket operations (as client or listener)...
      // ...and once you are done and after terminating all messages and
      // connections created you have to release the context by doing the
      // following:
      nopoll_ctx_unref (ctx);
      return 0;
    }       
  }
}


nopoll_bool on_connection_opened (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data)
{
  /* set connection close */
  nopoll_conn_set_on_close (conn, __nopoll_regression_on_close, NULL);
  
  if (! nopoll_conn_set_sock_block (nopoll_conn_socket (conn), nopoll_false)) {
    printf ("ERROR: failed to configure non-blocking state to connection..\n");
    return nopoll_false;
  } /* end if */
  
  /* check to reject */
  if (nopoll_cmp (nopoll_conn_get_origin (conn), "http://deny.aspl.es"))  {
    printf ("INFO: rejected connection from %s, with Host: %s and Origin: %s\n",
	    nopoll_conn_host (conn), nopoll_conn_get_host_header (conn), nopoll_conn_get_origin (conn));
    return nopoll_false;
  } /* end if */
  
  /* get protocol to reply an especific case. This is an example
   *   on how to detect protocols requested by the client and how
   *   to reply with a particular value at the server. */
  printf ("Requested protocol: %s\n", nopoll_conn_get_requested_protocol (conn));
  if (nopoll_cmp (nopoll_conn_get_requested_protocol (conn), "hello-protocol")) {
    /* set hello-protocol-response */
    nopoll_conn_set_accepted_protocol (conn, "hello-protocol-response");
  } /* end if */
  
  /* notify connection accepted */
  /* printf ("INFO: connection received from %s, with Host: %s and Origin: %s\n",
   *   nopoll_conn_host (conn), nopoll_conn_get_host_header (conn), nopoll_conn_get_origin (conn)); */
  return nopoll_true;
}

bool checkargs(int argc)
{
  bool ret = false;
  if(argc < 3)
  {
    printf("not enough params\n");      
  }
  else
  {
    ret = true;
  }
  
  return ret;
}

void __nopoll_regression_on_close (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data)
{
  printf ("Reg test: called connection close (TLS: %d)..\n", nopoll_conn_is_tls_on (conn));
  connection_close_count++;
  return;
}


void write_file_handler (noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr user_data)
{
  FILE       * open_file_cmd = (FILE*) user_data;
  const char * content = (const char *) nopoll_msg_get_payload (msg);
  int          value;
  
  /* check for close operation */
  if (nopoll_ncmp (content, "close-file", 10)) {
    printf ("CLOSING FILE: opened..\n");
    fclose (open_file_cmd);
    open_file_cmd = NULL;
    return;
  } /* end if */
  
  if (open_file_cmd) {
    /* write content */
    value = fwrite (content, 1, nopoll_msg_get_payload_size (msg), open_file_cmd);
    if (value < 0)
      return;
    
    return;
  } /* end if */
  return;
}

void __terminate_listener (int value)
{
	
	/* unlock listener */
	nopoll_loop_stop (ctx);

	return;
}