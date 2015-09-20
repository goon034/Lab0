//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int getFileLength(FILE *);
unsigned char *copyFileToCharPointer(FILE *, int);
unsigned char *generateS(unsigned char *, int);
unsigned char generateKeyByte(unsigned char *);

int main(int argc, const char * argv[]) {
	
	//declare file pointers
	FILE *kfp;
	FILE *ifp;
	FILE *ofp;
	//declare char pointers to store read file contents
	unsigned char *key;
	unsigned char *message;
	//declare the message/key lengths
	int kLength;
	int messageLength;
 
	//open the files. note that the input files should be in the same directory as the C file.
	kfp = fopen("./keyFile.txt", "rb");
	ifp = fopen("./encryptedText.txt", "rb");
	ofp = fopen("./originalText.txt", "w");
	
	//make sure the files were found correctly
	assert(kfp != NULL);
	assert(ifp != NULL);
	assert(ofp != NULL);
	
	//get file lengths
	kLength = getFileLength(kfp);
	messageLength = getFileLength(ifp);
	
	//create pointer "arrays"
	key = copyFileToCharPointer(kfp, kLength);
	message = copyFileToCharPointer(ifp, messageLength);
	
	//generate S
	unsigned char *S = generateS(key, kLength);
	
	//encrypt or decrypt the message by generating the keystream, XOR-ing it with the text file and
	//writing to the file pointed to by ifp
	for(int i=0; i<messageLength; i++){
		unsigned char c = generateKeyByte(S+i);
		c = c ^ *(message+i);
		fputc(c, ofp);
	}
	
	//close the files
	fclose(kfp);
	fclose(ofp);
	fclose(ifp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int getFileLength(FILE *file){
	//go to the end of the file
	fseek(file, 0L, SEEK_END);
	//ftell returns the position of the current char, which is the last one in the file
	int length = (int)ftell(file);
	//return to the beginning
	fseek(file, 0L, SEEK_SET);
	return length;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char *copyFileToCharPointer(FILE *file, int fileLength){
	unsigned char *contents;
	contents = (unsigned char *)malloc(fileLength*sizeof(char));
	for(int i=0; i<fileLength; i++)
	{
		*(contents+i) = fgetc(file);
	}
	return contents;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char *generateS(unsigned char *key, int kLength){
	unsigned char *s = (unsigned char *)malloc(256*sizeof(char));
	//fill S with [0, 1, 2, 3, ..., 255] as chars
	for(int i=0; i<256; i++)
	{
		*(s+i) = (char)i;
	}
	
	//initialize T.
	unsigned char *T;
	T = (unsigned char *)malloc(256*sizeof(char));
	//go through T setting T[i] = key[i mod kLength]
	for(int i=0; i<256; i++)
	{
		//note that for 0<=i<256, i mod kLength = i, so T=key if they're the same length or key is longer.
		*(T+i) = *(key+(i % kLength));
	}
	
	//permute S to get everything set up.
	int j=0;
	for(int i=0; i<256; i++)
	{
		//set up j
		j = (j + (int)(*(s+i)) + (int)(*(T+i))) % 256;
		//swap S[i] and S[j]
		char s_ti = *(s+i);
		char s_tj = *(s+j);
		*(s+i) = s_tj;
		*(s+j) = s_ti;
	}
	return s;
}
