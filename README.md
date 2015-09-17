# Lab0
main:
//get arrays containing the key and message to "crypt"
//algorithm is symmetric so we don't specify whether we're performing an encryption or decryption
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
//function is void, no return
