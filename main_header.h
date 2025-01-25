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
	char usr_name[30];
	char usr_email[50]
	char usr_pass[30];
}Usr_Info;
#endif
