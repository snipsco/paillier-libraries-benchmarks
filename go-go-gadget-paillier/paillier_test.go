package paillier_test

import (
	"crypto/rand"

	"github.com/roasbeef/go-go-gadget-paillier"

	"math/big"
	"testing"
)

func benchmarkKey(size int, b *testing.B) {
	for n := 0; n < b.N; n++ {
		paillier.GenerateKey(rand.Reader, size)
	}
}

func benchmarkEncryptionSmall(size int, b *testing.B) {
	m := new(big.Int).SetInt64(42)
	privKey, err := paillier.GenerateKey(rand.Reader, size)
	if err != nil {
		println("error")
	}
	for n := 0; n < b.N; n++ {
		paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	}
}

func benchmarkEncryptionLarge(size int, b *testing.B) {
	m := new(big.Int)
	privKey, err := paillier.GenerateKey(rand.Reader, size)
	if err != nil {
		println("error")
	}
	for n := 0; n < b.N; n++ {
		paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	}
}

func benchmarkDecryptionSmall(size int, b *testing.B) {
	m := new(big.Int).SetInt64(42)
	privKey, err := paillier.GenerateKey(rand.Reader, size)
	if err != nil {
		println("error")
	}
	c, err := paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	if err != nil {
		println("error")
	}

	for n := 0; n < b.N; n++ {
		paillier.Decrypt(privKey, c)
	}
}

func benchmarkDecryptionLarge(size int, b *testing.B) {
	m := new(big.Int)
	m.SetString("9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729", 10)
	privKey, err := paillier.GenerateKey(rand.Reader, size)
	if err != nil {
		println("error")
	}
	c, err := paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	if err != nil {
		println("error")
	}

	for n := 0; n < b.N; n++ {
		paillier.Decrypt(privKey, c)
	}
}

func benchmarkAddition(size int, b *testing.B) {
	ms := new(big.Int).SetInt64(42)
	m := new(big.Int)
	m.SetString("9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729", 10)
	privKey, errz := paillier.GenerateKey(rand.Reader, size)
	if errz != nil {
		println("error")
	}
	c, err := paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	cs, errs := paillier.Encrypt(&privKey.PublicKey, ms.Bytes())
	if err != nil {
		println("error")
	}

	if errs != nil {
		println("error")
	}

	for n := 0; n < b.N; n++ {
		paillier.AddCipher(&privKey.PublicKey, c, cs)
	}
}

func BenchmarkKey1024(b *testing.B) { benchmarkKey(1024, b) }
func BenchmarkKey2048(b *testing.B) { benchmarkKey(2048, b) }
func BenchmarkKey3072(b *testing.B) { benchmarkKey(3072, b) }
func BenchmarkKey4096(b *testing.B) { benchmarkKey(4096, b) }

func BenchmarkEncryptionSmall1024(b *testing.B) { benchmarkEncryptionSmall(1024, b) }
func BenchmarkEncryptionSmall2048(b *testing.B) { benchmarkEncryptionSmall(2048, b) }
func BenchmarkEncryptionSmall3072(b *testing.B) { benchmarkEncryptionSmall(3072, b) }
func BenchmarkEncryptionSmall4096(b *testing.B) { benchmarkEncryptionSmall(4096, b) }

func BenchmarkEncryptionLarge1024(b *testing.B) { benchmarkEncryptionLarge(1024, b) }
func BenchmarkEncryptionLarge2048(b *testing.B) { benchmarkEncryptionLarge(2048, b) }
func BenchmarkEncryptionLarge3072(b *testing.B) { benchmarkEncryptionLarge(3072, b) }
func BenchmarkEncryptionLarge4096(b *testing.B) { benchmarkEncryptionLarge(4096, b) }

func BenchmarkDecryptionSmall1024(b *testing.B) { benchmarkDecryptionSmall(1024, b) }
func BenchmarkDecryptionSmall2048(b *testing.B) { benchmarkDecryptionSmall(2048, b) }
func BenchmarkDecryptionSmall3072(b *testing.B) { benchmarkDecryptionSmall(3072, b) }
func BenchmarkDecryptionSmall4096(b *testing.B) { benchmarkDecryptionSmall(4096, b) }

func BenchmarkDecryptionLarge1024(b *testing.B) { benchmarkDecryptionLarge(1024, b) }
func BenchmarkDecryptionLarge2048(b *testing.B) { benchmarkDecryptionLarge(2048, b) }
func BenchmarkDecryptionLarge3072(b *testing.B) { benchmarkDecryptionLarge(3072, b) }
func BenchmarkDecryptionLarge4096(b *testing.B) { benchmarkDecryptionLarge(4096, b) }

func BenchmarkAdditionLarge1024(b *testing.B) { benchmarkAddition(1024, b) }
func BenchmarkAdditionLarge2048(b *testing.B) { benchmarkAddition(2048, b) }
func BenchmarkAdditionLarge3072(b *testing.B) { benchmarkAddition(3072, b) }
func BenchmarkAdditionLarge4096(b *testing.B) { benchmarkAddition(4096, b) }

