

/*
 * 1. Query binary folder for files
 * 2. Once: bin --verson to get the versions and populate the version table or
 * 	configuration. NOTE: for other file types we have to find a way to
 * 	get the version information
 *
 * 3. Periodically: Send a single request with all filenames to server to
 *    		query the version information
 *    		a. periodicity is a configurable option
 * 4. Wait for version of all files to be received from server
 * 5. Compare the versions received of all files with the version table.
 * 6. Request for files (only with different version) from server.
 * 7. Wait for response from server that sends the files along with
 * 	md5sum for each file
 * 8. Store the files in a tmp location. Do an integrate check for all files
 * 9. If any files md5sum doesn't match request for the files again that
 * don't match. Then goto step: 7
 *
 * 10. Stop the process if any to be updated is already running or close
 * files if already open or stop processes already using those files
 * 11. Update the files/binaries and restart the stopped process
 */

#include<config.h>
#include<stdio.h>
#include<getopt.h>

#define OTA_IOT_CLIENT_VERSION	"0.0.0"

static char *command;

static void print_version()
{
	printf("%s: version " OTA_IOT_CLIENT_VERSION "\n", command);
}

static void print_help()
{
	printf("Usage: %s [OPTION]...\n\n"
		"-h, --help		help\n"
		"-v, --version		version\n",
		command
	      );
}

int main(int argc, char **argv)
{
	int opt_index;
	static const char short_options[] = "hv";
	static const struct option long_options[] = {
		{"help", 0, 0, 'h'},
		{"version", 0, 0, 'v'},
		{0, 0, 0, 0}
	};
	int c;

	command = argv[0];

	while (1) {
		c = getopt_long(argc, argv, short_options, long_options, &opt_index);
		if (c == -1)
			break;
		switch(c) {
		case 'h':
				print_help();
				break;
		case 'v':
				print_version();
				break;
		};
	}

	return 0;
}
