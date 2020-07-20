import java.io.*
import java.util.*

fun main(args: Array<String>) {
  val br = BufferedReader(InputStreamReader(System.`in`))
  for (i in 0 until br.readLine().toInt()) {
    System.`out`.println(br.readLine().toLong().toString(3))
  }
}
