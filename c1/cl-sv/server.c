
/*
 *  server.c
 */

#include <stdio.h>
#include "server.h"

#define MAX_FILES  20

static FILE *openfiles[ MAX_FILES ];

static int not_verify_rd( RD rd )
	{
	if( rd < 0 || rd >= MAX_FILES )
		return -S_BAD_RD;
	if( openfiles[ rd ] == NULL )
		return -S_NOT_OPENED;
	return S_OK;
	}

RD ropen( const char *pathname, const char *mode )
	{
	FILE **pf;

	for( pf = openfiles ; pf < openfiles + MAX_FILES ; ++pf )
		if( *pf == NULL )
			{
			*pf = fopen( pathname, mode );
			if( *pf == NULL )
				return -S_BAD_OPEN;
			return pf - openfiles;
			}
	return -S_NO_ROOM;
	}

int rread( RD rd, void *data, int qty )
	{
	int status;

	if( status = not_verify_rd( rd ), status )
		return status;
	return fread( data, 1, qty, openfiles[ rd ] );
	}

int rwrite( RD rd, const void *data, int qty )
	{
	int status;

	if( status = not_verify_rd( rd ), status )
		return status;
	return fwrite( data, 1, qty, openfiles[ rd ] );
	}

int rclose( RD rd )
	{
	int status;

	if( status = not_verify_rd( rd ), status )
		return status;
	status = fclose( openfiles[ rd ] );
	openfiles[ rd ] = NULL;
	return status;
	}