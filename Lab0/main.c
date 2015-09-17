//
//  main.c
//  Lab0


#include <stdio.h>

int main(int argc, const char * argv[]) {
	// insert code here...
	FILE *ifp;
	FILE *ofp;
	
	ifp = fopen("./plainTextFile.txt", "r");
	ofp = fopen("./outputFile.txt", "w");

	int i;
	char S[i];
	
	
	
	
	for (i=0; i<256; i++){
		S[i]=i;
		printf("%i ",i);
	}
	
	assert(ifp != NULL);
	assert(ofp != NULL);
	/*initialized an array with 256 entries for S*/
    return 0;
}
