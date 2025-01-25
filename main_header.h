#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum
{
	v_success,
	v_failure
}Status;

typedef struct USER
{
	char name[30];
	char email[50];
	char pass[30];
}Usr_Info;
Status signup(Usr_Info *User, FILE *Usr_file);
#endif
