
extern void init_svg_document(FILE* fi, double width, double height);

extern void finish_svg_document(FILE* fi);

extern void draw_line(FILE* fi, double x1, double y1, double x2, double y2, int width, char* color);

extern void draw_text(FILE* fi, double x, double y, char* text, int font_size, char* color);
