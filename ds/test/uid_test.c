#include <stdlib.h> /* exit status */
#include <stdio.h>	/* printf */
#include <unistd.h>	/* sleep */

#include "uid.h"

static void UidManager();

int main()
{
	UidManager();
	
	return EXIT_SUCCESS;
}

static void UidManager()
{
	
	ilrd_uid_t ilrd_uid = {0};
	ilrd_uid_t ilrd_uid1 = {0};
	ilrd_uid_t ilrd_uid_bad = {0};
	ilrd_uid_t ilrd_uid_bad1 = {0};
	
	ilrd_uid = UidCreate();
	ilrd_uid_bad = GetBadUid();
	
	sleep(3);
	
	ilrd_uid1 = UidCreate();
	ilrd_uid_bad1 = GetBadUid();
	
	if (!UidIsSame(ilrd_uid_bad, ilrd_uid_bad1))
	{
		printf("UidIsSame failed ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	
	if (UidIsSame(ilrd_uid, ilrd_uid1))
	{
		printf("UidCreate makes the two uids the same ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	
	if (UidIsSame(ilrd_uid, ilrd_uid_bad))
	{
		printf("UidCreate failed and returns the baduid ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	
	if (ilrd_uid.count == ilrd_uid1.count)
	{
		printf("UidCreate failed and returns the same count ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	if (ilrd_uid1.count != (ilrd_uid.count + 1))
	{
		printf("UidCreate failed and returns wrong count ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	if ((ilrd_uid.time_stamp + 3)!= ilrd_uid1.time_stamp)
	{
		printf("UidCreate failed and returns wrong time_stamp ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	if (ilrd_uid.process_ID != ilrd_uid1.process_ID)
	{
		printf("UidCreate failed and returns diffrent process_ID ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	if (ilrd_uid.process_ID != getpid())
	{
		printf("UidCreate failed and returns wrong process_ID ");
		printf("error at line: %d\n", __LINE__); 	
	}
	
	return;
}

