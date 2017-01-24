#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

pub fn encryption<KS, PT>(b: &mut Bencher)
where
    KS: KeySize,
    PT: Plaintext
{
    let (ek, _) = Paillier::keypair_with_modulus_size(KS::get()).keys();
    let m = core::Plaintext(PT::get());

    b.iter(|| {
        let _ = Paillier::encrypt(&ek, &m);
    });
}

static SMALL: &'static str = "42";
static LARGE: &'static str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";

pub trait KeySize { fn get() -> usize; }
struct KeySize1024; impl KeySize for KeySize1024 { fn get() -> usize { 1024 } }
struct KeySize2048; impl KeySize for KeySize2048 { fn get() -> usize { 2048 } }
struct KeySize3072; impl KeySize for KeySize3072 { fn get() -> usize { 3072 } }
struct KeySize4096; impl KeySize for KeySize4096 { fn get() -> usize { 4096 } }

pub trait Plaintext { fn get() -> BigInteger; }
struct PlaintextSmall; impl Plaintext for PlaintextSmall { fn get() -> BigInteger { str::parse(SMALL).unwrap() } }
struct PlaintextLarge; impl Plaintext for PlaintextLarge { fn get() -> BigInteger { str::parse(LARGE).unwrap() } }

benchmark_group!(small,
    encryption<KeySize1024, PlaintextSmall>,
    encryption<KeySize2048, PlaintextSmall>,
    encryption<KeySize3072, PlaintextSmall>,
    encryption<KeySize4096, PlaintextSmall>
);

benchmark_group!(large,
    encryption<KeySize1024, PlaintextLarge>,
    encryption<KeySize2048, PlaintextLarge>,
    encryption<KeySize3072, PlaintextLarge>,
    encryption<KeySize4096, PlaintextLarge>
);

benchmark_main!(small, large);
