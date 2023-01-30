/*
this header file implements the algorithm for 128-bit encryption 
*/
#include<iostream>
#include "lookup_table_encoding.h"
#include "key_expand.h"
using namespace std;
void encryption(unsigned char * state,unsigned char * extendedkeys )
{
	int kp=0;
	for(int i=0;i<16;i++)
	{
		state[i]^=extendedkeys[i];
	}
	kp++;
	while(kp<11)
	{
	      //substitution bits
	      for(int i=0;i<16;i++)
	      {
	          state[i]=sbox[state[i]];
	      }
	      //shift row
	      unsigned char * state2 = new unsigned char[16];
	       for(int i=0;i<16;i++)
	       state2[i]=state[i];
	      //1st column
	       state[0]=state2[0];
	       state[4]=state2[4];
	       state[8]=state2[8];
	       state[12]=state2[12];
	       //2nd column
	       state[1]=state2[5];
	       state[5]=state2[9];
	       state[9]=state2[13];
	       state[13]=state2[1];
	       //3rd column
	       state[2]=state2[10];
	       state[6]=state2[14];
	       state[10]=state2[2];
	       state[14]=state2[6];
	       //4th column
	       state[3]=state2[15];
	       state[7]=state2[3];
	       state[11]=state2[7];
	       state[15]=state2[11];

	       //MIX column
	       if(kp<10)
	       {
	       	    for (int i = 0; i < 16; i++) {
		             state2[i] = state[i];
	              }
	       	//1st row
	            state[0] = (unsigned char) lookup2[state2[0]] ^ lookup3[state2[1]] ^ state2[2] ^ state2[3];
	            state[1] = (unsigned char) state2[0] ^ lookup2[state2[1]] ^ lookup3[state2[2]] ^ state2[3];
	            state[2] = (unsigned char) state2[0] ^ state2[1] ^ lookup2[state2[2]] ^ lookup3[state2[3]];
	            state[3] = (unsigned char) lookup3[state2[0]] ^ state2[1] ^ state2[2] ^ lookup2[state2[3]];
            //2nd row
	            state[4] = (unsigned char)lookup2[state2[4]] ^ lookup3[state2[5]] ^ state2[6] ^ state2[7];
	            state[5] = (unsigned char)state2[4] ^ lookup2[state2[5]] ^ lookup3[state2[6]] ^ state2[7];
	            state[6] = (unsigned char)state2[4] ^ state2[5] ^ lookup2[state2[6]] ^ lookup3[state2[7]];
	            state[7] = (unsigned char)lookup3[state2[4]] ^ state2[5] ^ state2[6] ^ lookup2[state2[7]];
            //3rd row
	            state[8] = (unsigned char)lookup2[state2[8]] ^ lookup3[state2[9]] ^ state2[10] ^ state2[11];
	            state[9] = (unsigned char)state2[8] ^ lookup2[state2[9]] ^ lookup3[state2[10]] ^ state2[11];
	            state[10] = (unsigned char)state2[8] ^ state2[9] ^ lookup2[state2[10]] ^ lookup3[state2[11]];
	            state[11] = (unsigned char)lookup3[state2[8]] ^ state2[9] ^ state2[10] ^ lookup2[state2[11]];
            //4th row
	            state[12] = (unsigned char)lookup2[state2[12]] ^ lookup3[state2[13]] ^ state2[14] ^ state2[15];
	            state[13] = (unsigned char)state2[12] ^ lookup2[state2[13]] ^ lookup3[state2[14]] ^ state2[15];
	            state[14] = (unsigned char)state2[12] ^ state2[13] ^ lookup2[state2[14]] ^ lookup3[state2[15]];
	            state[15] = (unsigned char)lookup3[state2[12]] ^ state2[13] ^ state2[14] ^ lookup2[state2[15]];
		   }

		   //Add Round Key
		    for(int i=0;i<16;i++)
	        {
	          state[i]^=extendedkeys[kp*16+i];
	        }
	        kp++;
	}
}

