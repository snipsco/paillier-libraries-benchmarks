# Javalier / JMH

This is the JMB bench for the javaillier library.

## Prerequisites

Java and Maven must be installed.

## Build it

`mvn install`

## Run it

`java -jar target/benchmarks.jar`

Due to JVM relatively high performance variablity, this takes a while. You can
tweak various running parameters or select different test from the command line.

For instance:

`java -jar target/benchmarks.jar Add -r 200ms -w 200ms -f 3`

More options:

`java -jar target/benchmarks.jar -h`