func TestCorrectness(t *testing.T) {
	// Generate a 128-bit private key.
	privKey, err := paillier.GenerateKey(rand.Reader, 128)
	if err != nil {
		t.Fatalf("Unable to generate private key: ", err)
	}

	// Encrypt the integer 15.
	m := new(big.Int).SetInt64(15)
	c, err := paillier.Encrypt(&privKey.PublicKey, m.Bytes())
	if err != nil {
		t.Fatalf("Unable to encrypt plain text: ", err)
	}

	// Now decrypt the cipher text. Should come back out to 15.
	d, err := paillier.Decrypt(privKey, c)
	if err != nil {
		t.Fatalf("Unable to decrypt cipher text: ", err)
	}
	originalInt := new(big.Int).SetBytes(d)
	if originalInt.Cmp(m) != 0 { // originalInt != 15
		t.Fatalf("Scheme is not correct. Got %v back should've got %v",
			originalInt.String(), m.String())
	}
}

func TestHomomorphicCipherTextAddition(t *testing.T) {
	// Generate a 128-bit private key.
	privKey, err := paillier.GenerateKey(rand.Reader, 128)
	if err != nil {
		t.Fatalf("Unable to generate private key: ", err)
	}

	// Encrypt the integer 15.
	m15 := new(big.Int).SetInt64(15)
	c15, err := paillier.Encrypt(&privKey.PublicKey, m15.Bytes())
	if err != nil {
		t.Fatalf("Unable to encrypt plain text: ", err)
	}

	// Encrypt the integer 20.
	m20 := new(big.Int).SetInt64(20)
	c20, err := paillier.Encrypt(&privKey.PublicKey, m20.Bytes())
	if err != nil {
		t.Fatalf("Unable to encrypt plain text: ", err)
	}

	// Now homomorphically add the encrypted integers.
	addedCiphers := paillier.AddCipher(&privKey.PublicKey, c15, c20)

	// When decrypted, the result should be 15+20 = 35
	plaintext, err := paillier.Decrypt(privKey, addedCiphers)
	if err != nil {
		t.Fatalf("Unable to decrypted cipher text: ", err)
	}
	decryptedInt := new(big.Int).SetBytes(plaintext)
	if decryptedInt.Cmp(new(big.Int).SetInt64(35)) != 0 {
		t.Fatalf("Incorrect. Plaintext decrypted to %v should be %v",
			decryptedInt.String(), 35)
	}
}

func TestHomomorphicConstantAddition(t *testing.T) {
	// Generate a 128-bit private key.
	privKey, err := paillier.GenerateKey(rand.Reader, 128)
	if err != nil {
		t.Fatalf("Unable to generate private key: ", err)
	}

	// Encrypt the integer 15.
	m15 := new(big.Int).SetInt64(15)
	c15, err := paillier.Encrypt(&privKey.PublicKey, m15.Bytes())
	if err != nil {
		t.Fatalf("Unable to encrypt plain text: ", err)
	}

	// Attempt to add the plaintext constant "10" to our encrypted integer
	// "15".
	ten := new(big.Int).SetInt64(10)
	encryptedAdd := paillier.Add(&privKey.PublicKey, c15, ten.Bytes())
	plainText, err := paillier.Decrypt(privKey, encryptedAdd)
	if err != nil {
		t.Fatalf("Unable to decrypt cipher text: ", err)
	}
	decryptedInt := new(big.Int).SetBytes(plainText)

	// When decrypted, the result should be 15+10 = 25
	if decryptedInt.Cmp(new(big.Int).SetInt64(25)) != 0 {
		t.Fatalf("Incorrect. Plaintext decrypted to %v should be %v",
			decryptedInt.String(), 25)
	}

}

func TestHomomorphicConstantMultiplication(t *testing.T) {
	// Generate a 128-bit private key.
	privKey, err := paillier.GenerateKey(rand.Reader, 128)
	if err != nil {
		t.Fatalf("Unable to generate private key: ", err)
	}

	// Encrypt the integer 15.
	m15 := new(big.Int).SetInt64(15)
	c15, err := paillier.Encrypt(&privKey.PublicKey, m15.Bytes())
	if err != nil {
		t.Fatalf("Unable to encrypt plain text: ", err)
	}

	// Attempt to multiply our encrypted integer
	ten := new(big.Int).SetInt64(10)
	encryptedAdd := paillier.Mul(&privKey.PublicKey, c15, ten.Bytes())
	plainText, err := paillier.Decrypt(privKey, encryptedAdd)
	if err != nil {
		t.Fatalf("Unable to decrypt cipher text: ", err)
	}
	decryptedInt := new(big.Int).SetBytes(plainText)

	// When decrypted, the result should be 15*10 = 150
	if decryptedInt.Cmp(new(big.Int).SetInt64(150)) != 0 {
		t.Fatalf("Incorrect. Plaintext decrypted to %v should be %v",
			decryptedInt.String(), 150)
	}
}
