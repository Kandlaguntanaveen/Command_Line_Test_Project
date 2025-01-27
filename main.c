#include "main_header.h"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\033[31mERROR!\nUSAGE: ./a.out <User's data file> <Password's File> <Question's File> <Answer's File>\n");
    }
    else
    {
        File_Info file_info;
        if(open_files_validation(argv, &file_info) == v_success)
        {
            short choice;
            Usr_Info User;
     label: print_main_menu();
            printf("Enter Your Choice: ");
            scanf("%hd",&choice);
            switch(choice)
            {
                case 1: if(signup(&User, file_info.Users_data_fname, file_info.Password_fname) == v_success)
                        {
                            printf("\t\t\033[33m****SignUp Successfully Saved Your Login Credentials****\033[0m\n");
                        }
                        else
                        {
                            printf("\t\t\t\033[31m****SignUp Failed!****\n");
                            return v_failure;
                        }
                        break;
                case 2: printf("In 2 option\n");
                        break;
                case 3: printf("\n\t\t\t\t\033[31m****Exiting the Test****\n");
                        exit(0);
                default:
                        printf("\n\033[31mERROR! Invalid Option\n--> Select 1 to 3\n");
                        goto label;  
            }
        }
        else
        {
            printf("222\033[31mERROR!\nUSAGE: ./a.out <User's data file> <Password's File> <Question's File> <Answer's File>\n");
        }
    }
    return 0;
}

void print_main_menu()
{
    printf("\t\t\t\033[32m*****************************************\n");
    printf("\t\t\t* ");
    printf("\033[33m     Welcome to Command Line Test\033[32m\t*\n");
    printf("\t\t\t*****************************************\033[0m\n");
    printf("Please Select the option below:\n");
    printf("1.SignUp\n2.SignIn\n3.Exit\n");
}