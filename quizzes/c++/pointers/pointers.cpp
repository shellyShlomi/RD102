
#include <iostream> /*  ostream  */

int main()
{
    // using namespace std;
    int a = 7;
    int *ptr = &a;

    // cout << ptr << endl;
    // cout << *ptr << endl;
    
    *(char *)&ptr = 1;

    // cout << ptr << endl;
    // cout << *ptr << endl;

    return 0;
}