
import time
import phe.paillier as paillier

ITERATIONS = 100
KEY_SIZES = [1024, 2048, 3072, 4096]

PLAINTEXTS = {
    'small': 42,
    'large': 9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729
}

def decryption(key_size, plaintext):

    pubkey, prikey = paillier.generate_paillier_keypair(n_length=key_size)
    m = PLAINTEXTS[plaintext]
    c = pubkey.encrypt(m)

    start = time.time()

    for _ in range(ITERATIONS):
        n = prikey.decrypt(c)

    stop = time.time()

    diff = stop - start
    diff = diff / ITERATIONS
    print("decryption (%d, %s): %fms" % (key_size, plaintext, diff * 1000))


if __name__ == "__main__":
    for key_size in KEY_SIZES:
        for plaintext in PLAINTEXTS.keys():
            decryption(key_size, plaintext)
