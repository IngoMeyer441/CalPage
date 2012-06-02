#include <stdio.h>
#include "svgwriter.h"


void init_svg_document(FILE* fi, double width, double height) {
	fprintf(fi, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
				"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n"
				"<svg xmlns=\"http://www.w3.org/2000/svg\"\n"
				"xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n"
				"version=\"1.1\" baseProfile=\"full\"\n"
				"width=\"%lfmm\" height=\"%lfmm\">\n", width, height);
}

void finish_svg_document(FILE* fi) {
	fprintf(fi, "</svg>\n");
}

void draw_line(FILE* fi, double x1, double y1, double x2, double y2, int width, char* color) {
	fprintf(fi, "    <line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"%lfpx\" color=\"%s\"/>\n");
} 

void draw_text(FILE* fi, double x, double y, char* text, int font_size, char* color) {
	fprintf(fi, "    <text x=\"%lf\" y=\"%lf\" font-size=\"%d\" color=\"%s\">%s</text>\n");
}