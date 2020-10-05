#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banlet.h"

int main( void){

	int _i, _len, _height, _length0, _state, _i_ret, _row, _codepoint;
	char * _p_ch_data;
	char _ch_datas[ 255];
	char _file_name[ 255];
	char * _p_left_data;
	FILE * _file;
	
  	_length0 = NUM_ASCII_GLYPHS;

  	font_t * _font;
  	_font = (font_t*)malloc( sizeof(font_t));
  	//printf("malloc-1\n");
  	_font->glyphs = (glyph_t*)malloc( sizeof( glyph_t) * _length0);
  	//printf("malloc-2\n");

	strcpy( _file_name, "data/font_standard.txt");  	
	/*
	_file = NULL;
	_file = fopen( _file_name, "rt");

	if (_file == NULL){

	  return -1;
	}

	_state = 0;
	_i_ret = fscanf( _file, "%s\n", _ch_datas);
	printf("%s\n", _ch_datas);
	  while( _i_ret == 1){

	    switch( _state){
	      case 0:

		_p_left_data = strtok( _ch_datas, ":");
		_height = 0;
		if (_p_left_data != NULL){
		  
		  _height = atoi( _p_left_data);
		  _p_left_data = strtok( NULL, ":");
		  if (_p_left_data != NULL){

			  _height = atoi( _p_left_data);
		  }
		}
		if (_height > 0){

		  _font->height = _height;
		  printf("height = %d\n", _height);
		  _state = 1;
		}
		break;
	      case 1:
		
		if (_ch_datas != NULL){
		
			_codepoint = atoi( _ch_datas);
			printf("code point = %d\n", _codepoint);
			if (_codepoint < 0 || _codepoint >= _length0){

			  break;
			}
			_state = 2;
			_row = 0;
		}
		break;
	      case 2:

		if (_row == 0){
		 
		  _font->glyphs[ _codepoint].codepoint = _codepoint;
		  _len = strlen( _ch_datas);
		  _font->glyphs[ _codepoint].width = _len;
		}
		
		for (_i = 0; _i < _len; _i++){

		  _font->glyphs[ _codepoint].data[ _row][ _i] = _ch_datas[ _i];
		}
		_row++;

		if (_row >= _height){

		  _state = 1;
		}
		break;
	    }

	    _i_ret = fscanf( _file, "%s\n", _ch_datas);
	  }

	  fclose( _file);
	  //font_free( _font);
	  //printf("freed\n");
  	printf("height = %d\n", _font->height);
  	for (_i = 0; _i < 128; _i++){
  	
		printf("codepoint = %d\n", _font->glyphs[ _i].codepoint);
  	}
  	printf("tested!\n");*/
  	
	_font = font_load( "data/font_standard.txt");
	printf("font loaded!\n");
 	strcpy( _ch_datas, "\\]^_!`abcde");
	printf("string = %s", _ch_datas);
	
	_len = strlen( _ch_datas);
	for (_i = 0; _i < _len; _i++){
		
		printf(",%d:%c=%d\n", _i, _ch_datas[ _i], (int)_ch_datas[ _i]);
	}
	print_fontified_linebreaks( " !abced", _font);
	/*
	strcpy( _ch_datas, "height: 6");
	
        _p_ch_data = strtok( _ch_datas, ":");
        printf("%s\n", _p_ch_data);
        if (_p_ch_data != NULL){
          
          _p_ch_data = strtok( NULL, ":");
        }
        printf("%s\n", _p_ch_data);
        _height = atoi( _p_ch_data);
        */
	font_free( _font);
	return 0;
}

