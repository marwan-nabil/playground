#include "hamming.h"

int create_message(char *contents, message *m){
	int length =(int) strlen(contents);

	if (length > MAXMSG){
		printf("error: message is too long\n");
		return -1;
	} else {
		m->length = (unsigned char) length;
		m->contents = contents;
		return length;
	}
}

int try_r(unsigned char m, unsigned char r){
	float rr = (float) r;
	float temp =  powf(2.0,rr);
	if ((m+r+1) <= temp)
		return 1;
	else
		return 0;
}

unsigned char calculate_r(unsigned char m){
	unsigned char r;
	if (m == 1){
		r = 2;

	} else if (m == 2){
		r = 3;
	} else {
		r=4;
		while(!try_r(m,r)){
			r++;
		}
	}
	return r;
}



int main(int argc, char **argv){
	/*
	printf("\nWelcome to the program, please enter the contents of the first message:\n");
	char mssg[MAXMSG];
	gets(mssg);
	message m;
	create_message(mssg, &m);
	printf("The message struct has length field of :%d,\nand contents:\n\t%s\n", m.length, m.contents);
	*/
	printf("\nWelcome, we will test the redundancy calculation function, enter a message size: ");
	unsigned char m;
	scanf("%hhd", &m);
	printf("\nthe redundancy calculated should be the minimum r that conforms to [ (m+r+1) <= 2^r) ]\n");
	unsigned char r = calculate_r(m);
	printf("the redundancy is: %d\n",r);

	return 0;
}

