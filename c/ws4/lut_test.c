int main()
{	
	system("stty -icanon -echo");
	InputOutput();
	system("stty icanon echo");
	return (0);
}
