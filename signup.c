#include "main_header.h"

Status signup(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname)
{

label:  printf("\nCreate Your User Name: ");
        getchar();
        scanf("%[^\n]",User->name);

        if (user_exist(User->name, Usr_data_fname) == v_success)
        {   
            printf("\nINFO: \033[031mUser Name Already Exist\033[0m\n");
            printf("INFO: \033[031mTry Again\033[0m\n");
            goto label;
        }
        else
        {
            printf("\nINFO: \033[32mThis User Name is Exists\033[0m\n");

            char re_enter[USER_PASS_SIZE];
            char pass_show_flag;
            short failed_attempts = MAX_ATTEMPTS;

            while (failed_attempts) 
            {
                printf("\nINFO: \033[33mPassword length must be atleast 8 character's\n");
                printf("      Password must contain at least one uppercase letter, one digit, and one special character\n\033[0m\n");

                printf("\nINFO: \033[1mIf You Want to see the Password Press (D or d- Dispaly) or (H or h- Hide): \033[0m");
                scanf(" %c",&pass_show_flag);
                
                if(pass_show_flag == 'D' || pass_show_flag == 'd')
                {
                    printf("\nCreate Your Password: ");
                    scanf(" %[^\n]",User->password);
                    printf("\nRe-Enter Your Password: ");
                    scanf(" %[^\n]",re_enter);
                }
                else if(pass_show_flag == 'H' || pass_show_flag == 'h')
                {
                    strncpy(User->password, getpass("\nCreate Your Password: "), USER_PASS_SIZE - 1);
                    strncpy(re_enter, getpass("\nRe-Enter Your Password: "), USER_PASS_SIZE - 1);

                }
                else
                {
                    printf("\nINFO: \033[31mInvaild Option, Enter (D or d- Dispaly) or (H or h- Hide)\033[0m\n");
                    continue;
                }

                if (is_valid_password(User->password) == v_failure || strlen(User->password) < 8) 
                {
                    printf("\nINFO: \033[31mPassword does not meet the required criteria. Make sure to consider the below criteria\033[0m\n");
                    failed_attempts--;
                    continue;
                }

                if (strcmp(User->password, re_enter) == 0) 
                {
                    break;
                } 
                else 
                {
                    printf("\nINFO: \033[31mPassword Not Match\n\tTry Again\033[0m\n\n");
                    failed_attempts--;
                }
            }
            if (!failed_attempts)
            {
                printf("\nINFO: \033[31mToo Many Failed Attempts, Exiting the process.\033[0m\n");
                return v_failure;
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