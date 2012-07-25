/*
 * cookie.c: given the path to a contract status file, print out the contract's
 * cookie value.  See contract(4).
 */

#include <libcontract.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
	int fd, i;
	ct_stathdl_t stathdl;

	for (i = 1; i < argc; i++) {
		if ((fd = open(argv[i], O_RDONLY)) < 0) {
			warn("open %s", argv[i]);
			continue;
		}

		if (ct_status_read(fd, CTD_COMMON, &stathdl) == 0) {
			(void) printf("%s: %lx\n", argv[i],
			    ct_status_get_cookie(stathdl));
			ct_status_free(stathdl);
		} else {
			(void) printf("ct_status_read(%s) failed\n", argv[i]);
		}

		(void) close(fd);
	}

	return (0);
}
