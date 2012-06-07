#ifdef CREATE_PDF

#include <librsvg/rsvg.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>

#include "svg2pdf.h"

int svg2pdf(const char *svg_filename, const char *pdf_filename) {
	RsvgHandle *svg_handle;
	RsvgDimensionData dimension_data;
	cairo_surface_t *surface;
	cairo_t *cr;
	
	rsvg_set_default_dpi(72.0);
	svg_handle = rsvg_handle_new_from_file(svg_filename, NULL);
	if(svg_handle == NULL) {
		return 0;
	}
	rsvg_handle_set_dpi(svg_handle, 72.0);
	rsvg_handle_get_dimensions(svg_handle, &dimension_data);
	surface = cairo_pdf_surface_create(pdf_filename, dimension_data.width, dimension_data.height);
	if(cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS) {
		return 0;
	}
	cr = cairo_create(surface);
	if(cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
		return 0;
	}
	if(!rsvg_handle_render_cairo(svg_handle, cr)) {
		return 0;
	}
	
	cairo_show_page(cr);
	
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	g_object_unref(svg_handle);
	
	return 1;
}

#endif