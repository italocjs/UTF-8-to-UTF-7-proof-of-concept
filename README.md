# UTF8 to UTF7 compactor

This code demonstrate the possibility of converting a stream of data from UTF8 (8bits) into UTF7 (7bits). This can save up to 15% in storage/transmission, but will restrict the characters you can use to (a-z, A-Z, 0-9) and some basic symbols.

Why would i use this?
- if you need to send text data over expensive metered connections (i.e sattelite).
- if you need to send text data over LoRa, BLE and procotols which restrict the transmission rate. 
- if you need to store data somewhere extremely limited.

How does it works?
- Usually letters in ascii/utf8 are stored within one byte, which hold up to 255 characters, since most of the basic characters and control characters are stored before 127, its possible to reduce the data size from 8bits to 7bits.
- This example will first encode the incoming string to binary (7bit per char), 
- Then it will divide the binary in blocks of 8bits.  the output data will be of course completely distorted (as we have 7bits from char1 and 1bit from char2).
- To restore the data to its original format, we just need to break the distorted string again into binary and split it in groups of 7bits. the data will be back to the expected format.

Notes:
- Check accepted_characters.txt to find out which characters can be used (up to ascii DEC 127 HEX 7F).
- Characters above 127 will be represented by an "space" (ascii 32).
- this code is definitely NOT optimized for deployment in embedded systems, there is a huge processing overhead that can be removed using bit manipulation magic, but for demonstration purposes its acceptable. (if you improve it, please share the new code as a PR).
