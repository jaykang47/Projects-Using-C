#include <stdlib.h>
#include <stdio.h>

//Arrays
unsigned char Sbox[]= {
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
	};

unsigned char rcon[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

//Functions
void copyArray(unsigned char a[4][4], unsigned char b[4][4])
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			b[i][j]=a[i][j];
		}
	}
}
void mixColumns(unsigned char mix[4][4]) {
    /*int mix[4][4]={0};
    for(int a=0; a<4; a++)//converts matrix into int with mix array
    {
        for(int b=0; b<4; b++)
        {
            //mix[a][b]=0;
            mix[a][b]=(int)matrix[a][b];
        }
    }*/
	//unsigned char a[4] = {0}, b[4] = {0};
    for (int i = 0; i < 4; i++) 
	{
		char a[4] = {0}, b[4] = {0};
        for (int k = 0; k < 4; k++) 
		{
            a[k] = mix[k][i];
            b[k] = mix[k][i] <<  1;
            if (mix[k][i] >= 128 || mix[k][i] < 256) 
			{
                b[k] = b[k] - 256;
                b[k] = b[k] ^ 27;
            }
		//printf("a[%d] = %x b[%d] = %x\n",k,a[k],k, b[k]);
		}
		mix[0][i] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
		mix[1][i] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
		mix[2][i] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
		mix[3][i] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
	}
	/*for(int a=0; a<4; a++)//Converts mix back into unsigned char matrix
    {
        for(int b=0; b<4; b++)
        {
            matrix[a][b]=(unsigned char)mix[a][b];
        }
    }*/
}
void shiftArray(unsigned char A[], int i, int size)
{
	unsigned char temp1, temp2;    //temps to temporarily hold value during exchange
	unsigned char tempA[size];	//temp array to store shifted array
	int index;
	if(i<=0)
	{
        return;
	}
	index=size-i;
	temp1=A[0]; //Holds first value	-replace at index
	for(int j=0; j<i; j++)	//Circular shifts i times
	{
		temp2=A[0];
		for(int k=1; k<=size-1; k++)	//Copies shifted A elements to tempA
		{
			tempA[k-1]=A[k];
		}
		tempA[size-1]=temp2;
		for(int l=0; l<=size-1; l++)	//Copies tempA contents back to A
		{
			A[l]=tempA[l];
		}
	}
	A[index]=temp1;
}
void shiftRow(unsigned char Array[4][4])
{
	for(int i=0; i<4; i++)
	{
		shiftArray(Array[i], i, 4);
	}
}
void subBytes(unsigned char array[4][4])
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			array[i][j]=Sbox[array[i][j]];
		}
	}
}
void subBytesOneD(unsigned char array[4])
{
	for(int i=0; i<4; i++)
	{
		array[i]=Sbox[array[i]];
	}
}
void addRoundKey(unsigned char array[4][4], unsigned char roundKey[4][4])
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			array[i][j]^=roundKey[i][j];
		}
	}
}
void T(unsigned char W[4], unsigned char tempArray[4], int r)
{
	shiftArray(W, 1, 4);
	subBytesOneD(W);
	for(int i=0; i<4; i++)
	{
		if(i==0)
		{
			tempArray[i]=W[i]^rcon[r];
			continue;
		}
		tempArray[i]=W[i];
	}
}
void keySchedule(unsigned char key[4][4], int r)
{
	unsigned char rotWord[4], prevWord[4], prevKey[4][4];//rotWord is array to store T(W(i-1)) values
	for(int i=0; i<4; i++)//Copies key into prevKey
	{
		for(int j=0; j<4; j++)
		{
			prevKey[i][j]=key[i][j];
		}
	}
	T(key[3], rotWord, r);
	
	for(int row=0; row<4; row++)
	{
	    if(row==0)
		{
		    for(int i=0; i<4; i++)
		    {
		        key[0][i]=rotWord[i]^prevKey[0][i];
		        prevWord[i]=key[0][i];
		    }
		    continue;
		}
		for(int col=0; col<4; col++)
		{
		    key[row][col]=prevWord[col]^prevKey[row][col];
		    prevWord[col]=key[row][col];
		}
	}
}

int main()
{
	unsigned char key[4][4];
	int ID1 = 104063217; //Mitchell Bako
	int ID2 = 10423616; //Jay Kang
	int ID3 = 104038095; //Michael DiMeo

	int S1 = (int)(ID1%10 + ID2%10 + ID3%10);
	int S2 = 1 + 6 + 9;
	int A = S1%5;
	int B = (S2%5) + 5;
	
	unsigned char plaintext[4][4] = {   //0x00112233445566778899AABBCCDDEEFF;
	    {0x00, 0x11, 0x22, 0x33},
	    {0x44, 0x55, 0x66, 0x77},
	    {0x88, 0x99, 0xAA, 0xBB},
	    {0xCC, 0xDD, 0xEE, 0xFF}
	}; 
	unsigned char master_key[4][4] ={   //0x000102030405060708090A0B0C0D0E0F;
	    {0x00, 0x01, 0x02, 0x03},
	    {0x04, 0x05, 0x06, 0x07},
	    {0x08, 0x09, 0x0A, 0x0B},
	    {0x0C, 0x0D, 0x0E, 0x0F},
	};
	copyArray(master_key, key);
	printf("------------------------------------------");
	printf("\nID1 = %d (Mitchell Bako)", ID1);
	printf("\nID2 = %d (Jay Kang)", ID2);
	printf("\nID3 = %d (Michael DiMeo)",ID3);
	printf("\nGroup Code (A,B) = (%d,%d)", A, B);
	//The group code is (A,B) = (0,6)

    printf("\nOriginal Plaintext and Key:\n");
    printf("\nPlaintext: \n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%.2x ", plaintext[i][j]);
        }
    }
    printf("\n\nKey: \n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%.2x ", master_key[i][j]);
        }
    }
	
	printf("\n\n------------------------------------------");
    printf("\nKey Schedule Results for Each Round:");
    printf("\n--------------------------------------------");
	for(int r=1; r<=10; r++)
	{
		printf("\nRound %d:", r);
		keySchedule(key, r);
		printf("\n\tKey: ");
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				printf("%.2x ", key[i][j]);
			}
		}
	}
	
    printf("\n\n------------------------------------------");
    printf("\nData Results for Each Round:");
    printf("\n--------------------------------------------");
	copyArray(master_key, key);
    for(int r=0; r<=9; r++)
	{
		printf("\nRound %d: ", r);
		if(r==0)    //Round 0 case
		{
			printf("\n---Start: ");
			for(int i=0; i<4; i++)
			{
				for(int j=0; j<4; j++)
				{
					printf("%.2x ", plaintext[i][j]);
				}
			}
			printf("\n---Output: ");
			addRoundKey(plaintext, key);
			for(int i=0; i<4; i++)
			{
				for(int j=0; j<4; j++)
				{
					printf("%.2x ", plaintext[i][j]);
				}
			}
			continue;
		}
		printf("\n---Output: ");    //Rounds 1-9
		keySchedule(key, r);
		subBytes(plaintext);
		shiftRow(plaintext);
		mixColumns(plaintext);
		addRoundKey(plaintext, key);
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				printf("%.2x ", plaintext[i][j]);
			}
		}
	}
	//Round 10 Case - No MC
	printf("\nRound 10: ");
	printf("\n---Output: ");
	keySchedule(key, 10);
	subBytes(plaintext);
	shiftRow(plaintext);
	addRoundKey(plaintext, key);
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			printf("%.2x ", plaintext[i][j]);
		}
	}

	return 0;
}