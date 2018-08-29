/**
 * @file main.c
 * @brief Compiler entrypoint.
 * @author Shrikant Giridhar
 */
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <cc/common.h>
#include <cc/log.h>
#include <cc/lex.h>

#define VERSION "v1.0" 

static const char *prog;

struct compiler_opts {
	bool verbose;
	bool preprocess_only;
	const char *infile;
	const char *outfile;
};

static const char short_opts[] = "hvVo:I:";
static struct option long_opts[] = {
	{ "help",	no_argument,		0,			'h' },
	{ "version",	no_argument,		0,			'v' },
	{ "output",	required_argument,	0,			'o' },
	{ "preprocess",	no_argument,		0,			'E' },
	{ 0, 0, 0, 0 }
};

static const char ustr[] =
	"Usage: %s [OPTIONS] FILE\n"
	"Compile C99 source files to x86 assembly.\n\n"
	"  -o <file>         Store output into file.\n"
	"  -I <path>         Include file path.\n"
	"  -E, --preprocess  Preprocess only.\n"
	"  -h, --help        Print this message and exit.\n"
	"  -v, --version     Show program version and exit.\n"
	"  -V, --verbose     Show intermediate messages.\n";

static void NORETURN
usage(void)
{
	fprintf(stdout, ustr, prog);
	exit(EXIT_SUCCESS);
}

static void NORETURN
show_version(void)
{
	fprintf(stdout, "cc: The C99 compiler (%s).\n", VERSION);
	exit(EXIT_SUCCESS);
}

static void
parse_opts(int argc, char *argv[], struct compiler_opts *options)
{
	int ch, opt;

	while ((ch = getopt_long(argc, argv, short_opts, long_opts, &opt)) > 0) {
		switch (ch) {
			case 'E': options->preprocess_only = true; break;
			case 'o': options->outfile = optarg; break;
			case 'I': usage();
			case 'h': usage();
			case 'v': show_version(); break;
			case 'V': options->verbose = true; break;
			default: usage();
		}
	}

	if (optind != argc - 1)
		usage();

	options->infile = argv[optind];
}

int
main(int argc, char *argv[])
{
	struct compiler_opts options;
	prog = argv[0];
	log_set(LOG_WARN);
	parse_opts(argc, argv, &options);
	lex(options.infile);

	return EXIT_SUCCESS;
}
