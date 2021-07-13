/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;											*
 *  Date Of Creation:12.07.21;									*
 *  Date Of Approval:12.07.21;									*
 *  Approved By:ohad											*	 
 *  Description: semaphores basic commands experimet & exsersis	*/

#include <stdlib.h>	   /* EXIT_FAILURE */
#include <stdio.h>	   /* printf */
#include <semaphore.h> /* semaphore */
#include <fcntl.h>	   /* For O_* constants */
#include <assert.h>	   /* assert */
#include <string.h>	   /* strlen */
#include <ctype.h>	   /* isspace */

#define UNUSED(x) (void)(x)
#define BUFF (100)
#define CHARS_IN_UNDO (4)
#define ARITMETIC_OP (2)
#define EXIT (1)

typedef struct sem_elem
{
	sem_t *sem;
	int count;
} sem_elem_t;

typedef struct operation_recored
{
	const char *op;
	int (*RunOperation)(sem_elem_t *sem, int num);
} operation_recored_t;

/*------------------------------ exercise func --------------------------------*/


/* Semaphore init */
static sem_t *CreatSemaphore(char *sem_name);

/* flow control functions based on user input */
static int Manager(char *name);
static int OperationAnalyzer(sem_elem_t *sem, char *op);
static void RunOperation(sem_elem_t *sem);

/* functions that get the input and operat on it */
static int Decrements(sem_elem_t *sem, int num);
static int Increments(sem_elem_t *sem, int num);
static int GetVal(sem_elem_t *sem, int num);
static int ExitPorg(sem_elem_t *sem, int num);

/*------------------------------ implementetion --------------------------------*/
int main(int argc, char **argv)
{
	assert(argc > 1);
	assert(argv);

	UNUSED(argc);

	return (Manager(argv[1]));
}

static int Manager(char *name)
{
	static sem_elem_t sem = {0};
	int status = 0;

	sem.sem = CreatSemaphore(name);
	sem.count = 0;

	if (SEM_FAILED == sem.sem)
	{
		return (EXIT_FAILURE);
	}

	RunOperation(&sem);

	status = (0 < sem.count) ? Increments(&sem, sem.count) : Decrements(&sem, (-1 * sem.count));

	if (status + !!sem_close(sem.sem))
	{
		status = 0;
	}

	return (status);
}

static sem_t *CreatSemaphore(char *sem_name)
{
	sem_t *sem = NULL;
	assert(sem_name);

	sem = sem_open(sem_name, O_CREAT, 0660, 0);

	return (sem);
}

static void RunOperation(sem_elem_t *sem)
{
	int ret = 0;
	char buf[BUFF] = {'\0'};

	assert(sem);

	printf("***The folowing command can help you control your semaphore : ***\n");
	printf("\nD {num} [end_of_op] for decrements \nI {num} [end_of_op] for increments\nV show the value\nX exit the program \n\n");
	printf("Enter your operation:\n");

	while (EXIT_FAILURE != ret || EXIT != ret)
	{
		fgets(buf, BUFF - 1, stdin);
		ret = OperationAnalyzer(sem, buf);
	}

	return;
}
/* 
static int OperationAnalyzer(sem_elem_t *sem, char *op)
{

	static operation_recored_t sys_op[] =
		{
			{"D", Decrements},
			{"I", Increments},
			{"V", GetVal},
			{"X", ExitPorg}};

	size_t i = 0;
	size_t size = sizeof(sys_op) / sizeof(sys_op[0]);
	int num = 0;
	char *end_of_op = NULL;
	char *undo = NULL;
	char *operation = op;

	assert(sem);
	assert(op);

	SkipSpace(&operation);

	while (i < size && *operation != *sys_op[i].op)
	{
		++i;
	}

	if (isalnum(*(operation + 1)))
	{
		return (EXIT_SUCCESS);
	}

	if (i != size && i < ARITMETIC_OP)
	{
		++operation;
		num = strtod(operation, &end_of_op);

		SkipSpace(&end_of_op);

		operation = end_of_op;

		if ('\0' != *operation && (0 == strncmp(operation, "undo", CHARS_IN_UNDO)) &&
			(!isalnum(*(operation + CHARS_IN_UNDO + 1))))
		{
			if (i)
			{
				sem->count += -num;
			}
			else
			{
				sem->count += num;
			}
		}
	}
	else if (i == size)
	{
		i = 0;
	}

	return (sys_op[i].RunOperation(sem, num));
}
 */

static int OperationAnalyzer(sem_elem_t *sem, char *op)
{

	static operation_recored_t sys_op[] =
		{
			{"D", Decrements},
			{"I", Increments},
			{"V", GetVal},
			{"X", ExitPorg}};

	size_t i = 0;
	size_t size = sizeof(sys_op) / sizeof(sys_op[0]);
	int num = 0;
	char *num_str = NULL;
	char *undo = NULL;
	char *operation = NULL;

	assert(sem);
	assert(op);

	operation = strtok((char *)op, " ");

	while (i < size && *operation != *sys_op[i].op)
	{
		++i;
	}

	if (i != size && i < ARITMETIC_OP)
	{
		num_str = strtok(NULL, " ");
		if (num_str)
		{
			num = atoi(num_str);
			undo = strtok(NULL, " \n");
			
			if (undo && 0 == strncmp(undo, "undo", CHARS_IN_UNDO))
			{
				if (i)
				{
					sem->count += -num;
				}
				else
				{
					sem->count += num;
				}
			}
		}

	}
	else if (i == size)
	{
		i = 0;
	}

	return (sys_op[i].RunOperation(sem, num));
}

static int Decrements(sem_elem_t *sem, int num)
{
	assert(sem);

	while (0 < num && 0 == sem_wait(sem->sem))
	{
		--num;
	}

	if (num)
	{
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

static int Increments(sem_elem_t *sem, int num)
{

	assert(sem);

	while (0 < num && 0 == sem_post(sem->sem))
	{
		--num;
	}

	if (num)
	{
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

static int GetVal(sem_elem_t *sem, int num)
{
	int status = 0;
	int output_param = 0;

	assert(sem);

	UNUSED(num);

	status = sem_getvalue(sem->sem, &output_param);

	if (!status)
	{
		printf("%d\n", output_param);
	}

	return (status);
}

static int ExitPorg(sem_elem_t *sem, int num)
{
	assert(sem);
	UNUSED(num);

	return (EXIT);
}
