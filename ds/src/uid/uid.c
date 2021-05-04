
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved ;											*
 *  Date Of Creation:03.05.21;									*
 *  Date Of Approval:04.05.21;									*
 *  Approved By: OHAD											*
 *  Description:unique id data structure;						*/
 
#include <time.h>	/* time_t */
#include <unistd.h>	/* pid_t */

#include "uid.h"
 
ilrd_uid_t UidCreate(void)
{
	static size_t counter = 1;
	
	ilrd_uid_t uid_local = {0};
	
	uid_local.time_stamp = time(NULL);
	
	if ((time_t)-1 == uid_local.time_stamp)
	{
		return (GetBadUid());	
	}
	
	uid_local.process_ID = getpid();
	uid_local.count = counter;
	
	++counter;

	return (uid_local);
}

int UidIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{

	return (		(uid1.count == uid2.count) 				&& 
					(uid1.time_stamp == uid2.time_stamp) 	&& 
					(uid1.process_ID == uid2.process_ID)		);	
}

ilrd_uid_t GetBadUid(void)
{
	ilrd_uid_t bad_local = {0, 0, (time_t)-1};

	return (bad_local);
}
