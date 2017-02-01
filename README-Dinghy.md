# Running the Rust/Ramp bench on Phones

rust-paillier-ramp can be relatively easily ran on iOS and Android devices.

If you're already an iOS and Android developper, and the bench are already
running on your computer, then all you need is to install the phone toolchain,
then dinghy. [Dinghy](https://medium.com/p/c9f94f81d305/edit) is a tool we are
developping to spawn rust test and benches on iOS and Android devices.

For relatively recent apple devices:

```
rustup target install aarch64-apple-ios
```

For android

```
rustup target install arm-linux-androideabi
```

Then

```
cargo install dinghy
```

Plug-in your phone, unlock it...

```
cd rust-paillier-ramp
cargo dinghy bench
```

If you're not a registered iOS or Android user, then you will have some setup to
do, which is detailed in [Dinghy Readme](https://github.com/snipsco/dinghy).
