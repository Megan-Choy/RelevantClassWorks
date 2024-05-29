/*
Name: Megan Choy
Date: January 19, 2024
Title: Lab2 - Step 1
Description: This program creates multiple threads to make file transfers.
*/

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	//fprintf(stderr, "copy function \n");
	FILE *src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	FILE *dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	size_t *buf;
	buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data
	// reads content of file is loop iterations until end of file

	while (fread(buf, 1, sizeof(buf), src) != 0) {      
		// writes bytes_read to dst_filename 
    	fwrite(buf, 1, sizeof(buf), dst);
	}
	// closes src file pointer
	fclose(src);
	// closes dst file pointer
	fclose(dst);
	// frees memory used for buf
	free(buf);
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	//fprintf(stderr, "copy thread function \n");
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	fprintf(stderr, "thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function
	func_copy(params.src_filename, params.dst_filename);
	pthread_exit(NULL);
	//fprintf(stderr, "ending \n");
}

int main(int argc, char* argv[]) {
	 // check correct usage of arguments in command line
	//fprintf(stderr, "starting \n");
	if (argc != 11) {  
		fprintf(stderr, "usage: %s <src_filenames> <dst_filenames>\n", argv[0]);
		exit(1);
	}
	char* src_filename;
	char* dst_filename;
	char* src_filenames[] = {argv[1], argv[3], argv[5], argv[7], argv[9]}; // array of source files
	char* dst_filenames[] = {argv[2], argv[4], argv[6], argv[8], argv[10]}; // array of desintation files
	int num_threads = 5; // number of threads to create
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	
	for (i = 0; i < num_threads; i++) {
		// initialize thread parameters
		struct copy_struct params;
		params.thread_id = i;
		params.src_filename = src_filenames[i];
		params.dst_filename = dst_filenames[i];
		thread_params[i] = params;
		// create each copy thread
		// use pthread_create(.....);
		//fprintf(stderr, " %d \n", i);
		pthread_create(&threads[i], NULL, copy_thread, (void*)&thread_params[i]);
		//fprintf(stderr, "end of loop \n");
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);

	}
	pthread_exit(NULL);
}