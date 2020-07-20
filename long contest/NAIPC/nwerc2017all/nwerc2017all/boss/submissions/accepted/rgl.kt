import java.util.*

fun main(args: Array<String>) {
    var scan = Scanner(System.`in`)
    val n = scan.nextInt()
    System.`out`.format("%d%n", Math.max(n-2, 1))
}
