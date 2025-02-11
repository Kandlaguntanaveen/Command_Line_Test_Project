#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include <unistd.h>

/* 
 * Structure to store user information required for
 * login to take test and store their options 
 */
typedef struct USER
{
	char name[USER_NAME_SIZE];
	char password[USER_PASS_SIZE];
	char answers[MAX_QUESTIONS];
} Usr_Info;

/* 
 * Structure to store FILES information required for
 * opening and modifying the data
 */
typedef struct FILES
{
	FILE *Users_data_fname;
	FILE *Password_fname;
	FILE *Question_bank_fname;
	FILE *Answers_fname;
	FILE *Users_result;
} File_Info;

/* 
 * Structure to store correct options
 * and answers to validate with the user answers
 */
typedef struct {
    char option; 
    char description[MAX_ANSWER_LEN];
} Answer;

// Which prints starting Menu
void print_main_menu();

// Clears the screen
void clear_screen();

// Checks and vadilates the input files
Status open_files_validation(char *argv[], File_Info *file_info); 

// Taking user data and store in the files for login purpose
Status signup(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname);

// To check whether the user exists or not
Status user_exist(char *name, FILE *usr_file);

// To check whether the password is valid or not
Status is_valid_password(char *password);

// To convert the plain password to cipher
Status encrypt_password(char *user_password);

// To check the user exists or not to Signin
Status signin(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname, FILE *users_result_fname);

// check's whether the user name is exists or not and also find's the postion of the user in file
Status user_exist_with_position(char *name, FILE *usr_file, int *position);

// check's whether the password match's with the username or not
Status checking_password(char *password, FILE *password_file, int *position);

// To display each with certain time
Status Take_test(Usr_Info *User, FILE *Question_bank_fname);

// To take input options from the user for each question
Status user_input(char answers[], int *index);

// To show the correct answers
Status result(Usr_Info *User, File_Info *file);

// Closes all the opened files
void closing_files(File_Info *file);

#endif
