# Big Data Primality Test
Test with miracl library using Fermat Test

## Compile miracl library

For Linux,

### 1、Download the zip from Github repository

[Follow the Github Link](https://github.com/miracl/MIRACL)

### 2、Create a dictionary

Create a new folder to conain the unzipped files, for example, name it miracl
```bash
mkdir miracl
```
### 3、Unzip the .zip package
Copy the zip archieve into the new create folder and run unzip command,
```bash
unzip -j -aa -L MIRACL*.zip
```
### 4、Build 

For 64-bit Linux, run command below,
```bash
bash linux64
```




After compiled, copy the `miracl.h`, `mirdef.h`, `miracl.a` to the project root folder, beside the `main.c` file.
<br></br>
## Run program

```bash
# make the project
make
# run it
./main
```

So the program will using the `data.txt` to test the program.


