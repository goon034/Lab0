//
//  main.c
//  Lab0
//
//  Created by Ygorsunny Jean on 9/15/15.
//  Copyright (c) 2015 Ygorsunny Jean. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
	// insert code here...
	int i;
	
	
	char S[i];
	
	for (i=0; i<256; i++){
		S[i]=i;
		printf("%i ",i);
	}
	
	printf("Hello, World!\n");
	printf("Hello, World2!\n");
	printf("Hello, World3!\n");
    return 0;
}

//read in key file and put everything into the key array.
/*main:
 
 key = readText(keyLocation)
 uncryptedMessage = readText(uncryptedMessageLocation)
 
 //initialize the crypted message as an empty char array with the proper length
 cryptedMessage = char[length(uncryptedMessage)]
 
 //iterate over the uncrypted message char by char
 //get key byte, XOR, put it in the crypted array
 i = 0
 while (i < length(uncryptedMessage)):
 keyByte = keyStream(key)
 cryptedMessage[i] = (uncryptedMessage[i] XOR keyByte)
 i++
 
 //write crypted array to file
 fileOut(cryptedMessageLocation, textArray)
 
 
 //functions we need:
 
 //reads a text file character by character
 //returns a character array
 readText(fileLocation):
 //code goes here
 return textArray
 
 //generates the next byte of the keystream, which is a char
 keyStream(key):
 //code goes here
 return keyByte
 
 
 //outputs a character array to a text file
 fileOut(fileLocation, textArray):
 //code goes here
 //function is void, no return*/
