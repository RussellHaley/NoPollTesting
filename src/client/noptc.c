#include <nopoll.h>



int main (int argsc, char *argsv[])
{
   
noPollCtx * ctx = nopoll_ctx_new ();
if (! ctx) {
    // error some handling code here
}
// do some WebSocket operations (as client or listener)...
// ...and once you are done and after terminating all messages and
// connections created you have to release the context by doing the
// following:
nopoll_ctx_unref (ctx);

// call to create a connection 
noPollConn * conn = nopoll_conn_new (ctx, "172.23.153.112", "50004", NULL, NULL, NULL, NULL);

if (! nopoll_conn_is_ok (conn)) {
    // some error handling here
}

if (! nopoll_conn_wait_until_connection_ready (conn, 5)) {
        // some error handling
}

if (nopoll_conn_send_text (conn, "Hello there! this is a test", 27) != 27) {
        // send a message
printf("error batman");
}

}

