/*
 * bf.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Initial max data allocation
#define INIT_DATA 30000

void printUsage(){
	printf("Usage: bfz [code]\n");
	exit(1);
}

int main (int argc, char **argv) {
	if (argc < 2) printUsage();
	int p_len = strlen(argv[1]);
	int curr_data_size = INIT_DATA + p_len + 2;
	char *memory = malloc((curr_data_size) * sizeof(char));
	strcpy(memory + 1, argv[1]);
	memory[0] = memory[p_len + 1] = 0; //fuses
	char *dp = memory + p_len + 2, *ip = memory + 1; //Instruction, data pointer
	while(*ip){
		switch (*ip) {
			case ',':;
				char temp;
				if ((temp = getchar()) != EOF) *dp = temp;
				break;
			case '.':
				putchar(*dp);
				break;
			case '>':
				//realloc?
				if (!((memory + curr_data_size - 1) - dp)) {
					int ip_off = ip - memory;
					memory = realloc(memory, (2 * curr_data_size - p_len) * sizeof(char));
					dp = memory + curr_data_size - 1;
					ip = memory + ip_off;
					curr_data_size *= 2;
				}
				dp++;
				break;
			case '<':
				dp--;
				break;
			case '+':
				(*dp)++;
				break;
			case '-':
				(*dp)--;
				break;
			case '[':
				//If pointing to zero
				if (!*dp) {
					//Store current position
					char *buff = ip++;
					int count;
					//find next ip position, if exists
					for (count = 1; count; ip++) {
						if (!*ip) {
							//restore ip if fuse encountered. Cancels instruction.
							ip = buff;
							break;
						} else if (*ip == '[') count++;
						else if (*ip == ']') count--;
					}
				}
				break;
			case ']':
				//opposite
				if (*dp) {
					char *buff = ip--;
					int count;
					for (count = 1; count; ip--) {
						if (!*ip) {
							ip = buff;
							break;
						} else if (*ip == ']') count++;
						else if (*ip == '[') count--;
					}
				}
				break;
		}
		ip++;
	}
	free(memory);
	return 0;
}