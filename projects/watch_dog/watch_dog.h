#ifndef __watchdog_H__
#define __watchdog_H__

/*------------- FOR SETTING ENVIRONMENT VARIABLE ------------*/

/* if you use the watchdog app please dont use the name specified below */

#define BEATS_INTERVAL ("WD_BEATS_INTERVAL")
#define CHECK_RATIO ("WD_CHECK_RATIO")
#define USER_PID ("WD_USER_PID") 
#define WD_PID ("WD_PID")        
#define USER_APP ("WD_USER_APP")
#define WD_APP ("WD_APP")
#define SEM_SIGNAL_NAME ("WD_SEM_SIGNAL_NAME")
#define SEM_BLOCK_NAME ("WD_SEM_BLOCK_NAME")

/*--------------------- SEMAPHOR NAMES ---------------------*/

/* the user need to check the semephor name */
#define SIGNAL ("signal")
#define BLOCK ("block")

    /*Use WDStart to start watchdog protection on a section beggining with the 
    WDstart function call and end with the WDStop function call.

    the process will ping the watchdog every *process_ping_interval* seconds
    the watchdog will ping the process every *watchdog_ping_interval* seconds
    
    if max_time_out is elapsed without pong received, it is counted in a 
    time out counter, when the counter reaches max_timeout_count, the missing
    process (the watchdog or the original process) is forked and execed;*/


    int WDStart(char **argv, int check_ratio, int beats_interval);

    /*Use WDStop to the stop watchdog protection, if WDStop is invoked before
    WDStart, behaviour is undefined*/
    void WDStop(void);


#endif /* __watchdog_H__ */
