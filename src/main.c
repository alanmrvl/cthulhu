#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>

#define SUB_EXPR_COUNT 4

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

	//printf("Successful match\n");

	char roll_count_buf[4] = {0};
	int roll_count_start = (int)matches[1].rm_so;
	int roll_count_end = (int)matches[1].rm_eo;
	size_t roll_count_length = sizeof(char) * (roll_count_end - roll_count_start);
	strncpy(roll_count_buf, &verb[roll_count_start], roll_count_length);

	//printf("roll_count: %s\n", roll_count_buf);
	
	char die_buf[4] = {0};
	int die_start = (int)matches[3].rm_so;
	int die_end = (int)matches[3].rm_eo;
	size_t die_length = sizeof(char) * (die_end - die_start);
	strncpy(die_buf, &verb[die_start], die_length);

	//printf("die: %s\n", die_buf);

	int roll_count = strtol(roll_count_buf, NULL, 10);
	int die = strtol(die_buf, NULL, 10);

	int roll_total = 0;
	for (int i = 0; i < roll_count; i++) {
		int current_roll = rand() % die;
		roll_total += current_roll;
	}
	
	printf("%s: %d\n", verb, roll_total);

	return 0;
}
