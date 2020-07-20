import java.util.*

data class Formula(val axle: Int, val m: Int, val c: Int)

fun establish(
    x: Int,
    edges: Array<ArrayList<Formula>>,
    formulae: Array<HashSet<Formula>>,
    done: HashSet<Int>) {
  done.add(x)

  for (e in edges[x]) {
    for (a in formulae[x]) {
      formulae[e.axle].add(Formula(e.axle, e.m*a.m, e.m*a.c+e.c))
      if (done.contains(e.axle) == false) {
        establish(e.axle, edges, formulae, done)
      }
    }
  }
}

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)

  val n = scan.nextInt()
  val gears = Array<Int>(n, {_ -> scan.nextInt()})
  val edges = Array<ArrayList<Formula>>(n, {_ -> ArrayList<Formula>()})
  for (i in 0 until scan.nextInt()) {
    val a = scan.nextInt() - 1
    val b = scan.nextInt() - 1
    val w = scan.nextInt()
    edges[a].add(Formula(b, -1, w))
    edges[b].add(Formula(a, -1, w))
  }

  val max_gear = gears.max() ?: 0

  val formulae = Array<HashSet<Formula>>(n, {_ -> HashSet<Formula>()})
  val done = HashSet<Int>()
  formulae[0].add(Formula(0, 1, 0))
  establish(0, edges, formulae, done)

  for (sgn in -1..+1) {
    val biggest = formulae.map({s -> s.toList()}).flatten().filter({f -> f.m == sgn}).maxBy({f -> f.c})
    if (biggest != null) {
      val avail = HashMap<Int, Stack<Int>>()
      for (i in 0 until n) {
        val l = avail.get(gears[i]) ?: Stack<Int>()
        l.push(i+1)
        avail.put(gears[i], l)
      }

      val gear0 = (max_gear - biggest.c) / biggest.m
      val res = Array<Int>(n, init@ {i ->
        val want = formulae[i].first().m * gear0 + formulae[i].first().c
        for (f in formulae[i]) {
          if (want != f.m * gear0 + f.c) {
            return@init 0
          }
        }

        if (avail.get(want)?.isEmpty() ?: false){
          return@init 0
        } else {
          return@init avail.get(want)?.pop() ?: 0
        }
      })

      if ((res.min() ?: 0) > 0) {
        System.`out`.println(res.joinToString(" "))
        return
      }
    }
  }

  System.`out`.println("impossible")
}
