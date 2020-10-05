// banlet_funcs.c: support functions for the banlet_main program.

#include "banlet.h"

// PROBLEM 1: Replace instances of character 'old' with 'new' in the
// string 'str'.  May use the strlen() library function to determine
// string length or directly look for a '\0' null termination
// character to end the string.
// 
// EXAMPLES:
// char *s1="A A B B A"; string_replace_char(s1, 'A', 'X'); // s1 is "X X B B X"
// char *s2="A A B B A"; string_replace_char(s2, 'B', 'Y'); // s2 is "A A Y Y A"
// char *s3="A A B B A"; string_replace_char(s3, ' ', '-'); // s3 is "A-A-B-B-A"
void string_replace_char(char *str, char old, char new){
  // WRITE ME 
  int _i, _len;

  _len = strlen( str);
  for (_i = 0; _i < _len; _i++){

    if (str[ _i] == old){
      str[ _i] = new;
    }
  }
}

// PROBLEM 1: Counts the number of newline characters '\n' in the
// string 'msg'; return this number +1 as the end of lines will always
// be a line break. May use the strlen() library function to determine
// string length or directly look for a '\0' null termination
// character to end the string.
// 
// EXAMPLES:
// count_linebreaks("Hi")        ->  1
// count_linebreaks("Hi There")  ->  1
// count_linebreaks("Hi\nThere") ->  2
// count_linebreaks("O\nM\nG")   ->  3
int count_linebreaks(char *msg){
  // WRITE ME
  int _i, _c, _len;

  _len = strlen( msg);
  _c = 1;
  for (_i = 0; _i < _len; _i++){

    if (msg[ _i] == '\n'){

      _c++;      
    }
  }
  return _c;
}

// PROBLEM 1: Counts the linebreaks (newline '\n' chars and end of
// string) and returns an array of integers with the position for each
// linebreak in string 'msg'.  The 'nbreaks' parameter is an OUTPUT
// integer that should be set to the number of breaks in 'msg' using
// the C dereference operator (*).
//
// EXAMPLES:
// int nbreaks = -1;
// int *breaks = find_linebreaks("Hello\nWorld", &nbreaks);
// //            index in string: 012345 67890
// // nbreaks is now 2
// // breask is now [5, 11]
int *find_linebreaks(char *msg, int *nbreaks){
  // WRITE ME 
  int _i, _c, _len;
  int * _i_breaks;
 
  _len = strlen( msg);
  _i_breaks = (int*)malloc( sizeof( int) * _len);

  _c = 0;
  for (_i = 0; _i < _len; _i++){

    if (msg[ _i] == '\n'){
      
      _i_breaks[ _c] = _i;
      _c++;
    }
  }

  _i_breaks[ _c] = _i;
  _c++;

  *nbreaks = _c;
  return _i_breaks;
}

// PROBLEM 1: Prints string 'msg' using 'font'. Only prints characters
// 0 to 'length-1'.  Iterates over each row in font->height and then
// scans across the charactes in 'msg' printing each "row" of the
// character. On reaching index 'length', prints a newline and then
// scans across 'msg' again printing characters from the next row.
// Each msg[i] character is used to as the index into fonts->glyphs[]
// to access the "glyph" that will be printed.
//
// NOTE: This function does NOT handle embedded newline '\n'
// characters. It is intended to be called repeatedly on each line in
// multiline text with '\n' characters found using the
// 'find_linebreaks()' function.
//
// EXAMPLE:
//
// print_fontified("Hello!", 6, &font_standard);
// // Prints the following on standard output:
//  _   _        _  _         _ 
// | | | |  ___ | || |  ___  | |
// | |_| | / _ \| || | / _ \ | |
// |  _  ||  __/| || || (_) ||_|
// |_| |_| \___||_||_| \___/ (_)
void print_fontified(char *msg, int length, font_t *font){
  // WRITE ME 
  int _i, _j, _k, _c, _len0, _len, _height, _width, _i_data;
  char _ch_datas[ 255];

  _len = length;
  _len0 = strlen( msg);

  if ( _len > _len0 || _len < 0){

    printf(" Invalid the length!\n");
    return;
  }

  _height = font->height;
  for (_i = 0; _i < _height; _i++){

    _c = 0;
    for (_j = 0; _j < _len; _j++){

      _i_data = (int)msg[ _j];
      _width = font->glyphs[ _i_data].width;
      for (_k = 0; _k < _width; _k++){

        _ch_datas[ _c] = font->glyphs[ _i_data].data[ _i][ _k];
        _c++;
      }
    }

    _ch_datas[ _c] = 0;
    printf("%s\n", _ch_datas);
  }
}

