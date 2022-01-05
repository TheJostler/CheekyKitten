# CheekyKitten
A cheeky Kitten cipher is a simple hex obsfucation cipher. Designed to be quick to run and easy to implement on hardware --- Yeeaa working on it!!

This is a dependency for my "Quadcode" project. My original concept was to have a message interpreted from UTF-8 to hex and then written from top down, instead of left to write... then the 16's place of the first byte would be concatonated with the 16's place of the next byte and same with the 1's on the line bellow. This is a new concept that should be easier to program and will be more lightweight and faster. Instead the 64-bit line in hex would be grouped into 4 sections line by line as so:
|00 | 01 | 02 | 03 | 04 | 05 | 06 | 07|
|        |         |         |        |
|group 1 | group 2 | group 3 | group 4|

and so the 16's places would be concatonated together within the same group in possition 1 and the 1's in possition two
as so (A is 16's, B is 1's)
|00 | 01 | A2 | 03 | 37 | 05 | 06 | 68| <-- Original
|AB | AB | AB | AB | AB | AB | AB | AB|
|        |         |         |        |
|00 | 01 | A0 | 23 | 30 | 75 | 06 | 68| <-- Encoded
|AA | BB | AA | BB | AA | BB | AA | BB|
|   |    |    |    |    |    |    |   |
|16 | 1  | 16 | 1  | 16 | 1  | 16 | 1 | <-- places
|group 1 | group 2 | group 3 | group 4|


(For every group or every two bytes of input: x,y)
*All mathmatical operations are performed in base 16... so modulo 0x10 would be modulo 16 in regular decimal
 X | Y --> Input Bytes
ab | cd --> To help you visualise what the variables represent

b = x mod 0x10
d = y mod 0x10
x = y -d + x / 0x10;
y = d * 0x10 + b;

Move onto next group...
