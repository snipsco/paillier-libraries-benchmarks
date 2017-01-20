
# phe

This is the bench of the [phe](https://github.com/NICTA/python-paillier) library.

## Prerequisites

GMP.

## Installation

### Create virtual environment (optionally)
```
virtualenv -p python3 env
source env/bin/activate
```

### Install dependencies
```
pip3 install phe
```

## Benching

Run all in sequence:
```
python3 keygen.py && python3 encryption.py && python3 decryption.py && python3 addition.py
```

or specific ones:
```
python3 keygen.py
python3 encryption.py
python3 decryption.py
python3 addition.py
```
