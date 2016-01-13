/*
 * PIDTask.h
 *
 * Created: 2015-12-14 22:05:40
 *  Author: Stefan & Prince
 */

#ifndef PIDTASK_H_
#define PIDTASK_H_


//Defines for creation of PIDRegulationTask
#define TASK_PIDRegulation_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_PIDRegulation_STACK_PRIORITY (2)

void PIDRegulationTask (void *pvParameters);

#endif /* PIDTASK_H_ */
