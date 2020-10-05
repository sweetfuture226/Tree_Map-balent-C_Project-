#include "treemap.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main( int argc, char * argv[]){

	bool _b_break, _b_pre_empty_key;
	int _c, _len, _cmd_kind, _argc;
	char _ch_cmd0[ 255];
	char _ch_cmd[ 255];
	char _ch_arg1[ 255];
	char _ch_arg2[ 255];
	char _ch_key[ 255];
	char _ch_value[ 255];
	char _file_name[ 255];
	char * _p_ch_datas;
	treemap_t _tree;
	treemap_init( &_tree);
	
	printf("TreeMap Editor\n");
	printf("Commands:\n");
	printf("  quit:	    exit the program\n");
	printf("  print:	    shows contents of the tree in reverse sorted order\n");
	printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
	printf("  get <key>:	    prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
	printf("  clear:	    eliminates all key/vals from the tree\n");
	printf("  preorder:	    prints contents of the tree in pre-order which is how it will be saved\n");
	printf("  save <file>:	    writes the contents of the tree in pre-order to the given file\n");
	printf("  load <file>:	    clears the current tree and loads the one in the given file\n");
	
	_b_pre_empty_key = false;
	
	while( 1){
	
		_cmd_kind = 0;
		fgets( _ch_cmd0, 255, stdin);
		_len = strlen( _ch_cmd0);

		if (_len < 1){

			continue;
		}

		_ch_cmd0[ _len - 1] = 0;
		
		// Get the args.
		_p_ch_datas = strtok( _ch_cmd0, " ");
		_c = 0;
		_b_break = false;
		while( _p_ch_datas != NULL){

			switch( _c){
			case 0:
				
				strcpy( _ch_cmd, _p_ch_datas);
				break;
			case 1:

				strcpy( _ch_arg1, _p_ch_datas);
				break;
			case 2:

				strcpy( _ch_arg2, _p_ch_datas);
				_b_break = true;
				break;
						
			}
			_p_ch_datas = strtok( NULL, " ");
			
			_c++;
			if (_b_break || _c > 2){

				break;
			}
		}	
		
		_argc = _c;
		
		if (strcmp( _ch_cmd, "quit") == 0){

			printf("TM> quit\n");
			break;
		} else if (strcmp( _ch_cmd, "print") == 0){

			printf("TM> print\n");
			_cmd_kind = 1;
		} else if (strcmp( _ch_cmd, "add") == 0){

			if (_argc == 3){
			
				strcpy( _ch_key, _ch_arg1);
				strcpy( _ch_value, _ch_arg2);
				_cmd_kind = 2;
				printf("TM> %s %s %s\n", _ch_cmd, _ch_key, _ch_value);
			} else {

				continue;
			}
		} else if (strcmp( _ch_cmd, "get") == 0){
		
			if (_argc == 2){

				strcpy( _ch_key, _ch_arg1);
				_cmd_kind = 3;
				printf("TM> %s %s\n", _ch_cmd, _ch_key);
			} else {

				continue;
			}
		} else if (strcmp( _ch_cmd, "clear") == 0){

			printf("TM> clear\n");
			_cmd_kind = 4;
		} else if (strcmp( _ch_cmd, "preorder") == 0){
		
			printf("TM> preorder\n");
			_cmd_kind = 5;		
		} else if (strcmp( _ch_cmd, "save") == 0){
		
			if (_argc == 2){

				strcpy( _file_name, _ch_arg1);
				_cmd_kind = 6;
				printf("TM> %s %s\n", _ch_cmd, _file_name);
			} else {

				continue;
			}
		} else if (strcmp( _ch_cmd, "load") == 0){

			if (_argc == 2){

				strcpy( _file_name, _ch_arg1);
				_cmd_kind = 7;
				printf("TM> %s %s\n", _ch_cmd, _file_name);
			} else {

				continue;
			}
		} else {
		
			if (!_b_pre_empty_key){

				_b_pre_empty_key = true;
				printf("TM>\n");
			}
			continue;
		}

		if (_cmd_kind < 0){

			if (!_b_pre_empty_key){

				_b_pre_empty_key = true;
				printf("TM>\n");
			}
			continue;
		}

		_b_pre_empty_key = false;
		switch( _cmd_kind){

			case 1:
				
				treemap_print_revorder( &_tree);
				break;
			case 2:
				
				treemap_add( &_tree, _ch_key, _ch_value);				
				break;
			case 3:
				// Get the key
				_p_ch_datas = treemap_get( &_tree, _ch_key);
				if (_p_ch_datas == NULL){
				
					printf("NOT FOUND\n");
				} else {
					
					printf("FOUND: %s\n", _p_ch_datas);
				}
				break;
			case 4: // clear

				treemap_clear( &_tree);
				break;
			case 5: // preorder

				treemap_print_preorder( &_tree);
				break;
			case 6: // save
	
				treemap_save( &_tree, _file_name);
				break;
			case 7: // load
			
				treemap_clear( &_tree);
				treemap_load( &_tree, _file_name);
				break;
		}
	}

	return 0;
}


