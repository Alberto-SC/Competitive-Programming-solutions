import java.util.*

val p = Array<Array<Double>>(14, {_ -> Array<Double>(4096, {_ -> 0.0})})

fun rec(l:Int, r:Int, v:Int, s:Array<Double>) {
	if (l+1 == r) {
		p[v][l] = 1.0
		return
	}

	var m = (l+r) / 2
	rec(l, m, v+1, s)
	rec(m, r, v+1, s)

	for (i in l until m) {
		for (j in m until r) {
			if (s[i] > 0 || s[j] > 0) {
				var chance = p[v+1][i] * p[v+1][j] / (s[i] + s[j])
				p[v][i] += s[i] * chance
				p[v][j] += s[j] * chance
			}
		}
	}
}

fun main(args: Array<String>) {
    var scan = Scanner(System.`in`)

    val n = scan.nextInt()
    var n2 = 1
    while (n2 < n) { n2 *= 2 }

    val s = Array<Double>(n2, {i -> if (i < n) scan.nextDouble() else 0.0})
    val me = s[0].also { s[0] = 0.0 }
    s.sortDescending()

    for (i in 0 until n2-n) {
        s[n2-1-i*2] = s[n-1-i].also { s[n-1-i] = s[n2-1-i*2] }
    }
    s[n2-1] = me

    rec(0, n2, 0, s)
    System.`out`.format("%.8f%n", p[0][n2-1])
}
