#[macro_use]
extern crate bencher;
extern crate paillier;

use bencher::Bencher;
use paillier::*;
use paillier::plain::*;

type Scheme = PlainPaillier;

// pub fn bench_1024(b: &mut Bencher)
// {
//     let (ek, dk) = Scheme::keypair(1024);
//
//     let m = Scheme::encode(1056287461);
//
//     let c = Scheme::encrypt(&ek, &m);
//     b.iter(|| {
//         let _ = Scheme::decrypt(&dk, &c);
//     });
// }

pub fn bench_2048(b: &mut Bencher)
{
    let (ek, dk) = Scheme::keypair(2048);

    use paillier::arithimpl::traits::Samplable;
    // let n: BigInteger = str::parse("23601375460155562757123678360900229644381030159964965932095920363097284825175029196457022864038449469086188985762066259059164844287276915193108505099612427967057134520230945630209577834878763915645946525724125804370016991193585261991964913084246563304755455418791629494251095184144084978275430600444710605147457044597210354635288909909182640243950968376955162386281524128586829759108414295175173359174297599533960370415928328418610692822180389889327103292184546896322100484378149887147731744901289563127581082141485046742100147976163228583170704180024449958168221243717383276594270459874555884125566472776234343167371").unwrap();
    // let m = Plaintext(n);
    let m = Scheme::encode(1056287461);



    b.iter(|| {
        let c = Scheme::encrypt(&ek, &m);
        let _ = Scheme::decrypt(&dk, &c);
    });
}

benchmark_group!(group,
    // bench_1024,
    bench_2048
);

benchmark_main!(group);
