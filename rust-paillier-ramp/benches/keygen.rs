#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

mod constants;
use constants::*;

pub fn keygen<KS>(b: &mut Bencher)
where
    KS: KeySize
{
    b.iter(|| {
        let _ = Paillier::keypair_with_modulus_size(KS::get());
    });
}

benchmark_group!(group,
    keygen<KeySize1024>,
    keygen<KeySize2048>,
    keygen<KeySize3072>,
    keygen<KeySize4096>
);

benchmark_main!(group);
