#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Status will be used in fn. return type */
typedef enum
{
	v_success,
	v_failure
} Status;

/* 
 * Structure to store user information required for
 * login to take test
 */
typedef struct USER
{
	char name[30];
	char pass[30];
} Usr_Info;

/* 
 * Structure to store FILES information required for
 * opening and modifying the data
 */
typedef struct FILES
{
	FILE *fptr_Users_data_file;
	FILE *fptr_Password_file;
	FILE *fptr_Question_bank_file;
	FILE *fptr_Answers_file;
} File_Info;

Status 
Status signup(Usr_Info *User, FILE *Usr_file);

#endif
