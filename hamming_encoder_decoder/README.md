# Hamming encoder/decoder
this is a hamming encoder and decoder, Hamming coding is a channel coding scheme, 
it adds redundant bits (r bits) to messages (m bits long), this redundancy helps 
the receiver detect and correct transmission errors.
hamming code is the optimal channel coding scheme, it performs well against single bit
(spike) errors, not so well with burst errors, other schemes are used for other cases.


## features of this program:
1. calculating the required redundancy bits [r] from the length of the input message [m].
2. simulating channel errors, with 2 error classes [burst, single bit].
3. forming a hamming codeword from an input message.
4. calculating the code syndrome at the receiver end, then correcting any errors.
5. interactive message input and output, and channel setting.
6. [maybe] statistical comparison and performance testing of the scheme in both error cases.
