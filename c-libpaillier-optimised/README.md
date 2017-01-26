# libpaillier

This is the bench of [libpaillier](http://acsc.cs.utexas.edu/libpaillier/) written in C, with optimised encryption.

## Prerequisites

Requires GMP to be installed.


## Installation

Run the following to build the libpaillier library:
```
git clone https://github.com/mortendahl/libpaillier.git
cd libpaillier
./configure
make
cd ..
```
which on AWS must be done with the path to GMP explicitly specified:
```
git clone https://github.com/mortendahl/libpaillier.git
cd libpaillier
./configure --with-gmp-include=/usr/include/x86_64-linux-gnu/ --with-gmp-lib=/usr/lib/x86_64-linux-gnu/
make
cd ..
```


## Benching

Building the bench:
```
gcc -O3 bench.c libpaillier/paillier.o -Ilibpaillier -lgmp -o bench
```

Running the bench
```
./bench
```
