#include <nopoll.h>


void listner_on_message(noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr * user_data )
{
           // print the message (for debugging purposes) and reply
        printf ("Listener received (size: %d, ctx refs: %d): (first [removed] bytes, fragment: %d) '%s'\n", 
                nopoll_msg_get_payload_size (msg),
                nopoll_ctx_ref_count (ctx), nopoll_msg_is_fragment (msg), "I don't know what goes here");
    
        // reply to the message
        nopoll_conn_send_text (conn, "Message received", 16);
  
        return;
}

int main(int argc, char *argv[])
{
//Create a nopoll context
   noPollCtx * ctx = nopoll_ctx_new();

   if(! ctx)
   {
       //handle error here
   }

   noPollConn * listner = nopoll_listener_new (ctx, "0.0.0.0", "1234");
   if(! nopoll_conn_is_ok (listner))
   {
	//handle error here
   }

   nopoll_ctx_set_on_msg(ctx, listner_on_message, NULL);

   nopoll_loop_wait(ctx,0);
// release the context
   nopoll_ctx_unref(ctx);
}


