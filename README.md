## Run on AWS EC2

### Install basic dependencies

Compilers etc.:
```
sudo apt-get install build-essential
```

GMP:
```
sudo apt-get install libgmp10 libgmp-dev libmpfr-dev libmpc-dev
```

### Install Rust + nightly toolchain

From https://rustup.rs/:
```
curl https://sh.rustup.rs -sSf | sh
```

Then add `~/.cargo/bin` to `PATH`:
```
echo "PATH=\$PATH:~/.cargo/bin" >> ~/.bashrc
source ~/.bashrc
```

And finally install the nightly toolchain:
```
rustup toolchain install nightly
rustup default nightly
```

### Install Python and depencencies

Python3:
```
sudo apt-get install python3 python3-dev
```

`virtualenv` (optional):
```
sudo apt-get install virtualenv
echo "export LC_ALL=C" >> ~/.bashrc
source ~/.bashrc
```
