include("paillier.jl")

include("primes.jl")
include("plaintexts.jl")

ITERATIONS = 100

PUBKEYS = Dict()
for (keysize, primes) in PRIMES
  PUBKEYS[keysize] = PublicEncryptionKey(primes[1], primes[2])
end

function bench_encryption(keysize, plaintext1, plaintext2)
  pubkey = PUBKEYS[keysize]
  m1 = PLAINTEXTS[plaintext1]
  m2 = PLAINTEXTS[plaintext2]
  c1 = encrypt(pubkey, m1)
  c2 = encrypt(pubkey, m2)

  total_time = 0.0
  for i = 1:ITERATIONS
    tic()
    add(pubkey, c1, c2)
    total_time += toq()
  end

  total_time = total_time / ITERATIONS
  total_time_in_milliseconds = total_time * 1000.0
  println("Addition ($keysize, $plaintext1, $plaintext2): $total_time_in_milliseconds ms")
end

for keysize in keys(PRIMES)
  bench_encryption(keysize, "small", "large")
end
