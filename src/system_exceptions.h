#ifndef SYSTEM_EXCEPTIONS_H
#define SYSTEM_EXCEPTIONS_H

#include <stdint.h>

typedef void (*exception_handler) (void);

void NMI_handler(void);       
void HardFault_handler(void);       
void MemoryManage_handler(void);
void BusFault_handler(void);      
void UsageFault_handler(void);      
void SVC_handler(void);            
void DebugMonitor_handler(void);    
void PendSVC_handler(void);        
void system_tick_handler(void);    

uint32_t get_systick_count();
uint32_t get_seconds_passed();
void set_seconds(uint32_t value);

#endif