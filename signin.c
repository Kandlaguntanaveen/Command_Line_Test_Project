#include "main_header.h"

Status signin(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname, FILE *users_result_fname)
{
    char pass_show_flag;
    short failed_attempts = MAX_ATTEMPTS;
    int position = 0;
    printf("\nEnter Your User Name: ");
    scanf(" %[^\n]",User->name);

    clear_screen();
    
    if (user_exist_with_position(User->name, Usr_data_fname, &position) == v_success)
    {
        printf("\nINFO: \033[32m User Name Exists\033[0m\n");
        if (user_exist(User->name, users_result_fname) == v_success)
        {
            int score;
            fscanf(users_result_fname, "%d", &score);
            printf("INFO: \033[1;31m But %s Already Taken The Test.\033[1;33m You Got %d out of %d \033[0m\n", User->name, score, MAX_QUESTIONS);
            return v_failure;
        }
        while (failed_attempts)
        {
            printf("\nINFO: \033[1m If You Want to see the Password, Press (D or d- Dispaly) or (H or h- Hide): \033[0m");
            scanf(" %c",&pass_show_flag);
            if(pass_show_flag == 'D' || pass_show_flag == 'd')
            {
                printf("\nEnter Your Password: ");
                scanf(" %[^\n]",User->password);
            }
            else if(pass_show_flag == 'H' || pass_show_flag == 'h')
            {
                strncpy(User->password, getpass("\nEnter Your Password: "), USER_PASS_SIZE - 1);
            }
            else
            {
                printf("\nINFO: \033[31m Invaild Option, Enter (D or d- Dispaly) or (H or h- Hide)\033[0m\n");
                continue;
            }

            encrypt_password(User->password);
            if (checking_password(User->password, Usr_pass_fname, &position) == v_success)
            {
                clear_screen();
                return v_success;
            }
            else
            {
                failed_attempts--;
                clear_screen();
                printf("\nINFO: \033[31m Incorrect password. Please try again. You Have %hd Attempts Left\033[0m\n", failed_attempts);
            }
        }
        printf("\nINFO: \033[31m Too Many Failed Attempts, Exiting the process.\033[0m\n");
    }
    else
    {
        printf("\nINFO: \033[31m User does not exists\033[0m\n");
        printf("INFO: \033[1;31m SignUp First then SignIn! \033[0m\n\n");
    }
    return v_failure;
}

Status user_exist_with_position(char *name, FILE *usr_file, int *position)
{
    char ch, buf[USER_NAME_SIZE] = {0};
    int i = 0;

    rewind(usr_file);

    while((ch = fgetc(usr_file)) != EOF)
    {
        if (ch == ',' || ch == '\n' || ch == ' ')
        {
            buf[i] = '\0';
            if (ch == ',')
            {
                (*position)++;
            }
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

Status checking_password(char *password, FILE *password_file, int *position)
{
    char ch, buf[USER_PASS_SIZE] = {0};
    int i = 0;
    int count = 0;

    rewind(password_file);

    while((ch = fgetc(password_file)) != EOF)
    {
        if (ch == ',' || ch == '\n')
        {
            buf[i] = '\0';
            if (ch == ',')
            {
                count++;
            }
            if (count == *position)
            {
                if (!strcmp(password, buf))
                {
                    return v_success;
                }
            }
            i = 0;
        }
        else if(i < USER_PASS_SIZE - 1)
       	{
            buf[i++] = ch;
    	}
    }
    return v_failure;
}