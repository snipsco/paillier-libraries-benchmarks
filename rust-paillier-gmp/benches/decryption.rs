#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

mod constants;
use constants::*;

pub fn decryption<KS, DK, PT>(b: &mut Bencher)
where
    KS: KeySize,
    PT: Plaintext,
    for<'kp> DK: From<&'kp Keypair<BigInteger>>,
    Paillier: Decryption<DK, core::Ciphertext<BigInteger>, core::Plaintext<BigInteger>>,
{
    let keypair = Paillier::keypair_with_modulus_size(KS::get());
    let ek = StandardEncryption::from(&keypair);
    let dk = DK::from(&keypair);
    let m = core::Plaintext(PT::get());
    let c = Paillier::encrypt(&ek, &m);

    b.iter(|| {
        let _ = Paillier::decrypt(&dk, &c);
    });
}

benchmark_group!(standard,
    decryption<KeySize1024, StandardDecryption, PlaintextSmall>,
    decryption<KeySize1024, StandardDecryption, PlaintextLarge>,

    decryption<KeySize2048, StandardDecryption, PlaintextSmall>,
    decryption<KeySize2048, StandardDecryption, PlaintextLarge>,

    decryption<KeySize3072, StandardDecryption, PlaintextSmall>,
    decryption<KeySize3072, StandardDecryption, PlaintextLarge>,

    decryption<KeySize4096, StandardDecryption, PlaintextSmall>,
    decryption<KeySize4096, StandardDecryption, PlaintextLarge>
);

benchmark_group!(crt,
    decryption<KeySize1024, CrtDecryption, PlaintextSmall>,
    decryption<KeySize1024, CrtDecryption, PlaintextLarge>,

    decryption<KeySize2048, CrtDecryption, PlaintextSmall>,
    decryption<KeySize2048, CrtDecryption, PlaintextLarge>,

    decryption<KeySize3072, CrtDecryption, PlaintextSmall>,
    decryption<KeySize3072, CrtDecryption, PlaintextLarge>,

    decryption<KeySize4096, CrtDecryption, PlaintextSmall>,
    decryption<KeySize4096, CrtDecryption, PlaintextLarge>
);

benchmark_main!(standard, crt);
