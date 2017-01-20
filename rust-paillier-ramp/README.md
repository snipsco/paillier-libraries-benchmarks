# rust-paillier

This is the bench of the [rust-paillier](https://github.com/snipsco/rust-paillier) library written in Rust and using RAMP.

## Benching

Either run all of them:
```
cargo bench
```

or specific ones:
```
cargo bench --bench keygen
cargo bench --bench encryption
cargo bench --bench decryption
cargo bench --bench addition
```
