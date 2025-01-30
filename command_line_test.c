#include "main_header.h"
#include <sys/select.h>

void clear_screen() 
{
    // To clear the terminal screen
    system("clear");
}

Status Take_test(Usr_Info *User, FILE *Question_bank_fname, FILE *Answers_fname)
{
    int index = 0, lines = 0;
    char *user_answers = malloc(sizeof(char));
    if (user_answers == NULL) 
    {
        perror("malloc failed");
        return v_failure;
    }
    char buffer;
    clear_screen();
    printf("INFO:\033[1;33m Best of Luck\033[0m\n");
    for(int i = 10; i >= 0; i--)
    {
        printf("INFO: \033[1;33mTest Starts in ");
        if (i > 5) 
        {
            printf("\033[32m%2d\033[0m ", i);
        } 
        else 
        {
            printf("\033[31m%2d\033[0m ", i); 
        }
        printf("\033[1;33mseconds\033[0m");
        fflush(stdout);
        printf("\r");
        sleep(1);
    }

    clear_screen();

    while (fread(&buffer, 1, 1, Question_bank_fname) > 0)
    {
        if (buffer == '\n')
        {
            lines++;
        }
        if (lines < 5)
        {
            printf("%c", buffer);
            fflush(stdout);
        }
        else
        {
            printf("\n");
            user_input(user_answers, &index);
            user_answers = realloc(user_answers, index * sizeof(char));
            if (user_answers == NULL) 
            {
                perror("realloc failed");
                return v_failure;
            }
            sleep(2);
            clear_screen();
            lines = 0;
        }
    }
    
}

Status user_input(char answers[], int *index)
{
    int i;
    char opt = '\0';
    fd_set read_fds;
    struct timeval timeout;

    // Loop from 10 down to 1
    for (i = TIME_FOR_EACH_QUE; i >= 0; i--) 
    {
        //Print number with carriage return to overwrite the line
        if (i > 5) 
        {
            printf("You have \033[32m%2d\033[0m sec to enter: ", i);
        } 
        else
        {
            printf("You have \033[31m%2d\033[0m sec to enter: ", i);
        }
        fflush(stdout); 
        printf("\r");

        // Set up select() for 1 second timeout to simulate `read -t 1`
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);  // Watch standard input (keyboard)

        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;
        // Check if there's input within 1 second
        if (select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout) > 0) 
        {
            // Input available, read it
            opt = getchar();

            if(opt == 'a' || opt == 'b' || opt == 'c' || opt == 'd')
            {
                printf("\nYou pressed: %c\n", opt);
                printf("You Answered in %d seconds\n", TIME_FOR_EACH_QUE-i);
                //sleep(1);
                answers[(*index)] = opt;
                (*index)++;  
                break;
            }
            else if(opt != '\n' && opt != '\0')
            {  
                printf("\nINFO: INVALID OPTION   \n");
                i = TIME_FOR_EACH_QUE + 1;
            }
        }
    }

    if (opt < 'a' || opt > 'd')
    {
        answers[(*index)] = '0';
        (*index)++;
        printf("\nINFO: \033[31mTimeout\033[0m\n");
    }

    return v_success;
}