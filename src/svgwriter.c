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
	fprintf(fi, "    <line x1=\"%lfmm\" y1=\"%lfmm\" x2=\"%lfmm\" y2=\"%lfmm\" stroke=\"%s\" stroke-width=\"%dpx\"/>\n",
			x1, y1, x2, y2, color, width);
} 

void draw_text(FILE* fi, double x, double y, char* text, double font_size, char* text_anchor, char* color) {
	fprintf(fi, "    <text x=\"%lfmm\" y=\"%lfmm\" font-size=\"%lfmm\" text-anchor=\"%s\" font-family=\"sans-serif\" fill=\"%s\">%s</text>\n",
			x, y, font_size, text_anchor, color, text);
}

/*
void draw_textarea(FILE* fi, double x, double y, char* text, double width, double height, char* text_align, char* display_align, double font_size, char* color) {
	fprintf(fi, "    <textArea x=\"%lfmm\" y=\"%lfmm\" width=\"%lfmm\" height=\"%lfmm\" text-align=\"%s\" display-align=\"%s\" font-size=\"%lfmm\" font-family=\"sans-serif\" fill=\"%s\">%s</textArea>\n",
			x, y, width, height, text_align, display_align, font_size, color, text);
}
*/