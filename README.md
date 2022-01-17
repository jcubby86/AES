# AES
tests can be run with ./test.sh
usage:\t./test.sh program {128|192|256|all} [-d]
use the -d flag to compare using diff against expected files from FIPS spec
the code will automatically be compiled when you do this.

You can also compile the code with make and run with ./main
usage: %s infile {128|192|256} keyfile [-dt]
the -t flag will output every intermediate state of the code
the -d flag will decrypt only, without it the text will be encrypted and then decrypted

I did not use any resources not listed on the course website

All test cases in Appendix C pass.
