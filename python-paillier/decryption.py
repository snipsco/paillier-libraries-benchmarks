
import time
from paillier.paillier import *

ITERATIONS = 10
KEY_SIZES = [1024, 2048]

PLAINTEXTS = {
    'small': 42,
    'large': 9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729
}

def decryption(key_size, plaintext):

    prikey, pubkey = generate_keypair(key_size)
    m = PLAINTEXTS[plaintext]
    c = encrypt(pubkey, m)

    start = time.time()

    for _ in range(ITERATIONS):
        n = decrypt(prikey, pubkey, c)

    stop = time.time()

    diff = stop - start
    diff = diff / ITERATIONS
    print("decryption (%d, %s): %fms" % (key_size, plaintext, diff * 1000))


if __name__ == "__main__":
    for key_size in KEY_SIZES:
        for plaintext in PLAINTEXTS.keys():
            decryption(key_size, plaintext)
