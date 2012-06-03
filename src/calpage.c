#include <stdio.h>
#include <string.h>
#include <time.h>
#include "svgwriter.h"
#include "calpage.h"

#define is_leap_year(y) ((y % 500 == 0 || (y % 4 == 0 && y % 100 != 0)) ? 1 : 0)
#define HEAD_PART 0.1
#define BORDER_PART 0.02

static const char* weekday[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
static const char* month_name[] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
static int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void write_cal_page(FILE* fi, int year, int month, double width, double height) {
	struct tm time_input;
	char heading_text[100] = {'\0'};
	char day_text[100] = {'\0'};
	char buffer[100] = {'\0'};
	double x_pos, y_pos, y_pos2;
	int i;
	
	month_days[1] = is_leap_year(year) ? 29 : 28;
	
	time_input.tm_sec = 0;
	time_input.tm_min = 0;
	time_input.tm_hour = 12;
	time_input.tm_mday = 1;
	time_input.tm_mon = month-1;
	time_input.tm_year = year-1900;
	
	mktime(&time_input);    /* correct other values */
	
	/* init document */
	init_svg_document(fi, width, height);
	/* draw first line (month - year) */
	strcpy(heading_text, month_name[month-1]);
	strcat(heading_text, " - ");
	sprintf(buffer, "%d", year);
	strcat(heading_text, buffer);
	draw_text(fi, width/2, 0.75*HEAD_PART*height, heading_text, 0.5*HEAD_PART*height, "middle", "black");
	/* draw day lines */
	y_pos2 = HEAD_PART*height;
	for(i = 0; i < month_days[month-1]; ++i) {
		y_pos = y_pos2;
		y_pos2 = HEAD_PART*height + (i+1) * ((1-HEAD_PART)*height) / month_days[month-1];
		x_pos = BORDER_PART*width;
		sprintf(buffer, "%02d", i+1);
		strcpy(day_text, buffer);
		strcat(day_text, ", ");
		strcat(day_text, weekday[(time_input.tm_wday+i) % 7]);
		if((time_input.tm_wday+i) % 7 != 0) {
			draw_text(fi, x_pos, y_pos+0.85*((1-HEAD_PART)*height) / month_days[month-1], day_text, 0.8*((1-HEAD_PART)*height) / month_days[month-1], "left", "black");
			draw_line(fi, 0, y_pos2, width, y_pos2, 1, "black");
		}
		else {
			draw_text(fi, x_pos, y_pos+0.85*((1-HEAD_PART)*height) / month_days[month-1], day_text, 0.8*((1-HEAD_PART)*height) / month_days[month-1], "left", "red");
			draw_line(fi, 0, y_pos2, width, y_pos2, 3, "black");
		}
	}
	/* finish document */
	finish_svg_document(fi);
	
	month_days[1] = 28;
}