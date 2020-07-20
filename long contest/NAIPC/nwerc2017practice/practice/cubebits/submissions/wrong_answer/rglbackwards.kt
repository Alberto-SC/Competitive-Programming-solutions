import java.util.*

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)
  val cases = scan.nextInt()

  for (case in 0 until cases) {
    var n = scan.nextLong()
    var i = 0
    val s = StringBuilder()
    while (i == 0 || n > 0) {
      s.append("%d".format(n % 3))
      n /= 3
      i += 1
    }

    System.`out`.println(s.toString())
  }
}
