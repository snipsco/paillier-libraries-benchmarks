
import time
from paillier.paillier import *

def bench(key_size, rounds=10):

    prikey, pubkey = generate_keypair(key_size)

    m = 10

    start = time.time()

    for _ in range(rounds):
        c = encrypt(pubkey, m)
        n = decrypt(prikey, pubkey, c)

    stop = time.time()
    diff = stop - start
    diff = diff / rounds
    print("keysize %d: %fms" % (key_size, diff * 1000))

key_sizes = [512, 1024] #, 2048]
for key_size in key_sizes:
    bench(key_size)
