/*
this header file implements the algorithm for 128-bit decryption 
*/
#include<iostream>
#include "lookup_table_decoding.h"
#include "key_expand.h"
using namespace std;
void decryption(unsigned char * state,unsigned char * extendedkeys)
{
	int kp=10;
	while(kp>0)
	{
		//subtract round key
		for(int i=0;i<16;i++)
		{
			state[i]^=extendedkeys[(kp*16)+i];
		}

		//inverse mix column step
        if(kp<10){
	     unsigned char state2[16];
	     	for (int i = 0; i < 16; i++)
			 {
		     state2[i] = state[i];
			 }

	    state[0] = (unsigned char)lookup14[state2[0]] ^ lookup11[state2[1]] ^ lookup13[state2[2]] ^ lookup9[state2[3]];
	    state[1] = (unsigned char)lookup9[state2[0]] ^ lookup14[state2[1]] ^ lookup11[state2[2]] ^ lookup13[state2[3]];
	    state[2] = (unsigned char)lookup13[state2[0]] ^ lookup9[state2[1]] ^ lookup14[state2[2]] ^ lookup11[state2[3]];
	    state[3] = (unsigned char)lookup11[state2[0]] ^ lookup13[state2[1]] ^ lookup9[state2[2]] ^ lookup14[state2[3]];

	    state[4] = (unsigned char)lookup14[state2[4]] ^ lookup11[state2[5]] ^ lookup13[state2[6]] ^ lookup9[state2[7]];
	    state[5] = (unsigned char)lookup9[state2[4]] ^ lookup14[state2[5]] ^ lookup11[state2[6]] ^ lookup13[state2[7]];
	    state[6] = (unsigned char)lookup13[state2[4]] ^ lookup9[state2[5]] ^ lookup14[state2[6]] ^ lookup11[state2[7]];
	    state[7] = (unsigned char)lookup11[state2[4]] ^ lookup13[state2[5]] ^ lookup9[state2[6]] ^ lookup14[state2[7]];

	    state[8] = (unsigned char)lookup14[state2[8]] ^ lookup11[state2[9]] ^ lookup13[state2[10]] ^ lookup9[state2[11]];
	    state[9] = (unsigned char)lookup9[state2[8]] ^ lookup14[state2[9]] ^ lookup11[state2[10]] ^ lookup13[state2[11]];
	    state[10] = (unsigned char)lookup13[state2[8]] ^ lookup9[state2[9]] ^ lookup14[state2[10]] ^ lookup11[state2[11]];
	    state[11] = (unsigned char)lookup11[state2[8]] ^ lookup13[state2[9]] ^ lookup9[state2[10]] ^ lookup14[state2[11]];

	    state[12] = (unsigned char)lookup14[state2[12]] ^ lookup11[state2[13]] ^ lookup13[state2[14]] ^ lookup9[state2[15]];
	    state[13] = (unsigned char)lookup9[state2[12]] ^ lookup14[state2[13]] ^lookup11[state2[14]] ^ lookup13[state2[15]];
	    state[14] = (unsigned char)lookup13[state2[12]] ^ lookup9[state2[13]] ^ lookup14[state2[14]] ^ lookup11[state2[15]];
	    state[15] = (unsigned char)lookup11[state2[12]] ^ lookup13[state2[13]] ^ lookup9[state2[14]] ^ lookup14[state2[15]];
        }
		// Shifts rows right
     	unsigned char state2[16];
     	for (int i = 0; i < 16; i++)
		 {
		state2[i] = state[i];
	     }
	     //column one
	    state [0] = state2[0];
	    state [4] = state2[4];
	    state [8] = state2[8];
	    state [12] = state2[12];
         //column two
        state [1] = state2[13];
	    state [5] = state2[1];
	    state [9] = state2[5];
	    state [13] = state2[9];
         //column three
	    state [2] = state2[10];
	    state [6] = state2[14];
	    state [10] = state2[2];
	    state [14] = state2[6];
	    //column four
	    state [3] = state2[7];
	    state [7] = state2[11];
	    state [11] = state2[15];
	    state [15] = state2[3];

	    //substitution bits
	    for(int i=0;i<16;i++)
	     {
	        state[i]=in_sbox[state[i]];
	     }
	     kp--;
       }

	  	//subtract round key
		for(int i=0;i<16;i++)
		{
			state[i]^=extendedkeys[i];
		}

}

