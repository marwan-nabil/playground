/* This is a hamming code encoder/decoder implementation,
 * author: marwan nabil
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAXMSG	100
#define MAXSYNDROME 30
#define MAXCODE 150

typedef struct {	// a general variable length message type
	unsigned char	length;
	char 		*contents;
} message;

// creates a message
int create_message(char contents[], message *m);

typedef struct {	// the codeword representing the message after hamming encoding
	unsigned char 	length;
	char		contents[MAXCODE];
} codeword;

// creates a valid codeword from an input message,
// the codeword can correct single bit errors
int create_codeword(message m, codeword *w);

// a utility function to calculate the amount of
// redundancy needed for a message of a certain length
// to be able to correct single bit errors
// (m + r + 1) <= 2^r is the relation governing the minimum r,
// where r is the redundancy length in bits, m is the message
// length, i'll attempt a trial and error approach to find r given m.
unsigned char calculate_r(unsigned char l);
// auxiliary to calculate_r()
int try_r(unsigned char m, unsigned char r);


typedef enum {BURST, SINGLE} err_class;	// the type of channel errors, burst or frequent single bit 

typedef struct {	// holds channel parameters, like BER
	float 		ber;
	err_class	errortype;
} channel;

// sends a codeword through the channel and gets the recieved message
codeword send_through_channel(codeword w, channel c);

typedef char syndrome[MAXSYNDROME];	// the syndrome type

// calculates the syndrome from the codeword
void calculate_syndrome(codeword, syndrome *);

// retrieves the message from the codeword and syndrome
message get_message(codeword, syndrome);





