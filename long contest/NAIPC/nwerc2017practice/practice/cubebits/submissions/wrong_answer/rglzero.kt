import java.util.*

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)
  val cases = scan.nextInt()

  for (case in 0 until cases) {
    var n = scan.nextLong()
    val s = StringBuilder()
    while (n > 0) {
      s.append("%d".format(n % 3))
      n /= 3
    }

    System.`out`.println(s.toString().reversed())
  }
}
