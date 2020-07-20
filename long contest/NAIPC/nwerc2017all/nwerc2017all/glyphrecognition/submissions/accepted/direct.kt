import java.util.*

fun getArea(p: Pair<Double, Double>, k: Int): Double {
  val ang = (Math.atan2(p.second, p.first) + 2*Math.PI).rem(2*Math.PI / k) - Math.PI / k
  return Math.cos(ang) * Math.cos(ang) * (Math.pow(p.first,2.0) + Math.pow(p.second,2.0))
}

fun getScore(points: Array<Pair<Double, Double>>, k: Int): Double {
  val areas = points.map({p -> getArea(p, k)})
  return (areas.min() ?: 0.0) / (areas.max() ?: 1.0)
}

fun main(args: Array<String>) {
  var scan = Scanner(System.`in`)

  val points = Array<Pair<Double, Double>>(scan.nextInt(), {_ ->
    Pair<Double, Double>(scan.nextDouble(), scan.nextDouble())
  })

  val (best, res) = (3..8).map({k -> Pair<Double, Int>(getScore(points, k), k)}).maxBy({x -> x.first})!!
  System.`out`.format("%d %.10f%n", res, best)
}
