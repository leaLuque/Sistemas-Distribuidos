/*
 *	clstub.c
 */

#include <string.h>

#include "server.h"
#include "clserv.h"
#include "physic.h" static CLSVBUFF clsvbuff; static
int
send_rcv( CLSVBUFF *p, int opcode, int qty )
{
int qtyrec;

p->opc = opcode;
send_packet( p, qty + sizeof( OPC ) ); qtyrec = receive_packet( p, sizeof( *p ) ); return qtyrec - sizeof( OPC );
}


RD
ropen( const char *pathname, const char *mode )
{
CLSV_ROPEN *pc; SVCL_ROPEN *ps;

pc = &clsvbuff.data.clsv_ropen;
ps = &clsvbuff.data.svcl_ropen; strcpy( pc->pathname, pathname ); strcpy( pc->mode, mode );
send_rcv( &clsvbuff, ROPEN, sizeof( CLSV_ROPEN ) );

return ps->rd;
}

int
rread( RD rd, void *data, int qty )
{
CLSV_RREAD *pc; SVCL_RREAD *ps;

int status;

pc = &clsvbuff.data.clsv_rread;
ps = &clsvbuff.data.svcl_rread;

pc->rd = rd;
pc->qty = qty;
send_rcv( &clsvbuff, RREAD, sizeof( CLSV_RREAD ) );

status = ps->status;
if( status > 0 )
memcpy( data, ps->data, status );
return status;
}

int
rwrite( RD rd, const void *data, int qty )
{
CLSV_RWRITE *pc; SVCL_RWRITE *ps;

pc = &clsvbuff.data.clsv_rwrite;
ps = &clsvbuff.data.svcl_rwrite;

pc->rd = rd;
pc->qty = qty;
if( qty > 0 )
memcpy( pc->data, data, qty );
send_rcv( &clsvbuff, RWRITE, sizeof( CLSV_RWRITE ) );

return ps->status;
}

int
rclose( RD rd )
{
clsvbuff.data.clsv_rclose.rd = rd;
send_rcv( &clsvbuff, RCLOSE, sizeof( CLSV_RCLOSE ) );
return clsvbuff.data.svcl_rclose.status;
}
