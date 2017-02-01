# Running the Rust-RAMP benches on Phones

[rust-paillier-ramp](/rust-paillier-ramp) can be relatively easily run on iOS and Android devices.

If you're already an iOS and Android developer, and the bench is already
running on your computer, then all you need is to install the phone toolchain and [Dinghy](https://medium.com/p/c9f94f81d305/edit), a tool we are
developing to spawn Rust test and benches on iOS and Android devices.

For relatively recent Apple devices:

```
rustup target install aarch64-apple-ios
```

For Android

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
