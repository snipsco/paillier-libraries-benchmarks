package ai.snips;

import java.util.concurrent.TimeUnit;

import org.openjdk.jmh.infra.Blackhole;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Mode;

import com.n1analytics.paillier.*;

public class Keygen {

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testKeyGen_1024(Blackhole blackhole) {
        blackhole.consume(PaillierPrivateKey.create(1024));
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testKeyGen_2048(Blackhole blackhole) {
        blackhole.consume(PaillierPrivateKey.create(2048));
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testKeyGen_3072(Blackhole blackhole) {
        blackhole.consume(PaillierPrivateKey.create(3072));
    }

    @Benchmark()
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void testKeyGen_4096(Blackhole blackhole) {
        blackhole.consume(PaillierPrivateKey.create(4096));
    }
}
