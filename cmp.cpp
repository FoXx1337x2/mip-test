#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(char find[50], char source[50]){
	char low_source[50];
	char low_find[50];						//vlastna funkcia ktora mi hlada v stringoch zadany substring a ignoruje velke/male pismena

	strcpy((low_source),source);	
	strcpy((low_find),find);
	strlwr(low_source);						//string aj substing si zmenim na male pismena aby som ich mohol porovnat pomocou strcpy ktory hlada vyskyt substringu
	strlwr(low_find);

	if(strstr(low_source,low_find) != NULL){
		return 1;
	}											//funkcia vracia hodnotu 1 pokial tam substring je , inak vracia 0
	else
		return 0;

}

int main(){


	return 0;
}