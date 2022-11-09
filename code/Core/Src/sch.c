/*
 * sch.c
 *
 *  Created on: Nov 9, 2022
 *      Author: Administrator
 */
sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init ( void ) {
	unsigned char i ;
	for ( i = 0; i < SCH_MAX_TASKS; i ++) {
		SCH_Delete_Task( i ) ;
	}
	// Reset the global error variable
	// − SCH_Delete_Task () w ill generate an error code ,
	// ( because the task array i s empty)
	Error_code_G = 0;
	Timer_init () ;
	Watchdog_init () ;
}

void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;


		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
	}
}
