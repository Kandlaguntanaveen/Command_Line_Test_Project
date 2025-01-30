#ifndef TYPES_H
#define TYPES_H

#define USER_NAME_SIZE 30
#define USER_PASS_SIZE 30

#define MAX_ATTEMPTS 5
#define TIME_FOR_EACH_QUE 10

/* Status will be used in fn. return type */
typedef enum
{
	v_success,
	v_failure
} Status;

#endif