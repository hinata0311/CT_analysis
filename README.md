# CE65 CT-test, July 2025 @ Kyorin University

**authors** : Kai Teramoto, Hinata Nakamura

## Description
This is the analysis utils for analyzing data from CE-65 (AC amp) DAQ, and modified for lab test using CT-scanner. 

## Build
```shell
$ make clean
$ make
mv build/ce65dict_rdict.pcm build/lib/ # recommend this
```
## Tests
Put test file on `../data/tree/` or change `DEFAULT_INPUT_DIRECTORY` in `globals.h` into your own input file directory. and just excecute **`utils/src_test.sh`**

## Class definition