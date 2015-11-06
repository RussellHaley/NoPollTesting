bool checkargs(int argc);
nopoll_bool on_connection_opened (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data);
void __nopoll_regression_on_close (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data);
void write_file_handler (noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr user_data);
void __terminate_listener (int value);