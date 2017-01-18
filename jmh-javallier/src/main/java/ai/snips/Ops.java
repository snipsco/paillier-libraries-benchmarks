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

public class Ops {

    static BigInteger small = new BigInteger("42");
    static BigInteger large = new BigInteger("9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729");

    @State(Scope.Benchmark)
    public static class Keys {
        public PaillierPrivateKey key_1024 = PaillierPrivateKey.create(1024);
        public PaillierPrivateKey key_2048 = PaillierPrivateKey.create(2048);
        public PaillierPrivateKey key_3072 = PaillierPrivateKey.create(3072);
        public PaillierPrivateKey key_4096 = PaillierPrivateKey.create(4096);
        public PaillierPublicKey pubkey_1024 = key_1024.getPublicKey();
        public PaillierPublicKey pubkey_2048 = key_2048.getPublicKey();
        public PaillierPublicKey pubkey_3072 = key_3072.getPublicKey();
        public PaillierPublicKey pubkey_4096 = key_4096.getPublicKey();
        public EncryptedNumber cipher_small_1024 = encrypt(pubkey_1024, small);
        public EncryptedNumber cipher_small_2048 = encrypt(pubkey_2048, small);
        public EncryptedNumber cipher_small_3072 = encrypt(pubkey_3072, small);
        public EncryptedNumber cipher_small_4096 = encrypt(pubkey_4096, small);
        public EncryptedNumber cipher_large_1024 = encrypt(pubkey_1024, large);
        public EncryptedNumber cipher_large_2048 = encrypt(pubkey_2048, large);
        public EncryptedNumber cipher_large_3072 = encrypt(pubkey_3072, large);
        public EncryptedNumber cipher_large_4096 = encrypt(pubkey_4096, large);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_1024(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_1024, state.cipher_small_1024, state.cipher_large_1024);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_2048(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_2048, state.cipher_small_2048, state.cipher_large_2048);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_3072(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_3072, state.cipher_small_3072, state.cipher_large_3072);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_4096(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_4096, state.cipher_small_4096, state.cipher_large_4096);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_1024(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_1024, state.cipher_small_1024, state.cipher_large_1024);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_2048(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_2048, state.cipher_small_2048, state.cipher_large_2048);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_3072(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_3072, state.cipher_small_3072, state.cipher_large_3072);
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testAdd_4096(Blackhole blackhole, Keys state) {
        add(blackhole, state.pubkey_4096, state.cipher_small_4096, state.cipher_large_4096);
    }

    private static void add(Blackhole blackhole, PaillierPublicKey key, EncryptedNumber message1, EncryptedNumber message2) {
        PaillierContext paillierContext = key.createSignedContext();
        blackhole.consume(paillierContext.add(message1, message2));
    }

    private static EncryptedNumber encrypt(PaillierPublicKey key, BigInteger message) {
        PaillierContext paillierContext = key.createSignedContext();
        EncryptedNumber cipherText = paillierContext.encrypt(message);
        cipherText.obfuscate();
        return cipherText;
    }
}
