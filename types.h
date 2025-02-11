#ifndef TYPES_H
#define TYPES_H

#define USER_NAME_SIZE 30
#define USER_PASS_SIZE 30

#define MAX_ATTEMPTS 3

#define MAX_QUESTIONS 5
#define MAX_ANSWER_LEN 50
#define TIME_FOR_EACH_QUE 10

/* Status will be used in fn. return type */
typedef enum
{
	v_success,
	v_failure
} Status;

#endif