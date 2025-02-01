#include "main_header.h"

Status result(Usr_Info *User, File_Info *file)
{
    int ans_index = 0, lines = 0, score = 0;
    char correct_answer_line[MAX_ANSWER_LEN];
    char user_option_description[MAX_QUESTIONS][MAX_ANSWER_LEN];
    Answer correct_answers[MAX_QUESTIONS];

    while (fgets(correct_answer_line, sizeof(correct_answer_line), file->Question_bank_fname) != NULL)
    {
        if (correct_answer_line[1] >= 'a' && correct_answer_line[1] <= 'd')
        {
            if ((correct_answer_line[1] == User->answers[ans_index]) && correct_answer_line[2] == ')')
            {
                correct_answer_line[strlen(correct_answer_line) - 1] = '\0';
                strcpy(user_option_description[ans_index], correct_answer_line + 4);
                ans_index++;
            }  
        }
        if (ans_index > MAX_QUESTIONS)
        {
            break;
        }
    }

    ans_index = 0;
    while (fgets(correct_answer_line, sizeof(correct_answer_line), file->Answers_fname) != NULL) 
    {
        if (correct_answer_line[0] >= 'a' && correct_answer_line[0] <= 'd') 
        {
            correct_answers[ans_index].option = correct_answer_line[0];
            correct_answer_line[strlen(correct_answer_line) - 1] = '\0';
            strcpy(correct_answers[ans_index].description, correct_answer_line + 3);
            ans_index++;
        }
        if (ans_index > MAX_QUESTIONS)
        {
            break;
        }
    }

    rewind(file->Question_bank_fname);
    fseek(file->Question_bank_fname, sizeof("Questions"), SEEK_SET);

    ans_index = 0;
    char buffer;
    while (fread(&buffer, 1, 1, file->Question_bank_fname) > 0) 
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
            if (User->answers[ans_index] == correct_answers[ans_index].option)
            {
                printf("\nYour Answer: \033[1;32m %c) %s (Correct)\033[0m\n\n", User->answers[ans_index], correct_answers[ans_index].description); 
                score++;
            }
            else if (User->answers[ans_index] == '0')
            {
                printf("\n\033[1;31mTimeout for this question.\033[0m \nCorrect Answer is \033[1;32m %c) %s \033[0m\n\n", correct_answers[ans_index].option, correct_answers[ans_index].description); 
            }
            else
            {
                printf("\nYour Answer: \033[1;31m %c) %s (Wrong)\033[0m \nCorrect Answer: \033[32m %c) %s \033[0m\n\n", User->answers[ans_index], user_option_description[ans_index], correct_answers[ans_index].option, correct_answers[ans_index].description);
            }
            ans_index++;
            lines = 0;
            sleep(4);
        }
        if (ans_index > MAX_QUESTIONS)
        {
            break;
        }
    }
   
    printf("INFO:  %s You got \033[1;33m%d\033[0m marks out of \033[1;32m%d \033[0m\n", User->name, score, MAX_QUESTIONS);
    
    fprintf(file->Users_result,"%s %d\n", User->name, score);
    
    return v_success;
}