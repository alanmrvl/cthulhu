#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>

#define SUB_EXPR_COUNT 4

int
parse_num(char *verb, regmatch_t *match)
{
	char buffer[4] = {0};

	int substr_start = (int)match->rm_so;
	int substr_end = (int)match->rm_eo;
	size_t substr_length = sizeof(char) * (substr_end - substr_start);

	strncpy(buffer, &verb[substr_start], substr_length);

	int parsed = strtol(buffer, NULL, 10);

	return (parsed);
}

int
main(int argc, char** argv)
{
	srand(time(NULL));

	char* roll_format = "(^[[:digit:]]{1,3})(d|D)([[:digit:]]{1,3}$)";

	if (argc != 2) {
		fprintf(stderr, "Must pass exactly one argument.\n");
	}

	char* verb = argv[1];

	regex_t regex;
	int comp_status = regcomp(&regex, roll_format, REG_EXTENDED);

	if (comp_status) {
		fprintf(stderr, "Regex compilation failed.\n");
		exit(1);
	}

	regmatch_t matches[SUB_EXPR_COUNT];

	int exec_status = regexec(&regex, verb, SUB_EXPR_COUNT, matches, 0); 

	if (exec_status) {
		fprintf(stderr, "Invalid roll.\n");
		exit(1);
	}

	int roll_count = parse_num(verb, &matches[1]);
	int die = parse_num(verb, &matches[3]);

	int roll_total = 0;
	for (int i = 0; i < roll_count; i++) {
		int current_roll = rand() % die + 1;
		roll_total += current_roll;
	}
	
	printf("%s: %d\n", verb, roll_total);

	return 0;
}
