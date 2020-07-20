import java.util.*

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)
  val cases = scan.nextInt()

  for (case in 0 until cases) {
    var n = scan.nextLong()
    var i = 0
    val s = StringBuilder()
    while (i == 0 || n > 0) {
      val l = (n % 3).toInt()
      s.append(if (l == 0) '0' else if (l == 1) '1' else '2')
      n /= 3
      i += 1
    }

    System.`out`.println(s.toString().reversed())
  }
}
