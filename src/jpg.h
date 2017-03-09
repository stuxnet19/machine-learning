/*
 * jpg.h
 *
 *  Created on: 9 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_JPG_H_
#define PG_JPG_H_


#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jpeglib.h>



typedef struct jpegfile {
	FILE* file;
	struct jpeg_decompress_struct info;
	struct jpeg_error_mgr err;
	uint w,h;
} JPEGFILE;

inline JPEGFILE* open_jpg(const char* infile) {
	JPEGFILE* f = new JPEGFILE;
	f->file = fopen(infile, "rb");
	if(!f->file) { delete f; return NULL; }
	f->info.err = jpeg_std_error(&f->err);

	jpeg_create_decompress(&f->info);


	jpeg_stdio_src(&f->info, f->file);
	jpeg_read_header(&f->info, TRUE);

	jpeg_start_decompress(&f->info);

	f->w = f->info.output_width;
	f->h = f->info.output_height;

	return f;
}


inline void read_jpg(JPEGFILE* jpgfile, unsigned char* data) {
	unsigned char * rowptr[1];

	while (jpgfile->info.output_scanline < jpgfile->info.output_height)	{
		rowptr[0] = (unsigned char *)data + 3* jpgfile->info.output_width * jpgfile->info.output_scanline;
		jpeg_read_scanlines(&jpgfile->info, rowptr, 1);
	}

	jpeg_finish_decompress(&jpgfile->info);

}

inline void close_jpg(JPEGFILE* jpgfile) {
	fclose(jpgfile->file);
	delete jpgfile;
}



inline void save_jpg(const unsigned char* data, size_t w, size_t h, const char* filefmt, ...) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	va_list vl;
	va_start(vl,filefmt);
	char outfile[1024]; vsprintf(outfile, filefmt, vl);
	va_end(vl);
	char dir[1024]; strcpy(dir, outfile);
	char cmd[1024]; sprintf(cmd, "mkdir -p %s", dirname(dir)); system(cmd);
	FILE* f = fopen(outfile, "w");
	if(!f) {fprintf(stderr, "Can't open file : %s\n", outfile); exit(1); }

	jpeg_stdio_dest(&cinfo, f);

	cinfo.image_width = w; 	/* image width and height, in pixels */
	cinfo.image_height = h;
	cinfo.input_components = 3;		/* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 80, TRUE /* limit to baseline-JPEG values */);

	jpeg_start_compress(&cinfo, TRUE);

	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer[0] = (unsigned char*)&data[cinfo.next_scanline*w*3];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	fclose(f);
}

inline void save_jpg(const float* data, size_t w, size_t h, const char* filefmt, ...) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	va_list vl;
	va_start(vl,filefmt);
	char outfile[1024]; vsprintf(outfile, filefmt, vl);
	va_end(vl);
	char dir[1024]; strcpy(dir, outfile);
	char cmd[1024]; sprintf(cmd, "mkdir -p %s", dirname(dir)); system(cmd);
	FILE* f = fopen(outfile, "w");
	if(!f) {fprintf(stderr, "Can't open file : %s\n", outfile); exit(1); }

	jpeg_stdio_dest(&cinfo, f);

	cinfo.image_width = w; 	/* image width and height, in pixels */
	cinfo.image_height = h;
	cinfo.input_components = 3;		/* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 80, TRUE /* limit to baseline-JPEG values */);

	jpeg_start_compress(&cinfo, TRUE);

	unsigned char* line = new unsigned char[w*3];
	row_pointer[0] = line;
	while (cinfo.next_scanline < cinfo.image_height) {
		for(uint i=0; i<w; i++) line[i*3] = line[i*3+1] = line[i*3+2] = data[cinfo.next_scanline*w + i];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	delete line; line = 0;

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	fclose(f);
}



#endif /* PG_JPG_H_ */
