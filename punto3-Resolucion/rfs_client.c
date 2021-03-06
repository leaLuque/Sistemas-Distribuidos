/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rfs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void
rfs_1(char *host, char *file_name)
{
	CLIENT *clnt;
	int  *result_1;
	open_record  rfs_open_1_arg;
	file_data  *result_2;
	read_record  rfs_read_1_arg;
	int  *result_3;
	int  rfs_close_1_arg;
	int  *result_4;
	write_record  rfs_write_1_arg;
	int fd, n;

#ifndef	DEBUG
	clnt = clnt_create (host, RFS, RFS_VERS_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	rfs_open_1_arg.file_name=file_name;
	rfs_open_1_arg.flags=O_RDWR;

	result_1 = rfs_open_1(&rfs_open_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	fd=*result_1;

	rfs_read_1_arg.fd = fd;
	rfs_read_1_arg.count = 20;

	do {
		result_2 = rfs_read_1(&rfs_read_1_arg, clnt);
		if (result_2 == (file_data *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		for (n=0;n<result_2->file_data_len;++n)
			putchar(result_2->file_data_val[n]);
	}while(result_2->file_data_len==20);	
	putchar ("\n");

	result_3 = rfs_close_1(&rfs_close_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = rfs_write_1(&rfs_write_1_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	char *mensaje = argv[2];
	printf("Leyendo el archivo\n");
	rfs_1 (host,mensaje);

	exit (0);
}
