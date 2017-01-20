Library available at https://github.com/mikeivanov/paillier.

### Create virtual environment (optionally)
```
virtualenv -p python2 env
source env/bin/activate
```

### Install dependencies
```
cd paillier && python2 setup.py install && cd ..
```

### Run benches
```
python2 keygen.py
python2 encryption.py
python2 decryption.py
python2 addition.py
```
