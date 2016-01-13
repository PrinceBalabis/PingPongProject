/*
 * UARTTask.h
 *
 * Created: 2015-12-14 22:06:21
 *  Author: Stefan & Prince
 */


#ifndef UARTTASK_H_
#define UARTTASK_H_

#define TASK_SerialComTask_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_SerialComTask_STACK_PRIORITY (1)

void SerialComTask (void *pvParameters);

#endif /* UARTTASK_H_ */
