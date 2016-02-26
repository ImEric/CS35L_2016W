#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char** argv) {

	//check number of input arg
	if(argc != 3){
		fprintf(stderr, "Number of input arguments not match.\n");
		exit(1);
	}

	char* from = argv[1];
	char* to = argv[2];

	int len = strlen(from);

	//check length
	if(len != strlen(to)){
		fprintf(stderr, "Length of 'from' and 'to' not match.\n");
		exit(2);
	}

	//check duplicates
	int i;
	int j;
	for(i = 0; i < len; i++){
		for(j = 0; j < len; j++){
			if(i != j && from[i] == from[j]){
				fprintf(stderr, "String to be translated must contain no duplicates.\n");
				exit(3);
			}
		}
	}

	//create lookup table
	char** lookup_table = malloc(sizeof(char*) * 256);

	for(i = 0; i < 256; i++){
		lookup_table[i] = NULL;
	}

	for (i = 0; i < len; i++){
		lookup_table[from[i]] = &(to[i]);
	}

	//translate
	int input_byte;
	while ((input_byte = getchar())!= EOF){
		if(lookup_table[input_byte] != NULL)
			putchar(*lookup_table[input_byte]);
		else
			putchar(input_byte);

	}

	return 0;

}