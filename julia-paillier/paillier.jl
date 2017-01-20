type PrivateEncryptionKey
    l::BigInt
    m::BigInt
end

type PublicEncryptionKey
    n::BigInt
    n_sq::BigInt
    g::BigInt
end

PublicEncryptionKey(n) = PublicEncryptionKey(n,n^2,n+1)
PublicEncryptionKey(p,q) = PublicEncryptionKey(p*q)

function PrivateEncryptionKey(p,q,n)
    l = (p-1)*(q-1)
    m = invmod(l, n)
    PrivateEncryptionKey(l,m)
end

function encrypt(pub::PublicEncryptionKey, m)
    rng = RandomDevice()
    r = rand(rng, 2:pub.n)::BigInt
    rn = powermod(r, pub.n, pub.n_sq)
    gm = mod( (pub.n * m) + 1, pub.n_sq )
    c = mod(gm * rn, pub.n_sq)
end

function decrypt(priv, pub, cipher)
    x = powermod(cipher, priv.l, pub.n_sq) - 1
    plain = mod(div(x, pub.n) * priv.m, pub.n)
end