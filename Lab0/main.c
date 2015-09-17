//
//  main.c
//  Lab0


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main(int argc, const char * argv[]) {
	// insert code here...
	FILE *ifp;
	FILE *ofp;
	
	ifp = fopen("./plainTextFile.txt", "r");
	ofp = fopen("./outputFile.txt", "w");

	int i;
	unsigned char S[i];
	
	
	
	
	for (i=0; i<256; i++){
		S[i]=i;
		printf("%i ",i);
	}
	
	assert(ifp != NULL);
	assert(ofp != NULL);
	/*initialized an array with 256 entries for S*/
    return 0;
}
/*
//initialize T.
unsigned char T[256];
//go through T setting T[i] = key[i mod 256]
for(i=0; i<256; i++)
{
	//note that for 0<=i<256, i mod kLength = i, so T=key if they're the same length or key is longer. Not a mistake.
	T[i] = key[i % kLength];
}

//permute S to get everything set up.
int j=0;
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

//prints the shit out: this is just for testing
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
printf("\n");
 */
