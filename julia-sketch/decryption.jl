include("paillier.jl")

include("primes.jl")
include("plaintexts.jl")

ITERATIONS = 100

PUBKEYS = Dict()
for (keysize, primes) in PRIMES
  PUBKEYS[keysize] = PublicEncryptionKey(primes[1], primes[2])
end

PRIKEYS = Dict()
for (keysize, primes) in PRIMES
  PRIKEYS[keysize] = PrivateDecryptionKey(primes[1], primes[2])
end

function bench_decryption(keysize, plaintext)
  pubkey = PUBKEYS[keysize]
  prikey = PRIKEYS[keysize]
  m = PLAINTEXTS[plaintext]
  c = encrypt(pubkey, m)

  total_time = 0.0
  for i = 1:ITERATIONS
    tic()
    decrypt(prikey, c)
    total_time += toq()
  end

  total_time = total_time / ITERATIONS
  total_time_in_milliseconds = total_time * 1000.0
  println("Decryption ($keysize, $plaintext): $total_time_in_milliseconds ms")
end

for keysize in keys(PRIMES)
  for plaintext in keys(PLAINTEXTS)
    bench_decryption(keysize, plaintext)
  end
end
