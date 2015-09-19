//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main(int argc, const char * argv[]) {

	//declare file pointers
	FILE *kfp;
	FILE *ifp;    
	FILE *ofp;    
   
	//declare the message/key lengths
	int kLength;
	int messageLength;

	//declare i and j (used in loops)
	int i;  
	int j;
 
	//open the files. note that the input files should be in the same directory as the C file.
	kfp = fopen("./keyFile.txt", "rb");
	ifp = fopen("./plainText.txt", "rb");
	ofp = fopen("./encryptedText.txt", "w");
	

	//make sure the files were found correctly
	assert(kfp != NULL);
	assert(ifp != NULL);
	assert(ofp != NULL);

    
	//this block gets the message/key lengths.
	//go to the end of the file
	fseek(kfp, 0L, SEEK_END);
	//ftell returns the position of the current char, which is the last one in the file 
	kLength = ftell(kfp);
	//return to the beginning
	fseek(kfp, 0L, SEEK_SET);
	//same as before
	fseek(ifp, 0L, SEEK_END);
	messageLength = ftell(ifp);
	fseek(ifp, 0L, SEEK_SET);

	unsigned char *key;
	key = (char *)malloc(kLength*sizeof(char));
	for(i=0; i<kLength; i++)
	{
		*(key+i) = fgetc(kfp);
	}

	unsigned char *message;
	message = (char *)malloc(messageLength*sizeof(char));
	for(i=0; i<messageLength; i++)
	{
		*(message+i) = fgetc(ifp);
	}



	//initialize S
	unsigned char S[256];
	//fill S with [0, 1, 2, 3, ..., 255] as chars
	for(i=0; i<256; i++)
        {
        	S[i] = (char)i;
        }


	//initialize T.
	unsigned char T[256];
	//go through T setting T[i] = key[i mod kLength]
	for(i=0; i<256; i++)
	{
		//note that for 0<=i<256, i mod kLength = i, so T=key if they're the same length or key is longer.
		//kLength_test should be replaced with kLength once the I/O stuff is working
		T[i] = *(key+(i % kLength));
	}


	//permute S to get everything set up.
	j=0;
	for(i=0; i<256; i++)
	{
		//set up j
		j = (j + (int)S[i] + (int)T[i]) % 256;
		//swap S[i] and S[j]
		char S_ti = S[i];
		char S_tj = S[j];
		S[i] = S_tj;
		S[j] = S_ti;
	}


	//prints shit out: this is just for testing
	printf("kLength: %d\n\n", kLength);
	printf("messageLength: %d\n\n", messageLength);
	printf("keyFile.txt: ");
	for(i=0; i<kLength; i++)
	{
		printf("%c", *(key+i));
	}
	printf("\n\n");
	printf("plainText.txt: ");
	for(i=0; i<messageLength; i++)
	{
		printf("%c", *(message+i));
	}
	printf("\n\n");
	printf("S: ");
	for(i=0; i<256; i++)
	{
		printf("%c", S[i]);
		printf(", ");
	}
	printf("\n\n");
	printf("T: ");
	for(i=0; i<256; i++)
	{
		printf("%c", T[i]);
		printf(", ");
	}
	printf("\n\n");

	


	//close the files
	fclose(kfp);
	fclose(ofp);
	fclose(ifp);
}
