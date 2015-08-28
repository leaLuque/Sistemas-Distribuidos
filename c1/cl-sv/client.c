/*
 *  client.c
 */

/*
 *  Test of server
 */

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

#define XFER_BUFF  32

static void get( const char *to, const char *from )
	{
	RD rd;
	FILE *f;
	int qty;
	char buffer[ XFER_BUFF ];

	printf( "transferring %s from remote to %s local\n", from, to );
	rd = ropen( from, "r" );
	printf( "get: open remote: %d\n", rd );
	f = fopen( to, "w" );
	if( f == NULL )
		{
		perror( "get" );
		exit( 1 );
		}

	while( ( qty = rread( rd, buffer, sizeof( buffer ) ) ) > 0 )
		fwrite( buffer, 1, qty, f );
	printf( "get: end of xfer %d\n", qty ); printf( "closing remote %d\n", rclose( rd ) ); 	fclose( f );
	}

static void put( const char *to, const char *from )
	{
	RD rd;
	FILE *f;
	int qty;
	char buffer[ XFER_BUFF ];

	printf( "transferring %s from local to %s in remote\n", from, to );
	rd = ropen( to, "w" );
	printf( "get: open remote: %d\n", rd );
	f = fopen( from, "r" );
	if( f == NULL )
		{
		perror( "get" );
		exit( 1 );
		}
	while( ( qty = fread( buffer, 1, sizeof( buffer ), f ) ) > 0 )
		rwrite( rd, buffer, qty );
	printf( "closing remote %d\n", rclose( rd ) );
	fclose( f );
	}

void main( void )
	{
	get( "client1.c", "client.c" );
	put( "client2.c", "client1.c");
	}

