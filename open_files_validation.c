#include "main_header.h"
Status check_file_order(FILE *fname, char *str)
{
    char ch, identity[10];
    short i = 0;

    while((ch=fgetc(fname)) != '\n')
    {
        identity[i++] = ch;
    }
    identity[i] = '\0';
   
    if(strcmp(identity, str))
    {
        return v_failure;
    }

    return v_success;
}

Status open_files_validation(char *argv[], File_Info *file_info)
{
    char *p;
    p = strstr(argv[1],".");
    if (!(strcmp(p,".csv")))
    {
        file_info->Users_data_fname = fopen(argv[1], "a+");

        if (file_info->Users_data_fname == NULL)
        {
            fprintf(stderr,"ERROR: Unable open %s File\n",argv[1]);
            return v_failure;
        }

        if ((check_file_order(file_info->Users_data_fname,"Userdata")))
        {
            printf ("\033[31m\nERROR: User Data File Must Have First Line as \"Userdata\"\n"); 
            return v_failure;
        }
    }
    else
    {
        return v_failure;
    }
    p = strstr(argv[2],".");
    if (!(strcmp(p,".csv")))
    {
        file_info->Password_fname = fopen(argv[2], "a+");

        if (file_info->Password_fname == NULL)
        {
            fprintf(stderr,"ERROR: Unable open %s File\n",argv[2]);
            return v_failure;
        }

        if ((check_file_order(file_info->Password_fname,"Passwords")))
        {
            printf ("\033[31m\nERROR: Password File Must Have First Line as \"Passwords\"\n"); 
            return v_failure;
        }
    }
    else
    {
        return v_failure;
    }

    p = strstr(argv[3],".");
    if (!(strcmp(p,".txt")))
    {
        file_info->Question_bank_fname = fopen(argv[3], "r");

        if (file_info->Question_bank_fname == NULL)
        {
            fprintf(stderr,"ERROR: Unable open %s File\n",argv[3]);
            return v_failure;
        }

        if ((check_file_order(file_info->Question_bank_fname,"Questions")))
        {
            printf ("\033[31m\nERROR: Question's File Must Have First Line as \"Questions\"\n"); 
            return v_failure;
        }
    }
    else
    {
        return v_failure;
    }
    
    p = strstr(argv[4],".");
    if (!(strcmp(p,".txt")))
    {
        file_info->Answers_fname = fopen(argv[4], "r");

        if (file_info->Answers_fname == NULL)
        {
            fprintf(stderr,"ERROR: Unable open %s File\n",argv[4]);
            return v_failure;
        }

        if ((check_file_order(file_info->Answers_fname,"Answers")))
        {
            printf ("\033[31m\nERROR: Answers File must have first line as \"Answers\"\n"); 
            return v_failure;
        }
    }
    else
    {
        return v_failure;
    }
    
    return v_success;
}
