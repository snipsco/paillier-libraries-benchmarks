Library available at https://github.com/NICTA/python-paillier.

### Create virtual environment (optionally)
```
virtualenv -p python3 env
source env/bin/activate
```

### Install dependencies
```
pip3 install phe
```

### Run benches

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
