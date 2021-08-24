

int i = 0;

int main()
{
    func();
    printf("i=%d\n", i);
    return (0);
}

void func(void)
{
    ++i;
}
