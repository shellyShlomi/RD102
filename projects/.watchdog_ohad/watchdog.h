#ifndef __OL102_WATCHDOG_H__
#define __OL102_WATCHDOG_H__

#include <stddef.h>

/* Use StartWD to start watchdog protection and  StopWD to end
   the protection.
 * the args in StartWD should be greater than zero, if not 
   the behavior is undefined.
 * note: if StartWD failed, there will be no protection to your app 
 * do not change the name of the executable file and place it in the 
   same directory.     
 * SIGUSR1 and SIGUSR2 are occupied by watchdog for its functionality.   
 */

int StartWD(char **argv, size_t time_to_signal, size_t time_to_check_signals);
void StopWD(void);

#endif /* __OL102_WATCHDOG_H__ */ 