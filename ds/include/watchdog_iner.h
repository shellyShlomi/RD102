#ifndef __OL102_WATCHDOG_H__
#define __OL102_WATCHDOG_H__

/*------------- FOR SETTING ENVIRONMENT VARIABLE ------------*/

#define BEATS_INTERVAL ("WD_BEATS_INTERVAL")
#define CHECK_RATIO ("WD_CHECK_RATIO")

/*------------- CLEAN UP DESCRIPTOR FLAGS ------------*/
#define CF_CLOSE_SEM_SIGNAL     (0x0000001)
#define CF_CLOSE_SEM_BLOCK      (0x0000010)
#define CF_UNLINK_SEM_SIGNAL    (0x0000100)
#define CF_UNLINK_SEM_BLOCK     (0x0001000)
#define CF_STOP_SCHEDULER       (0x0010000)
#define CF_DESTROY_SCHEDULER    (0x0100000)
#define CF_FREE_WATCHDOG        (0x1000000)

#endif /* __OL102_WATCHDOG_H__ */


/* static void CleanUp(watchdog_t *watchdog,
                    int to_close_sem_signal,
                    int to_close_sem_block,
                    int to_unlink_sem_signal,
                    int to_unlink_sem_block,
                    int to_stop_scheduler,
                    int to_destroy_scheduler,
                    int to_free_watchdog); */ 
