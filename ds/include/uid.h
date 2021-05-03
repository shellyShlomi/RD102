#define __OL102_UID_H__
#define __OL102_UID_H__

#include <unistd.h> 	/* pid_t */
#include <time.h> 		/* time_t */


/* DO NOT USE INTERNAL MEMBERS OF THE STRUCT */

typedef struct unique_id
{
	size_t count;
	pid_t process_ID:
	time_t time_stamp;
} ilrd_uid_t;


/*UidCreate
 * DESCRIPTION		:	The function create a unique object and returns 
 *						the object by value
 * 
 * PARAMETERS    	:   void function
 *
 * RETURN VALUE   	:   ilrd_uid_t - the unique id object by value    
 * 
 * COMPLEXITY   	:   Time - O(1); Space - O(1) 
 */
 ilrd_uid_t UidCreate(void);
 
 
 /*UidIsSame
 * DESCRIPTION		:	The function checks whether two uids are the same
 * 
 * PARAMETERS    	:   uid1 - (const ilrd_uid_t) a unique id
 *						uid2 - (const ilrd_uid_t) a unique id  
 *
 * RETURN VALUE   	:   boolian value : 1 is same uid, 0 not same uid     
 * 
 * COMPLEXITY   	:   Time - O(1) 
 */
 int UidIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2);
 
 
 
 
 /*GetBadUid
 * DESCRIPTION		:	The function create a bad unique object, used to test
 *						uids, for validity. done by uses of - UidIsSame 
 *						comparing the bad uid with the user uid
 *						
 * 
 * PARAMETERS    	:   uid1 - (const ilrd_uid_t) a unique id
 *						uid2 - (const ilrd_uid_t) a unique id  
 *
 * RETURN VALUE   	:   ilrd_uid_t - a bad unique id object by value
 * 
 * COMPLEXITY   	:   Time - O(1) 
 */
 ilrd_uid_t GetBadUid(void);
 
 #endif /* __OL102_UID_H__ */
