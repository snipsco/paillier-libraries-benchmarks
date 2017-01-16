
import time
import phe.paillier as paillier

def bench(key_size, rounds=100):

    pubkey, prikey = paillier.generate_paillier_keypair(n_length=key_size)

    m = 10

    start = time.time()

    for _ in range(rounds):
        c = pubkey.encrypt(m)
        n = prikey.decrypt(c)

    stop = time.time()
    diff = stop - start
    diff = diff / rounds
    print("keysize %d: %fms" % (key_size, diff * 1000))

key_sizes = [512, 1024, 2048]
for key_size in key_sizes:
    bench(key_size)
