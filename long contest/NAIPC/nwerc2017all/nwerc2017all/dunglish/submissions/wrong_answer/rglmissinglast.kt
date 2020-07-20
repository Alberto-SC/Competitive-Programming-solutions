import java.util.Scanner;

fun f(map: Map<String,List<String>>, words: List<String>): Long {
  var res: Long = 1
  for (i in words) {
    res *= map.get(i)!!.size
  }
  return res
}

fun main(args: Array<String>) {
  val possibleGood = HashMap<String, MutableList<String>>()
  val possibleAll = HashMap<String, MutableList<String>>()

  val scan = Scanner(System.`in`)
  val n = scan.nextInt()

  val words = ArrayList<String>(n)
  for (i in 0 until n) {
    words.add(scan.next());
    possibleGood.put(words.get(i), ArrayList<String>());
    possibleAll.put(words.get(i), ArrayList<String>());
  }

  val m = scan.nextInt()
  for (i in 1 /* oh no! :( */ until m) {
    val a = scan.next()
    val b = scan.next()
    val c = scan.next()
    possibleAll.get(a)?.add(b);
    if (c.startsWith("c")) {
      possibleGood.get(a)?.add(b)
    }
  }

  val all = f(possibleAll, words)
  val good = f(possibleGood, words)

  if (all == 1L) {
    val sb = StringBuilder()
    for (i in words) {
      if (sb.length > 0) {
        sb.append(" ")
      }
      sb.append(possibleAll.get(i)!!.get(0))
    }
    System.`out`.println(sb.toString())
    System.`out`.println(if (all == good) "correct" else "incorrect");
  } else {
    System.`out`.println("" + (good) + " correct");
    System.`out`.println("" + (all-good) + " incorrect");
  }
}
