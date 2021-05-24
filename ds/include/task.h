#ifndef __OL102_TASK_H__
#define __OL102_TASK_H__

#include <sys/types.h> /* time_t */
#include <stddef.h> 	/* size_t */
#include <time.h>	/* time_t */

#include "uid.h"

typedef struct task task_t;


task_t *TaskCreate(int (*action_func)(void *param), 
					size_t interval_in_sec,
					void *param);

void TaskDestroy(task_t *task);

ilrd_uid_t TaskGetUid(const task_t *task);

int TaskUpdateExecutionTime(task_t *task);

time_t TaskGetExecutionTime(task_t *task);

int TaskExecute(task_t *task);

#endif /* __OL102_TASK_H__ */
