/*
 * sch.h
 *
 *  Created on: Nov 9, 2022
 *      Author: Administrator
 */

#ifndef INC_SCH_H_
#define INC_SCH_H_

typedef struct {
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void ( * pTask) ( void ) ;
	// Delay ( ti ck s ) until the function w ill ( next ) be run
	uint32_t Delay ;
	// Interval ( ti ck s ) between subsequent runs .
	uint32_t Period ;
	// Incremented ( by scheduler ) when task i s due to execute
	uint8_t RunMe;
	// This i s a hint to solve the question below .
	uint32_t TaskID ;
} sTask ;
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
extern sTask SCH_tasks_G[SCH_MAX_TASKS] ;

extern int current_index_task;

void SCH_Init(void);

void SCH_Add_Task( void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete_Task( int TASK_INDEX);

#endif /* INC_SCH_H_ */
