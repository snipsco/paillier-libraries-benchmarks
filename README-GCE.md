# Installation on Google GCE

## Basic dependencies

Compilers etc.:
```
sudo apt-get install build-essential
```

GMP:
```
sudo apt-get install libgmp10 libgmp-dev libmpfr-dev libmpc-dev
```

## Rust and nightly toolchain

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

## Python and dependencies

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


## Java

Add Oracle repository:
```
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
```

Install Oracle Java and set as default:
```
sudo apt-get install oracle-java8-installer
sudo apt install oracle-java8-set-default
```

Install Maven
```
sudo apt-get install maven
```


## Julia

```
sudo apt-get install julia
```


## Go
```
sudo apt-get install golang
echo "export GOPATH=~/.go" >> ~/.bashrc
```
