#include "main_header.h"

Status signup(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname)
{
label: printf("Create Your User Name: ");
    getchar();
    scanf("%[^\n]",User->name);

    if (user_exist(User->name, Usr_data_fname) == v_success)
    {
        printf("\t\t\t\033[031m***User Name Already Exist***\n\t\t\t\t***Try Again***\033[0m\n");
        goto label;
    }
    else
    {
        char re_enter[USER_PASS_SIZE];
        char pass_show_flag;

        while (1) 
        {
            strncpy(User->password, getpass("Create Your Password: "), USER_PASS_SIZE - 1);

            printf("If You Want to see the Password You Entered Press (Y-Yes or N-No): ");
            scanf(" %c",&pass_show_flag);
            if(pass_show_flag == 'Y' || pass_show_flag == 'y')
            {
                printf("\nPassword You Entered: \"%s\"\n\n",User->password);
            }

            if (is_valid_password(User->password) == v_failure || strlen(User->password) < 8) 
            {
                printf("\033[31m\t\t\t ***Password length must be atleast 8 character's***\n");
                printf("\t***Password must contain at least one uppercase letter, one digit, and one special character***\n\t\t\t\t\t ***Try Again***\n");
                return v_failure;
            }

            strncpy(re_enter, getpass("Re-Enter Your Password: "), USER_PASS_SIZE - 1);

            if (strcmp(User->password, re_enter) == 0) 
            {
                break;
            } 
            else 
            {
                printf("\033[31m\t\t***Password Not Match***\n\t\t  ***Try Again***\033[0m\n\n");
            }
        }

        fseek(Usr_data_fname, 0, SEEK_END);
        long pos = ftell(Usr_data_fname);
        fseek(Usr_data_fname,pos-1,SEEK_CUR);
        fprintf(Usr_data_fname, "%s,", User->name);

        fseek(Usr_pass_fname, 0, SEEK_END);
        pos = ftell(Usr_pass_fname);
        fseek(Usr_pass_fname,pos-1,SEEK_CUR);
        fprintf(Usr_pass_fname, "%s,", User->password);
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

Status is_valid_password(char *password)
{
    short is_lower = 0, is_upper = 0, is_digit = 0, is_special = 0;
    for (int i = 0; password[i] != '\0'; i++)
    {
        if(isspace(password[i]))
        {
            return v_failure;
        }
        if (islower(password[i]))
        {
            is_lower = 1;
        }
        else if (isupper(password[i]))
        {
            is_upper = 1;
        }
        else if (ispunct(password[i]))
        {
            is_special = 1;
        }
        else if(isdigit(password[i]))
        {
            is_digit = 1;
        }
    }

    if (is_lower && is_upper && is_special && is_digit)
    {
        return v_success;
    }
    return v_failure;
}