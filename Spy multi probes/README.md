# Spy program with multi probes
Here you can find the source code of a spy program to probe multiple given addresses.
The first argument must be the path to the binary, the following ones must be `label:address`

The label must be a string consisting of alphanumeric characters. The address must be in hexadecimal.

Example to probe the addresses 0x4242 and 0xbeef with the labels 'foo' and 'bar' :
```
./spy /path/to/binary foo:0x4242 bar:0xbeaf
```
