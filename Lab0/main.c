//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main(int argc, const char * argv[]) {

	//test key and length. this should be removed once the I/O's running.
	unsigned char key[256] = {'£', '\x82', 'o', 'ä', '\x0c', '\n', '5', 'å', '\x96', '\x1f', 'Á', 'Ý', 'k', '\x89', '\x87', 'ä', '_', '\x9b', 'î', '\x86', 'f', 'o', 'Ë', 'H', '\x15', '\x97', '\x17', 'S', 'þ', '.', 'b', 'B', '\x81', 'ã', '+', '\x8b', '@', '£', '\x8c', '¥', '3', '®', '\x08', 'æ', 'f', '!', 'Ë', 'ú', 'g', '\x8a', '(', '\x87', 'A', '\x15', '\x0e', 'Í', '~', '¹', '\x17', '¦', 'ú', '\x84', 'ö', 'Q', '\x10', '3', '|', 'B', 'j', '\x82', 'Ç', 'ª', '\x86', '\x19', '*', 'Ï', '÷', 'a', '\x0e', '\x03', 'Ë', 'Ã', 'N', 'Z', 'ÿ', 'x', '~', 'y', '\x0f', 'ê', 'P', 'J', '\\', '\x95', '\x83', 'æ', '·', '¾', 'Ü', 'U', 'é', 'Ë', 'ï', 'Ã', 'Ô', '!', 'ò', 'ë', 'É', '\x97', 'ß', '0', '*', '\x06', 'ý', 'j', 'µ', 'l', '»', '\x1e', '(', '\x83', '\n', 'S', 'ó', '\x98', 'w', 'i', 'Å', '\x02', 'E', 'Ì', '\x17', 'r', '¦', '¢', '^', 'Þ', '\x14', 'j', 'D', '«', '>', 'x', ']', 'ì', '\x06', '\x96', '\x86', ']', 'ê', '¤', '5', 'w', 'ú', '5', '6', 'Ï', 'û', 'C', 'ï', '$', '\x10', '\x99', 'ó', '|', '\x85', '\x94', '\x17', '¬', '\x19', 'R', '\x07', 'f', '=', 'õ', 'c', '\x1c', 'j', 'ó', 'B', 'É', '¡', '\x9b', '\x16', '\x14', '\x90', 'Ê', 'À', '=', 'à', '÷', 'ÿ', 'A', 'G', '\x98', '\x19', 'Q', 'Ù', '¤', 'Ã', '\\', '²', '\x16', '¡', '&', '\r', '\x01', '\\', '³', '¯', 'Î', '¹', 'È', 'v', 'B', 'n', 'z', 'Ú', 'b', 'P', 'Ø', '3', 'É', '\x91', 'u', 'B', '\x85', '¨', '¹', '\x1a', 'å', 'A', ']', '\x9a', 'E', '>', '\x86', '3', 'S', '¥', '_', '¢', ')', 'Ô', 'ò', '|', 'Ø', '[', '\x7f', '÷', '\x1a', 'æ', '*', 'P', '³'};
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
