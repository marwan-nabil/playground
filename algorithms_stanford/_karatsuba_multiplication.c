/* This program does some multiplications on large integers using the karatsuba algorithm
	which is more efficient than ordinary integer multiplication.
	TODO: check that itoa() is working correctly, and debug karatsuba_multiply() piece by piece
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTR 20

// string to integer
// int atoi(char *str)
// {
// 	int val;
// 	int i, sign;
// 	for(i = 0; isspace(str[i]); i++)
// 		;
// 	sign = (str[i] == '-' ? -1 : 1);
// 	if (str[i]=='-' || str[i]=='+')
// 		i++;
// 	if (!isdigit(str[i]))
// 	{
// 		printf("ERROR: atoi: invalid prefix on integer.\n");
// 	}
// 	for(val = 0; isdigit(str[i]); i++)
// 		val = 10*val + (str[i]- '0');
// 	if(str[i] != ' ' || str[i]!='\0')
// 	{
// 		printf("ERROR: atoi: invalid suffix on integer.\n");
// 	}
// 	return val*sign;
// }

// integer to string
void itoa(int i, char *str)
{
	static unsigned int str_index = 0;
	if (i < 10){
		if (str_index < MAXSTR - 1){
			str[str_index++] = '0' + i;
			str[str_index] = '\0';
		}
		else {
			printf("\nError: internal buffer limit exceeded.\n");
			exit(1);
		}
	}
	else {
		if (str_index < MAXSTR - 1){
			itoa( i/10, str);
			str[str_index++] = '0' + i%10;
			str[str_index] = '\0';
		}
		else {
			printf("\nError: internal buffer limit exceeded.\n");
			exit(1);
		}
	}
}

int karatsuba_multiply(int i1, int i2)
{
	char one[MAXSTR];
	char two[MAXSTR];
	char temp[MAXSTR];
	int a, b, c, d;
	int ac, bd, ad_plus_bc, suitable_length;
	// check the base case (two numbers smaller than 10)
	if((abs(i1)<10)&&(abs(i2)<10))
	{
		return i1*i2;
	}
	// make them into strings
	itoa(i1, one); itoa(i2, two);
	// get the suitable length for manipulation
	suitable_length = strlen(one)>strlen(two) ? strlen(one) : strlen(two);
	// make it even
	if(suitable_length%2 == 1)
	{
		suitable_length++;
	}
	// zero left pad the two strings to make them even and equal lengths
	int delta1 = suitable_length - strlen(one);
	int delta2 = suitable_length - strlen(two);
	memset(temp, '0', delta1);	strcpy(temp+delta1, one); strcpy(one, temp);
	memset(temp, '0', delta2);	strcpy(temp+delta2, two); strcpy(two, temp);
	// divide each string into two, making 4 integers a, b, c, d
	strncpy(temp, one, strlen(one)/2); 					a = atoi(temp);
	strncpy(temp, one + strlen(one)/2, strlen(one)/2); 	b = atoi(temp);
	strncpy(temp, two, strlen(two)/2); 					c = atoi(temp);
	strncpy(temp, two + strlen(two)/2, strlen(two)/2); 	d = atoi(temp);
	// we must now compute the components ac, bd, ad, bc to substitute
	// in the expression (10^n)ac + (10^(n/2))(ad + bc) + bd 
	// which is the actual product of the two integers
	ac = karatsuba_multiply(a, c);
	bd = karatsuba_multiply(b, d);
	// we then get away with a single recursive call to get the
	// expression ad + bc instead of two calls
	// this is because (a+b)*(c+d) - ac - bd = ad + bc
	//						^        ^    ^
	//	   will cost a call |         \___|___--> we have those from before
	// note: assuming that addition is much cheaper than multiplication
	ad_plus_bc = karatsuba_multiply((a+b),(c+d)) - ac - bd;
	// return the final result
	return((10^suitable_length)*ac + (10^(suitable_length/2))*ad_plus_bc + bd);
}

int main()
{
	int i1, i2;
	// get two integers from user
	printf("\nEnter the first integer to be multiplied: ");
	scanf("%d", &i1);
	printf("\nEnter the second integer: ");
	scanf("%d", &i2);
	// print out the result
	printf("\nThe result of the multiplication is: %d", karatsuba_multiply(i1, i2));
}