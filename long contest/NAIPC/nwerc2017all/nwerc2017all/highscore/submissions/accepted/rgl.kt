import java.util.*

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)
  val cases = scan.nextInt()
  for (i in 0 until cases) {
    val v: LongArray = LongArray(3, {_ -> scan.nextLong()})
    val pts = scan.nextLong()
    var answer: Long = 0

    v.sort()
    for (spend in 0 until Math.min(5, pts) + 1) {
      val w = v.copyOf()
      for (j in 0 until spend) {
        w[0]++
        w.sort()
      }
      w[2] += pts - spend
      answer = Math.max(answer, w[0]*7 + w[0]*w[0] + w[1]*w[1] + w[2]*w[2])
    }

    System.`out`.format("%d%n", answer)
  }
}
