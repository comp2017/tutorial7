#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Authors Note: NEVER DO ANY MAJOR PROCESSING IN A SIGNAL HANDLER
 * Use signal handlers to with flags.
 */
 
//We use the volatile keyword because we don't want the value cached
//Signals can only access variables in global, use sig_atomic_t type for flags

volatile sig_atomic_t output = 0;
volatile sig_atomic_t quit = 0;

//We use function pointers for the signal handlers
void sig_pipe_toggle_output(int signo) {
	output = !output;
}

void sig_int_quit(int signo) {
	quit = !quit;
}

//asks them to count until a signal is sent
int talk(int n) {
	if(output) {
		printf("Number %d\n", n);
	}	
	sleep(1);
	return n+1;
}

void write_pid() {
	FILE* f = fopen("talker.pid", "w");	
	fprintf(f, "%d\n", getpid());
	fclose(f);
}

int main(int argc, char** argv) {
	
	signal(SIGPIPE, sig_pipe_toggle_output);
	signal(SIGINT, sig_int_quit);
	write_pid();
	printf("I'm going to count until you tell me to stop!\n");
	int n = 1;
	while(!quit) {
		n = talk(n);
	}
	
	printf("Okay! I'm going to stop counting\n");
	
	return 0;
}
