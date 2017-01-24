#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

mod constants;
use constants::*;

pub fn addition<KS, PT1, PT2>(b: &mut Bencher)
where
    KS: KeySize,
    PT1: Plaintext,
    PT2: Plaintext
{
    let (ek, _) = Paillier::keypair_with_modulus_size(KS::get()).keys();
    let m1 = core::Plaintext(PT1::get());
    let m2 = core::Plaintext(PT2::get());
    let c1 = Paillier::encrypt(&ek, &m1);
    let c2 = Paillier::encrypt(&ek, &m2);

    b.iter(|| {
        let _ = Paillier::add(&ek, &c1, &c2);
    });
}

benchmark_group!(group,
    addition<KeySize1024, PlaintextSmall, PlaintextLarge>,
    addition<KeySize2048, PlaintextSmall, PlaintextLarge>,
    addition<KeySize3072, PlaintextSmall, PlaintextLarge>,
    addition<KeySize4096, PlaintextSmall, PlaintextLarge>
);

benchmark_main!(group);
