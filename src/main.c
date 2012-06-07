#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "calpage.h"
#ifdef CREATE_PDF
#include "svg2pdf.h"
#endif


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

char* create_filename(char* buffer, struct ym* dat, const char* extension) {
	strcpy(buffer, IMAGE_DIR);
#ifdef _WIN32
	strcat(buffer, "\\");
#else
	strcat(buffer, "/");
#endif
	sprintf(buffer + strlen(buffer), "%d-%d.%s", dat->year, dat->month, extension);
	return buffer;
}

int main(int argc, char** argv) {
	
	FILE* fi = NULL;
	struct ym dat;
	char svg_filename[100];
#ifdef CREATE_PDF
	char pdf_filename[100];
#endif
	int read_values = 0, created_dir = 0;
	
	read_values = get_year_month(&dat, argc, argv);
	created_dir = create_dir(IMAGE_DIR);
	create_filename(svg_filename, &dat, "svg");
	if(read_values && created_dir && (fi = fopen(svg_filename, "w")) != NULL) {
		write_cal_page(fi, dat.year, dat.month, PAGE_WIDTH, PAGE_HEIGHT);
		fclose(fi);
	}
	else {
		if(!read_values) {
			fprintf(stderr, "Could not get proper values for year and month\n");
		}
		else if(!created_dir) {
			fprintf(stderr, "Could not create the directory " IMAGE_DIR "\n");
		}
		else {
			fprintf(stderr, "Could not open the file %s\n", svg_filename);
		}
		return 1;
	}
	
#ifdef CREATE_PDF
	create_filename(pdf_filename, &dat, "pdf");
	g_type_init();
	if(!svg2pdf(svg_filename, pdf_filename)) {
		fprintf(stderr, "Conversion to pdf not possible\n");
		return 1;
	}
#else
	return 0;
#endif
}