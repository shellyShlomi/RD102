#include <stdio.h>

int flip_num(int n) 
{
int ans=0,res=0,sing=1;


if (n<0)
{
int sing = -1;
}

while (n!=0)
{
res=n%10;
n=n/10;

if (n==0)
{
return (ans+res);
}

ans = (res+ans)*10;


}

return ans;


}

int main ()
{

int a = 56340;
int exp_a=4365;

// int x flip_num(a);
// printf("%d",x);

if(exp_a!=flip_num(a))
{
printf("the num is %d\n the expected num is %d\n",a,exp_a);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",a,exp_a);
printf("YESSSSSS\n");
}

int b = 0;
int exp_b=0;
if (exp_b!=flip_num(b))
{
printf("the num is %d\n the expected num is %d\n",b,exp_b);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",b,exp_b);
printf("YESSSSSS\n");
}



int d = -1;
int exp_d=-1;
if (exp_d!=flip_num(d))
{
printf("the num is %d\n the expected num is %d\n",d,exp_d);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",d,exp_d);
printf("YESSSSSS\n");
}




int e = 2345;
int exp_e=5432;
if (exp_e!=flip_num(e))
{
printf("the num is %d\n the expected num is %d\n",e,exp_e);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",e,exp_e);
printf("YESSSSSS\n");
}


 b = -2345;
 exp_b=-5432;
if (exp_b!=flip_num(b))
{
printf("the num is %d\n the expected num is %d\n",b,exp_b);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",b,exp_b);
printf("YESSSSSS\n");
}


int f = -23456;
int exp_f=-65432;
if (exp_f!=flip_num(f))
{
printf("the num is %d\n the expected num is %d\n",f,exp_f);
printf("ERROR\n");

}
else
{
printf("the num is %d\n the expected num is %d\n",f,exp_f);
printf("YESSSSSS\n");
}
return 0;
}

