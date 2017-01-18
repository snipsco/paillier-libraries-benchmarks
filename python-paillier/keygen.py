
import time
from paillier.paillier import *

ITERATIONS = 10
KEY_SIZES = [1024, 2048]

def keygen(key_size):

    start = time.time()

    for _ in range(ITERATIONS):
        pubkey, prikey = generate_keypair(key_size)

    stop = time.time()

    diff = stop - start
    diff = diff / ITERATIONS
    print("keygen (%d): %fms" % (key_size, diff * 1000))


if __name__ == "__main__":
    for key_size in KEY_SIZES:
        keygen(key_size)