// PROBLEM 2: Uses print_fontified() with find_linebreaks() to
// correctly print 'msg' with 'font' even if there are linebreaks in
// 'msg'.  Uses find_linebreaks() to find the end of each line in
// 'msg' and then iterates over lines printing each.  Uses pointer
// arithmetic to pass the starting position of each line into calls of
// print_fontified(). Frees memory allocated before returning.
//
// EXAMPLE:
// print_fontified_linebreaks("apple\nB@N@N@\nCarr0^", &font_standard);
// // Shows the following on standard output:
//                       _       
//   __ _  _ __   _ __  | |  ___ 
//  / _` || '_ \ | '_ \ | | / _ \
// | (_| || |_) || |_) || ||  __/
//  \__,_|| .__/ | .__/ |_| \___|
//        |_|    |_|             
//  ____     ____   _   _    ____   _   _    ____  
// | __ )   / __ \ | \ | |  / __ \ | \ | |  / __ \ 
// |  _ \  / / _` ||  \| | / / _` ||  \| | / / _` |
// | |_) || | (_| || |\  || | (_| || |\  || | (_| |
// |____/  \ \__,_||_| \_| \ \__,_||_| \_| \ \__,_|
//          \____/          \____/          \____/ 
//   ____                      ___   /\ 
//  / ___|  __ _  _ __  _ __  / _ \ |/\|
// | |     / _` || '__|| '__|| | | |    
// | |___ | (_| || |   | |   | |_| |    
//  \____| \__,_||_|   |_|    \___/     
void print_fontified_linebreaks(char *msg, font_t *font){
  // WRITE ME 
  int _i, _j, _c, _count, _n_breaks;
  char _ch_datas[ 255];
  int * _i_breaks;
  
  _i_breaks = find_linebreaks( msg, &_n_breaks);

  _c = 0;
  for (_i = 0; _i < _n_breaks; _i++){
    
      _count = _i_breaks[ _i] - _c;
      
      for (_j = 0; _j < _count; _j++){
      
        _ch_datas[ _j] = msg[ _c];
        _c++;
      }
      _ch_datas[ _j] = 0;
      _c++;
      print_fontified( _ch_datas, _count, font);
  }	
}

// PROVIDED: Initializes a glyph to mostly X's except for its
// codepoint on the first line.
void glyph_init(glyph_t *glyph, int codepoint){
  glyph->codepoint = codepoint;
  glyph->width = 6;
  for(int i=0; i<MAX_HEIGHT; i++){
    for(int j=0; j<MAX_WIDTH; j++){
      if(j == glyph->width){
        glyph->data[i][j] = '\0'; // null terminate
      }
      else{
        glyph->data[i][j] = 'X';
      }
    }
  }
  int len = sprintf((char *)glyph->data, "%d",codepoint); // add codepoint # to glyph
  glyph->data[0][len] = 'X';                              // remove null termination char
}        

// PROBLEM 2: Loads a banner font from 'filename'.  The format of text
// file is documented more thoroughly in the project specification but
// is generally comprised of a first line that indicate the height of
// each glyph in the font followed by a sequence of each glyph
// starting with its codepoint (ASCII index) and a grid of characters
// in it. To make parsing easier, the @ character is used to represent
// blank spaces in glyph shapes.
//
// EXAMPLE:
// height: 4
// 42
// @@@
// \|/
// /|\
// @@@
// 43
// @@@
// _|_
// @|@
// @@@
//
// The two characters above are the codepoint 42 '*' and codepoint 43
// '+' with the @ symbols eventually being replaced by spaces during
// loading.
// 
// If 'filename' cannot be opened for reading, returns NULL.
//
// Memory allocation happens in two steps: (1) allocates memory for a
// font_t struct then (2) allocates memory for an array of glyph_t
// structs of length NUM_ASCII_GLYPHS (a constant defined in
// banlet.h). Sets the font->glyphs field to be the allocated array of
// glyphs.  Reads the font->height field from teh first line of the
// file.  Iterates over each element of the glyphs array and calls the
// glyph_init() function on it to populate it with default data.  Then
// proceeds to read glyphs from the file. Glyphs are read by reading
// the integer codepoint first which determins which element of the
// glyph array to read into.  Then a loop over the height of the font
// is used to read each row of the glyph into the
// glyph[codepoint]->data[row]; fscanf() with '%s' specifier is used
// for this.  Finally, the string_replace_char() function is used to
// replace all '@' characters with ' ' (space) characters in the glyph
// data. Sets the width of each glyph using the strlen() function on
// any balid row of the glyph data.
//
// Glyphs are read from 'filename' until an attempt to read a glyph's
// codepoint with fscanf() returns EOF (end of file). This causes the
// routine to return the allocated font_t data for use elsewhere.
font_t *font_load(char *filename){
  // WRITE ME
  FILE * _file;
  int _i, _i_ret, _row, _length0, _len, _state, _height, _codepoint;
  char _ch_datas[ 1024];
  char * _p_left_data;

  _length0 = NUM_ASCII_GLYPHS;

  font_t * _font;
  _font = (font_t*)malloc( sizeof( font_t));
  _font->glyphs = (glyph_t*)malloc( sizeof( glyph_t) * _length0);

  for (_i = 0; _i < _length0; _i++){
  
	glyph_init( &_font->glyphs[ _i], _i);
  }
  
  _file = NULL;
  _file = fopen( filename, "rt");
  
  if (_file == NULL){

    return NULL;
  }

  _state = 0;
  _i_ret = fscanf( _file, "%s\n", _ch_datas);
  while( _i_ret == 1){

    switch( _state){
      case 0:

	_height = 0;
 	_p_left_data = strtok( _ch_datas, ":");
	if (_p_left_data != NULL){
		  
	  _height = atoi( _p_left_data);
	  _p_left_data = strtok( NULL, ":");
	  if (_p_left_data != NULL){

	    _height = atoi( _p_left_data);
	  }
	}
	if (_height > 0){

	  _font->height = _height;
	  _state = 1;
	}
        break;
      case 1:

	if (_ch_datas != NULL){
        
          _codepoint = atoi( _ch_datas);
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
	
	string_replace_char( _ch_datas, '@', ' ');
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
  return _font;
}



// PROBLEM 2: Frees the memory associated with 'font'.  First frees
// the glyph array, then frees the font itself. Hint: this funciton
// should be 2 lines long.
void font_free(font_t *font){
  // WRITE ME
  free( font->glyphs);
  free( font);
}

