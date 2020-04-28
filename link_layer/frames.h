#include<stdio.h>
#include<stdlib.h>

typedef char	ip_num[15];		// the ip number,example 192.234.590.001 15 chars
typedef char 	mac_addr[11];		// the mac address, ex: a3:2f:00:5e , 11 chars
typedef unsigned long ip_data;		// ip packet payload, from transport layer
typedef unsigned long data_buffer;	// where ip_data is stored on hosts
typedef char	host_name[10];		// name of the host in readable format

typedef enum {CLIENT, SERVER, DNS} host_type;	// the type of the host
typedef enum {ACK, NACK} ack_status;		// the status of acknowledgement frames
typedef enum {VALID, INVALID} chksm_res;	// the results of validating a checksum

// ip address + port number
typedef struct {
	ip_num		ip;
	unsigned char	port_num;
} inet_addr;

// the network layer whole packet
typedef struct {
	inet_addr	sender_addr;
	inet_addr	receiver_addr;
	ip_data		data;
} net_packet;

// the link layer whole frame
typedef struct {
	char start_f;
	unsigned short 	seq_num;
	unsigned int 	checksum;
	net_packet	payload;
} frame;

// the link layer acknowledgement frame
typedef struct {
	unsigned short 	seq_num;
	ack_status 	status;
} ackn;

// the host machine, could be client or server
typedef struct {
	host_name	name;
	host_type	type;
	inet_addr	my_addr;
	data_buffer	buff;
	mac_addr	mac;
} host;

/* TODO: make a linked list of all hosts
 * that are registered on the network */

// a single entry for some sent data
typedef struct{
	host	*sender;
	host	*receiver;
	unsigned long	data;
} entry;

// the whole transactions_record
struct{
	entry	entries[30];
	int	last;
} transaction_record = { 0, 0 };



/* procedures ********************************************/

// validates a checksum
chksm_res validate_chksm(frame);

// calculates a checksum from the frame's payload (network layer packet)
void calculate_chksm(frame *);

// creates and adds a host to the network, the hosts are added on the heap
// host-node *add_host(host_type, host_name, mac_addr, ip_num, unsigned char, host_node *);

// removes hosts, repairs the list, cleans memory
// int remove_host(host_name, host_node *);

// generates random data to act as the frame's payload,
// then registers it on both the sending host and an 
// accounting structure transaction_record
unsigned long gen_payload(typeof(transaction_record) *, host *);
















