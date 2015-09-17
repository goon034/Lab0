# Lab0
Lab 0: Encryption and Decryption

This is a symmetric algorithm, meaning that the same operations are used for both encryption
and decryption. The algorithm consists of generating a key stream starting from an initial key of
length up to 256 bytes. This key stream is bit-wise ex-ored with the stream of bytes representing
the message to be encrypted. (These bytes are in the form of chars; recall that a char variable is
one byte long.
