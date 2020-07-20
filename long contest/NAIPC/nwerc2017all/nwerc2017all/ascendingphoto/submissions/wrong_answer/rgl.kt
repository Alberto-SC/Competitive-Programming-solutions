import java.util.*

fun heightmap(h: ArrayList<Int>): TreeMap<Int, Int>{
  var idx = 0
  val res = TreeMap<Int, Int>()
  for (i in h.toSet().sorted()) {
    res.put(i, idx)
    idx++
  }
  return res
}

fun renumber(h: Array<Int>): List<Int> {
  val r = ArrayList<Int>(h.size)
  for (i in h) {
    if (r.size == 0 || i != r[r.size-1]) {
      r.add(i)
    }
  }
  val hm = heightmap(r).withDefault({_ -> 0})
  return r.mapNotNull({i -> hm.get(i)})
}

fun findplaces(h: List<Int>): SortedMap<Int, ArrayList<Int>> {
  val r = TreeMap<Int, ArrayList<Int>>()
  for (i in 0 until h.size) {
    val l = r.get(h[i]) ?: ArrayList<Int>()
    l.add(i)
    r.put(h[i], l)
  }
  return r
}

fun solve(h: List<Int>): Int? {
  val n = h.size
  val dp = Array<Int>(n, {_ -> n + 1})

  val places = findplaces(h)
  for (i in places.keys.reversed()) {
    val iv = (places.get(i) ?: ArrayList<Int>()).toSet()

    if (i + 1 == places.size) {
      for (j in iv) {
        dp[j] = iv.size - 1
      }
    }
    else if (iv.size == 1) {
      for (j in iv) {
        places.get(i+1)?.forEach({k ->
          dp[j] = Math.min(dp[j], dp[k] + if (k != j+1) 1 else 0)
        })
      }
    }
    else {
      (places.get(i+1) ?: emptyList<Int>())
          .sortedBy({k -> dp[k] - if (iv.contains(k-1)) 0 else 1})
          .take(4)
          .forEach({k -> iv.forEach({j ->
        dp[j] = Math.min(dp[j],
            dp[k] +
            iv.size-1 +
            if (k != j+1 && iv.contains(k-1)) 0 else 1)
      })})
    }
  }
  return places.get(0)?.map({i -> dp[i]})?.min()
}

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)

  val n = scan.nextInt()
  val h = renumber(Array<Int>(n, {_ -> scan.nextInt()}))
  System.`out`.println(solve(h))
}
