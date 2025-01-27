#include "main_header.h"

Status signup(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname)
{
label: printf("Create Your User Name: ");
    getchar();
    scanf("%[^\n]",User->name);
    if (user_exist(User->name, Usr_data_fname) == v_success)
    {
        printf("\t\t\033[031m***User Name Already Exist***\n\t\t\t***Try Again***\033[0m\n");
        goto label;
    }
    else
    {
        char re_enter[USER_PASS_SIZE];
        strncpy(User->password, getpass("Create Your Password: "), USER_PASS_SIZE - 1);
        strncpy(re_enter, getpass("Create Your Password: "), USER_PASS_SIZE - 1);
        while (strcmp(User->password, re_enter) != 0)
        {
            printf("\033[31m\t\t\t***Password Not Match***\n\t\t\t***Try Again***\033[0m\n");
            strncpy(User->password, getpass("Create Your Password: "), USER_PASS_SIZE - 1);
            strncpy(re_enter, getpass("Create Your Password: "), USER_PASS_SIZE - 1);
        }
        fseek(Usr_data_fname, 0, SEEK_END);
        getchar();
        long pos = ftell(Usr_data_fname);
        fseek(Usr_data_fname,pos-1,SEEK_CUR);
        fprintf(Usr_data_fname, "%s,", User->name);
    }	
    return v_success;
}

Status user_exist(char *name, FILE *usr_file)
{
    char ch, buf[USER_NAME_SIZE] = {0};
    int i = 0;
    rewind(usr_file);
    while((ch = fgetc(usr_file)) != EOF)
    {
	if (ch == ',' || ch == '\n')
	{
	    buf[i] = '\0';
	    if (!strcmp(name, buf))
	    {
		return v_success;
	    }
	    i = 0;
	}
	else if(i < USER_NAME_SIZE - 1)
       	{
		buf[i++] = ch;
    	}
    }
    return v_failure;
}

//Status password_strength()
