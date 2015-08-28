

/*
 *	svstub.c
 */

/*
 *	System includes
 */

/*
 *	General includes
 */

#include "mydefs.h"

/*
 *	Project includes
 */

#include "server.h"
#include "clserv.h"
#include "physic.h"

/*
 *	Static variables
 */

static CLSVBUFF clsvbuff;

/*
 *	Static functions
 */ static int
process_ropen( DATA *p, int qty )
{
p->svcl_ropen.rd = ropen( p->clsv_ropen.pathname, p->clsv_ropen.mode );
return sizeof( SVCL_ROPEN );
}

static int
process_rread( DATA *p, int qty )
{
p->svcl_rread.status =
rread( p->clsv_rread.rd, p->svcl_rread.data, p->clsv_rread.qty );
return sizeof( SVCL_RREAD );
}

static int
process_rwrite( DATA *p, int qty )
{
p->svcl_rwrite.status =
rwrite( p->clsv_rwrite.rd, p->clsv_rwrite.data, p->clsv_rwrite.qty );
return sizeof( SVCL_RWRITE );
} static int
process_rclose( DATA *p, int qty )
{
p->svcl_rclose.status = rclose( p->clsv_rclose.rd );
return sizeof( SVCL_RCLOSE );
}

static int (*proc[])( DATA *p, int qty ) =
{
process_ropen, process_rread, process_rwrite, process_rclose
};



static int
process_server( CLSVBUFF *p, int qty )
{
int opcode;

opcode = p->opc;
qty = (*proc[opcode])( &p->data, qty - sizeof( OPC ) );
p->opc = opcode + SERVER_OFF;
return qty + sizeof( OPC );
}

static void
do_server( void )
{
int qty;

qty = receive_packet( &clsvbuff, sizeof( clsvbuff ) );
qty = process_server( &clsvbuff, qty );
send_packet( &clsvbuff, qty );
}

/*
 *	Public functions
 */

void
main( void )
{
forever
	do_server();

}



