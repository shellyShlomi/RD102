#include <stdio.h>  /* 	print	*/
#include <string.h> /*  strlen	*/
#include <assert.h> /*	assert	*/

#include "stack.h"

typedef enum err
{
	MALLOC_FAIL = -1,
	SUCCESS,
	FAILE
	
}err_status_t;


err_status_t BalancedParenthees(const char *str);
static void Test();

int main()
{
	Test();
	
	return 0;
}

err_status_t BalancedParenthees(const char *str)
{
	stack_t *s = NULL;
	assert(NULL != str);
	
	s = StackCreate(strlen(str) / 2);
	
	if (NULL == s)
	{
		return MALLOC_FAIL; 
	}

	
	while ('\0' != *str)
	{
		switch(*str)
		{
			case '[':
		    case '{':
			case '(':
  			{	
  				StackPush(s, (void *)str);
  				
				break;
			}
					
			case ']':
			{	
				if(StackIsEmpty(s))
				{	
					StackDestroy(s);
					return !SUCCESS; 
				} 
				
  				if('[' == *(char *)StackPeek(s))
  				{
  					StackPop(s);
					break;
  				} 
  				StackDestroy(s);
  				return FAILE;
			}
		   	case ')':
		    {	
		    	if(StackIsEmpty(s))
				{	
					StackDestroy(s);
					return !SUCCESS; 
				} 
				
  				if('(' == *(char *)StackPeek(s))
  				{
  					StackPop(s);
					break;
  				} 
  				StackDestroy(s);
  				return FAILE;
			}			
  			case '}':
  			{	
  				if(StackIsEmpty(s))
				{	
					StackDestroy(s);
					return !SUCCESS; 
				} 
				
  				if('{' == *(char *)StackPeek(s))
  				{
  					StackPop(s);
					break;
  				} 
  				StackDestroy(s);
  				return FAILE;
			}
			
  			default:
			{
				break;
			}
		
		}
		++str;
	}
	
	if(StackIsEmpty(s))
	{	
		StackDestroy(s);
		return SUCCESS; 
	} 
	
	StackDestroy(s);
	return FAILE;
}


static void Test()
{
	char *str_arr[] =  {
						"()({}]) jhhjh(", 
						"{}{([()])}{}",
						"{s}{([(ds)]{}",
						"  "
											}; 
											
	err_status_t exp_arr[] = {FAILE, SUCCESS, FAILE, SUCCESS};										
	size_t i = 0;
	size_t size = sizeof(str_arr)/sizeof(str_arr[0]);

	for (i = 0; i < size; ++i)
	{

		if (exp_arr[i] != BalancedParenthees(*(str_arr + i)))
		{	
			printf("BalancedParenthees error at index: %ld\n", i);
		}
	}

	return; 
}
