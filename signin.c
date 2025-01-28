#include "main_header.h"

Status signin(Usr_Info *User, FILE *Usr_data_fname, FILE *Usr_pass_fname)
{
    char pass_show_flag;
    printf("Enter Your User Name: ");
    scanf(" %[^\n]",User->name);

    if (user_exist(User->name, Usr_data_fname) == v_success)
    {
        printf("\t\t\t\t\033[32m***User Name Exist***\033[0m\n\n");
        
        strncpy(User->password, getpass("Enter Your Password: "), USER_PASS_SIZE - 1);
        
        if (user_exist(User->password, Usr_pass_fname) == v_success)
        {
            return v_success;
        }
        else
        {
            printf("If You Want to see the Password You Entered Press (Y-Yes or N-No): ");
            scanf(" %c",&pass_show_flag);
            if(pass_show_flag == 'Y' || pass_show_flag == 'y')
            {
                printf("\nPassword You Entered: \"%s\"\n\n",User->password);
            }
        }
    }

    return v_failure;
}