#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stack.h"
#define DEFAULT_TEST 10

int main(int argc, char** argv) {
	int n = DEFAULT_TEST;
	if(argc > 1) {
		n = strtol(argv[1], NULL, 10);
	}

	stack* s = stack_alloc();
	
	for(int i = 0; i < n; i++) {
		#if DEBUG
			printf("Pushing %d\n", i);
		#endif
		push(s, i);
	}
	
	for(int i = 0; i < n; i++) {
		s_result res = pop(s);
		if(!res.failed) {
			#if DEBUG
				printf("Value: %d\n", res.val);
			#endif
		} else {
			fprintf(stderr, "No element returned\n");
		}
	}
	
	stack_free(s);
}
