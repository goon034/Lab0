//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

char generateKeyByte(char *s);

int main(int argc, const char * argv[]) {
	
	//test key and length. this should be removed once the I/O's running.
	unsigned char key[256] = {'f', 'l', 'o', 'w', 'e', 'r', 's', ' ', 'a', 'r', 'e', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 't', 'e', 'l', 'y', ' ', 'l', 'o', 'o', 'v', 'e', 'l', 'y', '.', ' ', 'f', 'l', 'o', 'w', 'e', 'r', 's', ' ', 'l', 'o', 'o', 'k', ' ', 'l', 'i', 'k', 'e', 'a', 's', 'd', 'f', 'g', 'h', '!', '@', '#', '$', '%', '^', '&', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', 'l', 'i', 'e', 'n', 's', '.', ' ', 'T', 'h', 'e', ' ', 'b', 'i', 'g', 'e' , 'a', 'l', ' ', 'a', 'b', 'o', 'u', 't', ' ', 'f', 'l', 'o', 'w', 'e', 'r', 's', ' ', 'i', 's', ' ', 'b', 'o', 't', 'a', 'n', 'i', 'c', 'a', 'l', '.', ' ', 'E', 'v', 'e', 'r', 'y', 't', 'h', 'i', 'n', 'g', ' ', 'a', 'b', 'o', 'u', 't', ' ', 't', 'h', 'e', 'm', ' ', 's', 'u', 'c', 'k', 's', '.', 'x', 'x', 'x', 'x', '(', 'r', 'u', 'l', 'e', 's', ':', ')', ')', ' ', 's', 'e', 'n', 'd', 'm', 'e', ' ', '$', '7', '0', '0', ',', '0', '0', '0', ',', '0', '0', '0', ',', '0', '0', '0', ',', '0', '0', 'i', 'b', 'u', 't', 'i', 'o', 'n', ' ', 't', 'o', ' ', 't', 'h', 'e', ' ', 'p', 'r', 'o', 'j', 'e', 'k', 't', ' ', 'a', 'n', 'd', ' ', 'a', ' ', 'N', 'o', 'b', 'e', 'l', ' ', 'p', 'r', 'i', 'z', 'e', ' ', ' ', '.', '.', '.', '.', ')', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
	int kLength_test = 256;
	
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
	kfp = fopen("./keyFile.txt", "rb"); //read in binary: "rb"
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
	kLength = (int) ftell(kfp);
	//return to the beginning
	fseek(kfp, 0L, SEEK_SET);
	//same as before
	fseek(ifp, 0L, SEEK_END);
	messageLength = (int) ftell(ifp);
	fseek(ifp, 0L, SEEK_SET);
	
	
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
		T[i] = key[i % kLength_test];
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
		printf("%c", fgetc(kfp));
	}
	printf("\n\n");
	printf("plainText.txt: ");
	for(i=0; i<messageLength; i++)
	{
		printf("%c", fgetc(ifp));
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
	printf("key: ");
	for(i=0; i<256; i++)
	{
		printf("%c", key[i]);
		printf(", ");
	}
	
	
	
	
	//close the files
	fclose(kfp);
	fclose(ofp);
	fclose(ifp);
}

char generateKeyByte(char *s){
	static int i = 0;
	static int j = 0;
	static int t = 0;
	i = (i+1) % 256;
	j = (j + *(s+i)) % 256;
	//Swap *(s+i) and *(s+j)
	char s_ti = *(s+i);
	char s_tj = *(s+i);
	*(s+i) = s_tj;
	*(s+j) = s_ti;
	t = (*(s+i) + *(s+j)) % 256;
	return *(s+t);
}
