/*
 *  server.h
 */

typedef int RD;

enum {S_OK, S_BAD_OPEN, S_NO_ROOM, S_BAD_RD, S_NOT_OPENED, S_NUM_ERRORS};

RD ropen( const char *pathname, const char *mode );
int rread( RD rd, void *data, int qty );
int rwrite( RD rd, const void *data, int qty );
int rclose( RD rd );