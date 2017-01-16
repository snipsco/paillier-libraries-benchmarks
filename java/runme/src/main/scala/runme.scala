
package bench

import com.n1analytics.paillier._

object runme {
  /*
  def synchronized b(m:Integer, p:Integer) {}
    val c = paillierContext.encrypt(m)
    keypair.decrypt(c)
  }
  */

  def main(args: Array[String]): Unit = {

    val keypair = PaillierPrivateKey.create(2048)
    var publicKey = keypair.getPublicKey
    val paillierContext = publicKey.createSignedContext

    val m = new java.math.BigInteger("25099612427967057134520230945630209577834878763915645946525724125804370016991193585261991964913084246563304755455418791629494251095184144084978275430600444710605147457044597210354635288909909182640243950968376955162386281524128586829759108414295175173359174297599533960370415928328418610692822180389889327103292184546896322100484378149887147731744901289563127581082141485046742100147976163228583170704180024449958168221243717383276594270459874555884125566472776234343167371")

    val start = java.lang.System.currentTimeMillis()
    for (i <- 1 to 100) {
      val c = paillierContext.encrypt(m)
      c.obfuscate()
      val _ = keypair.decrypt(c)
    }
    val stop = java.lang.System.currentTimeMillis()
    val diff = stop - start

    println(diff)
    println(diff / 100f)

  }
}
