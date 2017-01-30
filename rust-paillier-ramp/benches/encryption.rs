#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

mod constants;
use constants::*;

pub fn encryption<KS, EK, PT>(b: &mut Bencher)
where
    KS: KeySize,
    PT: Plaintext,
    for<'kp> EK: From<&'kp Keypair<BigInteger>>,
    Paillier: Encryption<EK, core::Plaintext<BigInteger>, core::Ciphertext<BigInteger>>,
{
    let keypair = Paillier::keypair_with_modulus_size(KS::get());
    let ek = EK::from(&keypair);
    let m = core::Plaintext(PT::get());

    b.iter(|| {
        let _ = Paillier::encrypt(&ek, &m);
    });
}

benchmark_group!(generic,
    encryption<KeySize1024, GenericEncryption, PlaintextSmall>,
    encryption<KeySize1024, GenericEncryption, PlaintextLarge>,

    encryption<KeySize2048, GenericEncryption, PlaintextSmall>,
    encryption<KeySize2048, GenericEncryption, PlaintextLarge>,

    encryption<KeySize3072, GenericEncryption, PlaintextSmall>,
    encryption<KeySize3072, GenericEncryption, PlaintextLarge>,

    encryption<KeySize4096, GenericEncryption, PlaintextSmall>,
    encryption<KeySize4096, GenericEncryption, PlaintextLarge>
);

benchmark_group!(standard,
    encryption<KeySize1024, StandardEncryption, PlaintextSmall>,
    encryption<KeySize1024, StandardEncryption, PlaintextLarge>,

    encryption<KeySize2048, StandardEncryption, PlaintextSmall>,
    encryption<KeySize2048, StandardEncryption, PlaintextLarge>,

    encryption<KeySize3072, StandardEncryption, PlaintextSmall>,
    encryption<KeySize3072, StandardEncryption, PlaintextLarge>,

    encryption<KeySize4096, StandardEncryption, PlaintextSmall>,
    encryption<KeySize4096, StandardEncryption, PlaintextLarge>
);

benchmark_main!(standard, generic);
