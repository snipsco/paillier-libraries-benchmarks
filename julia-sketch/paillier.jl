type PrivateDecryptionKey
    l::BigInt
    m::BigInt
    n::BigInt
    n_sq::BigInt
end

type PublicEncryptionKey
    n::BigInt
    n_sq::BigInt
    g::BigInt
end

PublicEncryptionKey(p,q) = PublicEncryptionKey(p*q)
PublicEncryptionKey(n) = PublicEncryptionKey(n,n^2,n+1)

PrivateDecryptionKey(p,q) = PrivateDecryptionKey(p,q,p*q)
function PrivateDecryptionKey(p,q,n)
    l = (p-1)*(q-1)
    m = invmod(l, n)
    PrivateDecryptionKey(l,m,n,n^2)
end


function encrypt(pub::PublicEncryptionKey, m)
    rng = RandomDevice()
    r = rand(rng, 2:pub.n)::BigInt
    rn = powermod(r, pub.n, pub.n_sq)
    gm = mod( (pub.n * m) + 1, pub.n_sq )
    c = mod(gm * rn, pub.n_sq)
end

function decrypt(priv::PrivateDecryptionKey, c)
    x = powermod(c, priv.l, priv.n_sq) - 1
    m = mod(div(x, priv.n) * priv.m, priv.n)
end
