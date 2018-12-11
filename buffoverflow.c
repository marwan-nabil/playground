#include <stdio.h>

void echo(void)
{
	char buf[4];
	gets(buf);
	puts(buf);
}

int main(void)
{
	printf("\ntype a string plz: ");
	echo();
	return 0;
}