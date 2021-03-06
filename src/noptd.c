#include <nopoll.h>
#include <stdbool.h>

void listener_on_message(noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr * user_data )
{
           // print the message (for debugging purposes) and reply
        printf ("Listener received (size: %d, ctx refs: %d): (first [removed] bytes, fragment: %d) '%s'\n", 
                nopoll_msg_get_payload_size (msg),
                nopoll_ctx_ref_count (ctx), nopoll_msg_is_fragment (msg), nopoll_msg_get_payload(msg));
    
        // reply to the message
        nopoll_conn_send_text (conn, "Message received", 16);
  
        return;
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

int main(int argc, char *argv[])
{

   bool enough_args;
   enough_args = checkargs(argc);

   if(!enough_args)
   {
      return false;
   }
//Create a nopoll context
   noPollCtx * ctx = nopoll_ctx_new();

   if(! ctx)
   {
       //handle error here
   }

   noPollConn * listener = nopoll_listener_new (ctx, argv[1], argv[2]);

   //noPollConn * listener = nopoll_listener_new (ctx,"172.23.153.112" , "50004");
   if(! nopoll_conn_is_ok (listener))
   {
	//handle error here
	printf("not okay");
   }

   nopoll_ctx_set_on_msg(ctx, listener_on_message, NULL);

   nopoll_loop_wait(ctx,0);
// release the context
	printf("got here");
   nopoll_ctx_unref(ctx);
}


