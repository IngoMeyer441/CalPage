#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "calpage.h"


#define IMAGE_DIR "images"
#define PAGE_WIDTH  210
#define PAGE_HEIGHT 297

struct ym {
	int year;
	int month;
};

int get_year_month(struct ym* buffer, int argc, char** argv) {
	int year=-1, month=-1;
	
	if(argc > 2) {
		year =  atoi(argv[1]);
		month = atoi(argv[2]);
		if(year >= 1900 && month > 0 && month <= 12) {
			buffer->year  = year;
			buffer->month = month;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		while(1) {
			printf("year? ");
			scanf("%d", &year);
			printf("month? ");
			scanf("%d", &month);
			if(year >= 1900 && month > 0 && month <= 12) {
				buffer->year  = year;
				buffer->month = month;
				return 1;
			}
			else {
				printf("\nInvalid values, please try again.\n\n");
			}
		}
	}
}

int create_dir(char* name) {
	
	char buffer[100];
	struct stat fileStat;
    if(stat(name,&fileStat) < 0) {  
#ifdef _WIN32
		strcpy(buffer, "md ");
#else
		strcpy(buffer, "mkdir ");
#endif
		strcat(buffer, name);
		return !system(buffer);
	}
	else {
		return S_ISDIR(fileStat.st_mode);
	}
	
}

char* create_filename(char* buffer, struct ym* dat) {
	strcpy(buffer, IMAGE_DIR);
#ifdef _WIN32
	strcat(buffer, "\\");
#else
	strcat(buffer, "/");
#endif
	sprintf(buffer + strlen(buffer), "%d-%d.svg", dat->year, dat->month);
	return buffer;
}

int main(int argc, char** argv) {
	
	FILE* fi = NULL;
	struct ym dat;
	char buffer[100];
	int read_values = 0, created_dir = 0;
	
	read_values = get_year_month(&dat, argc, argv);
	created_dir = create_dir(IMAGE_DIR);
	create_filename(buffer, &dat);
	if(read_values && created_dir && (fi = fopen(buffer, "w")) != NULL) {
		write_cal_page(fi, dat.year, dat.month, PAGE_WIDTH, PAGE_HEIGHT);
		fclose(fi);
		return 0;
	}
	else {
		if(!read_values) {
			fprintf(stderr, "Could not get proper values for year and month");
		}
		else if(!created_dir) {
			fprintf(stderr, "Could not create the directory " IMAGE_DIR);
		}
		else {
			fprintf(stderr, "Could not open the file %s", buffer);
		}
		return 1;
	}
}