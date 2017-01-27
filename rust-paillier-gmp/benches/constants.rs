
#![allow(dead_code)]

use paillier::*;

static SMALL: &'static str = "42";
static LARGE: &'static str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";

pub trait KeySize { fn get() -> usize; }
pub struct KeySize1024; impl KeySize for KeySize1024 { fn get() -> usize { 1024 } }
pub struct KeySize2048; impl KeySize for KeySize2048 { fn get() -> usize { 2048 } }
pub struct KeySize3072; impl KeySize for KeySize3072 { fn get() -> usize { 3072 } }
pub struct KeySize4096; impl KeySize for KeySize4096 { fn get() -> usize { 4096 } }

pub trait Plaintext { fn get() -> BigInteger; }
pub struct PlaintextSmall; impl Plaintext for PlaintextSmall { fn get() -> BigInteger { str::parse(SMALL).unwrap() } }
pub struct PlaintextLarge; impl Plaintext for PlaintextLarge { fn get() -> BigInteger { str::parse(LARGE).unwrap() } }

pub type StandardEncryption = core::standard::EncryptionKey<BigInteger>;
pub type GenericEncryption = core::generic::EncryptionKey<BigInteger>;

pub type StandardDecryption = core::standard::DecryptionKey<BigInteger>;
pub type CrtDecryption = core::crt::DecryptionKey<BigInteger>;
