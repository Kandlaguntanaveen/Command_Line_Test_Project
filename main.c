#include "main_header.h"

int main (int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("\033[31mERROR!\nUSAGE: ./a.out  <User's data file>  <Password's File>  <Question's File>  <Answer's File>\n");
    }
    else
    {
        File_Info file;
        if(open_files_validation(argv, &file) == v_success)
        {
            char choice;
            Usr_Info User;
            while(1)
            {
                clear_screen();
                print_main_menu();
                printf("Enter Your Choice: ");
                scanf("  %c",&choice);
                switch(choice)
                {
                    case '1': printf("\nINFO: \033[33m You Entered the Signup Option\033[0m\n");

                            if(signup(&User, file.Users_data_fname, file.Password_fname) == v_success)
                            {
                                printf("\nINFO: \033[1;33m Password Match and Created Successfully\033[0m\n");
                                printf("\nINFO: \033[1;32m SignUp Successful\033[0m\n");
                                printf("\nINFO: \033[1;33m Signin to Take Test\033[0m\n");
                                closing_files(&file);
                                return v_success;
                            }
                            else
                            {
                                printf("\nINFO: \033[1;91m SignUp Failed!\n");
                                printf("\nINFO: \033[1;33m Exiting from the SignUp Option \033[0m\n");
                                printf("\nINFO: \033[1;33m Redirecting to the Main Menu\033[0m\n");
                            }
                            break;
                            
                    case '2': printf("\nINFO: \033[33m You Entered the SignIn Option\033[0m\n");

                            if(signin(&User, file.Users_data_fname, file.Password_fname, file.Users_result) == v_success)
                            {
                                printf("\nINFO: \033[1;33m Password Match\033[0m\n");
                                printf("\nINFO: \033[1;32m SignIn Successful\033[0m\n");
                                sleep(2);
                        label:  clear_screen();
                                printf("\033[1m \nPlease Select the option below:\n");
                                printf("\n\t 1.Take Test \n\t 2.Back to Main Menu\033[0m\n");
                                char option;
                                printf("\nEnter Your Choice: ");
                                scanf("  %c",&option);
                                if (option == '1')
                                {
                                    if(Take_test(&User, file.Question_bank_fname) == v_success)
                                    {
                                        printf("INFO: \033[1;33m Test Completed Successfully\033[0m\n");
                                        printf("INFO: \033[1;33m It's Result Time \033[0m\n\n");
                                        sleep(4);
                                        clear_screen();
                                        rewind(file.Question_bank_fname);
                                        fseek(file.Question_bank_fname, sizeof("Questions"), SEEK_SET);

                                        result(&User, &file);
                                        printf("\nINFO: \033[1;33m Exiting From The Test \033[0m\n\n");
                                        closing_files(&file);
                                        return v_success;
                                    }
                                }
                                else if(option == '2')
                                {
                                    printf("\nINFO: \033[1;33mExiting from the Signin Option \033[0m\n");
                                    printf("\nINFO: \033[1;33m Redirecting to the Main Menu\033[0m\n");
                                }
                                else
                                {
                                    printf("\nINFO: \033[31m ERROR! Invalid Option\n\tSelect --> 1 or 2 \033[0m\n");
                                    goto label;
                                } 
                            }
                            else
                            {
                                printf("INFO: \033[1;31m SignIn Failed! \033[0m\n\n");
                                closing_files(&file);
                                return v_failure;
                            }
                            break;
                            
                    case '3': printf("\nINFO: \033[31m Exiting From The Test\n");
                              closing_files(&file);
                              exit(0);
                    default:
                            printf("\nINFO: \033[31m ERROR! Invalid Option\n\tSelect --> 1 to 3\n");
                }
                sleep(4);
            }
        }
        else
        {
            printf("\n\033[31mERROR!\nUSAGE: ./a.out  <User's data file>  <Password's File>  <Question's File>  <Answer's File>\n");
        }
    }
    return v_success;
}

void print_main_menu()
{
    printf("\t\t\t\033[32m*****************************************\n");
    printf("\t\t\t*\033[33m      Welcome to Command Line Test\033[32m\t*\n");
    printf("\t\t\t*****************************************\033[0m\n");
    printf("\033[1mPlease Select the option below:\n");
    printf("\n\t 1.SignUp - If not registered \n\t 2.SignIn - To take the Test \n\t 3.Exit\033[0m\n\n");
}

void closing_files(File_Info *file)
{
    fclose(file->Answers_fname);
    fclose(file->Question_bank_fname);
    fclose(file->Password_fname);
    fclose(file->Users_data_fname);
}