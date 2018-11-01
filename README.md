# CAST256
C++ realization algorithm block cipher CAST256 (CAST6).
##### Support CBC mode only.

## Usage
Run: ./cast6 <options> <INPUT_FILE> <OUTPUT_FILE>

##### Options:
| Key         | option      |                                        DESCRIPTION                                   |
|:-----------:|:-----------:|:------------------------------------------------------------------------------------:|
|  -m, --mode | \<MODE>     | Set mod of program. MODE may be <encrypt>, <decrypt>                                |
|  -k, --key  | \<KEY>      | Set key for encryption or decryption. Size must be 128, 160, 192, 224 or 256 bits.  |           
|  -v, --iv   | \<IV>       | Set initialization vector. Size of IV must be 128 bits.                             |
|  -i, --inp  |\<INPUT_FILE>| You can use this option ONLY with -k AND -v
    You also can set <INPUT_FILE> without options
    It is described above. Then input file must contains:
    1st line: key (128, 160, 192, 224 or 256 bits)
    2nd line: 128-bit initialization vector
    3rd line: plaint text or cipher text