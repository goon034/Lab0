//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

unsigned char generateKeyByte(unsigned char *s);

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
	kLength = (int)ftell(kfp);
	//return to the beginning
	fseek(kfp, 0L, SEEK_SET);
	//same as before
	fseek(ifp, 0L, SEEK_END);
	messageLength = (int)ftell(ifp);
	fseek(ifp, 0L, SEEK_SET);
	
	unsigned char *key;
	key = (unsigned char *)malloc(kLength*sizeof(char));
	for(i=0; i<kLength; i++)
	{
		*(key+i) = fgetc(kfp);
	}
	
	unsigned char *message;
	message = ( unsigned char *)malloc(messageLength*sizeof(char));
	for(i=0; i<messageLength; i++)
	{
		*(message+i) = fgetc(ifp);
	}
	
	
	
	//initialize S
	unsigned char *S;
	S = (unsigned char *)malloc(256*sizeof(char));
	//fill S with [0, 1, 2, 3, ..., 255] as chars
	for(i=0; i<256; i++)
	{
		*(S+i) = (char)i;
	}
	
	
	//initialize T.
	unsigned char *T;
	T = (unsigned char *)malloc(256*sizeof(char));
	//go through T setting T[i] = key[i mod kLength]
	for(i=0; i<256; i++)
	{
		//note that for 0<=i<256, i mod kLength = i, so T=key if they're the same length or key is longer.
		*(T+i) = *(key+(i % kLength));
	}
	
	
	//permute S to get everything set up.
	j=0;
	for(i=0; i<256; i++)
	{
		//set up j
		j = (j + (int)(*(S+i)) + (int)(*(T+i))) % 256;
		//swap S[i] and S[j]
		char S_ti = *(S+i);
		char S_tj = *(S+j);
		*(S+i) = S_tj;
		*(S+j) = S_ti;
	}
	
	
	
	for(i=0; i<messageLength; i++){
		unsigned char c = generateKeyByte(S+i);
		c = c ^ *(message+i);
		fputc(c, ofp);
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
		printf("%c", *(S+i));
		printf(", ");
	}
	printf("\n\n");
	printf("T: ");
	for(i=0; i<256; i++)
	{
		printf("%c", *(T+i));
		printf(", ");
	}
	printf("\n\n");
	
	
	
	
	//close the files
	fclose(kfp);
	fclose(ofp);
	fclose(ifp);
}



unsigned char generateKeyByte(unsigned char *s){
	static int i = 0;
	static int j = 0;
	static int t = 0;
	i = (i+1) % 256;
	j = (j + *(s+i)) % 256;
	//Swap *(s+i) and *(s+j)
	unsigned char s_ti = *(s+i);
	unsigned char s_tj = *(s+i);
	*(s+i) = s_tj;
	*(s+j) = s_ti;
	t = (*(s+i) + *(s+j)) % 256;
	return *(s+t);
}
