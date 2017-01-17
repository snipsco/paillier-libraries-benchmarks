#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;

pub fn encrypt_decrypt<KS>(b: &mut Bencher)
where
    KS: KeySize
{
    let (ek, dk) = Paillier::keypair_with_modulus_size(KS::get());

    // let n: BigInteger = str::parse("23601375460155562757123678360900229644381030159964965932095920363097284825175029196457022864038449469086188985762066259059164844287276915193108505099612427967057134520230945630209577834878763915645946525724125804370016991193585261991964913084246563304755455418791629494251095184144084978275430600444710605147457044597210354635288909909182640243950968376955162386281524128586829759108414295175173359174297599533960370415928328418610692822180389889327103292184546896322100484378149887147731744901289563127581082141485046742100147976163228583170704180024449958168221243717383276594270459874555884125566472776234343167371").unwrap();
    // let m = Plaintext(n);
    let m = core::Plaintext::from(1056287461);

    b.iter(|| {
        let c = Paillier::encrypt(&ek, &m);
        let _ = Paillier::decrypt(&dk, &c);
    });
}

pub trait KeySize { fn get() -> usize; }
struct KeySize1024; impl KeySize for KeySize1024 { fn get() -> usize { 1024 } }
struct KeySize2048; impl KeySize for KeySize2048 { fn get() -> usize { 2048 } }
struct KeySize3072; impl KeySize for KeySize3072 { fn get() -> usize { 3072 } }
struct KeySize4096; impl KeySize for KeySize4096 { fn get() -> usize { 4096 } }

benchmark_group!(group,
    encrypt_decrypt<KeySize1024>,
    encrypt_decrypt<KeySize2048>,
    encrypt_decrypt<KeySize3072>,
    encrypt_decrypt<KeySize4096>
);

benchmark_main!(group);
