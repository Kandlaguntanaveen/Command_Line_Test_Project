#include "main_header.h"

Status signin(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname)
{
    char pass_show_flag;
    short failed_attempts = MAX_ATTEMPTS;
    printf("\nEnter Your User Name: ");
    scanf(" %[^\n]",User->name);

    if (user_exist(User->name, Usr_data_fname) == v_success)
    {
        printf("\nINFO: \033[32m This User Name Exist\033[0m\n");
        while (failed_attempts)
        {
            printf("\nINFO: \033[1mIf You Want to see the Password, Press (D or d- Dispaly) or (H or h- Hide): \033[0m");
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
                printf("\nINFO: \033[31mInvaild Option, Enter (D or d- Dispaly) or (H or h- Hide)\033[0m\n");
                continue;
            }
        
            if (user_exist(User->password, Usr_pass_fname) == v_success)
            {
                return v_success;
            }
            else
            {
                failed_attempts--;
                printf("\nINFO: \033[31mIncorrect password. Please try again.\033[0m\n");
            }
        }
        printf("\nINFO: \033[31mToo Many Failed Attempts, Exiting the process.\033[0m\n");
    }
    else
    {
        printf("\nINFO: \033[31mThis User does not exists\033[0m\n");
    }
    return v_failure;
}