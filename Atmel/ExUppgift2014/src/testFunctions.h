/*
 * testFunctions.h
 *
 * Created: 2015-10-10 16:07:07
 *  Author: Stefan
 */ 


#ifndef TESTFUNCTIONS_H_
#define TESTFUNCTIONS_H_

#define LED13 PIO_PB27_IDX
#define LEDUART PIO_PB21_IDX
#define LEDUART2 PIO_PB14_IDX

void testUARTr(void);
void blinkTest(void);
void testReceive(void);
void testFilter(void);
void testFans(void);

#define TASK_testFunctions_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_testFunctions_STACK_PRIORITY (4)

void testFunctions (void *pvParameters);

#endif /* TESTFUNCTIONS_H_ */
