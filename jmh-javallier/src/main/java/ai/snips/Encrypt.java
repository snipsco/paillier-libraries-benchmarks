package ai.snips;

import java.math.BigInteger;

import java.util.concurrent.TimeUnit;

import org.openjdk.jmh.infra.Blackhole;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;

import com.n1analytics.paillier.*;

public class Encrypt {

    static BigInteger small = new BigInteger("42");
    static BigInteger large = new BigInteger("9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729");

    @State(Scope.Benchmark)
    public static class Keys {
        public PaillierPrivateKey key_1024 = PaillierPrivateKey.create(1024);
        public PaillierPublicKey pubkey_1024 = key_1024.getPublicKey();
        public PaillierPrivateKey key_2048 = PaillierPrivateKey.create(2048);
        public PaillierPublicKey pubkey_2048 = key_2048.getPublicKey();
        public PaillierPrivateKey key_3072 = PaillierPrivateKey.create(3072);
        public PaillierPublicKey pubkey_3072 = key_3072.getPublicKey();
        public PaillierPrivateKey key_4096 = PaillierPrivateKey.create(4096);
        public PaillierPublicKey pubkey_4096 = key_4096.getPublicKey();
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_small_1024(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_1024, small);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_small_2048(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_2048, small);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_small_3072(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_3072, small);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_small_4096(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_4096, small);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_large_1024(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_1024, large);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_large_2048(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_2048, large);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_large_3072(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_3072, large);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testEncrypt_large_4096(Blackhole blackhole, Keys state) {
        encrypt(blackhole, state.pubkey_4096, large);
    }

    private void encrypt(Blackhole blackhole, PaillierPublicKey key, BigInteger rawMessage) {
        PaillierContext paillierContext = key.createSignedContext();
        BigInteger message = rawMessage.remainder(key.getModulus());
        EncryptedNumber cipherText = paillierContext.encrypt(message);
        cipherText.obfuscate();
        blackhole.consume(cipherText);
    }
}
