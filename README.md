# CheekyKitten
The Cheeky Kitten encoder is a simple binary obsfucation tool. Designed to be quick to run and effective at hiding data. It uses a simple "hex shuffle" algorithm to corrupt encode the binary data in such a way that it can be easily decoded, but that statistically looks completely different to the original.

This is the software which implements my quadcode algorithm. My original concept was to have a message interpreted from UTF-8 to hex and then written from top down, instead of left to write... then the 16's place of the first byte would be concatonated with the 16's place of the next byte and same with the 1's on the line bellow. This is a new concept that should be easier to translate onto a computer program and will be more lightweight and faster. Instead the 64-bit(8 bytes) line in hex would be grouped into 4 sections line by line as so:

|XX|YY| |XX|YY| |XX|YY| |XX|YY|

(For every group or every two bytes of input: x,y)

*All mathmatical operations are performed in base 16... so modulo 0x10 would be modulo 16 in regular decimal.

 X | Y --> Input Bytes(in hexadecimal)

ab | cd --> To help you visualise what the variables represent(since X and Y will always be two digits long - even if only 01)

b = x mod 0x10

d = y mod 0x10

x = (y -d) + (x / 0x10);

y = (d * 0x10) + b;

Move onto next group...

# INSTALL

Download and compile from source: 

`git clone https://github.com/TheJostler/CheekyKitten.git`

`make`

`sudo make install`


# USAGE
 
    cheeky / cheekytesting [options] -input file- -output file-
    CheekyKitten will default to stdout/stdin if i/o files are not provided
              -h           Print this help menu

              -r           Reverse
 
              -b           Output as binary 
 
Some examples:

`cheeky file file.cheek`       -will input binary from file and write cheeky code to .cheek file-

`cheeky file`                  -will input binary from file and output human readable cheeky code(hex) from IXI function-

`cheeky file -b > file.cheek`  -will input binary from file and output binary cheeky code, bash then redirects to file.cheek-

`echo "hi" | cheeky`           -will input binary from stdin and output human readable cheeky code(hex)-

# .cheek File mime-types

If you would like to add .cheek mime types to your system so that your computer can recognise files encoded with cheekykitten, the files in the MIME directory can help you add .cheek mime-types to your system, I haven't created an automatic installer for doing this however it's not difficult. Search on Google how to add mime types to your particular system if you want...

This step is not necessary for the normal functioning of cheekykitten!

Have Fun! =D
