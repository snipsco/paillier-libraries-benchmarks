# Julia

This is the bench for a quick implementation of Paillier using Julia's native `BigInt` (which wraps GMP). Key generation is not implemented.

## Benching

Either run all of them:
```
julia encryption.jl && julia decryption.jl && julia addition.jl
```

or specific ones:
```
julia encryption.jl
julia decryption.jl
julia addition.jl
```
