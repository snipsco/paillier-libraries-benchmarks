#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

pub fn keygen<KS>(b: &mut Bencher)
where
    KS: KeySize
{
    b.iter(|| {
        let _ = Paillier::keypair_with_modulus_size(KS::get());
    });
}

pub trait KeySize { fn get() -> usize; }
struct KeySize1024; impl KeySize for KeySize1024 { fn get() -> usize { 1024 } }
struct KeySize2048; impl KeySize for KeySize2048 { fn get() -> usize { 2048 } }
struct KeySize3072; impl KeySize for KeySize3072 { fn get() -> usize { 3072 } }
struct KeySize4096; impl KeySize for KeySize4096 { fn get() -> usize { 4096 } }

benchmark_group!(group,
    keygen<KeySize1024>,
    keygen<KeySize2048>,
    keygen<KeySize3072>,
    keygen<KeySize4096>
);

benchmark_main!(group);
