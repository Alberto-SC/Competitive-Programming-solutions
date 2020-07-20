{-# LANGUAGE NoMonomorphismRestriction, FlexibleContexts, TypeFamilies #-}
import Control.Arrow
import Data.Fixed
import Data.List.Split
import Diagrams.Prelude
import Diagrams.Backend.SVG.CmdLine
import System.FilePath
import System.IO

polygonRadius :: Int -> P2 Double -> Double
polygonRadius n p = r * cos (alpha - sector/2) / cos (sector/2)
    where (x,y)   = unp2 p
          sector  = 2*pi / fromIntegral n
          r = sqrt (x^2 + y^2)
          alpha = atan2 y x `mod'` sector

letter :: Double -> Int -> Diagram B
letter r n = polygon (with & polyType .~ PolyRegular n r & polyOrient .~ NoOrient)

alphabet :: Diagram B
alphabet = mconcat [ letter 1 (3 + round (2*y+x)) # translate (3 *^ (x ^& (-y))) # lc tomato
                   | x <- [0..1]
                   , y <- [0..2]
                   ]

polygons :: Int -> [P2 Double] -> Diagram B
polygons n ps = letter rmin n # fc white <> letter rmax n # fc tomato
    where (rmin,rmax) = (minimum &&& maximum) $ map (polygonRadius n) ps

axes :: Double -> Diagram B
axes xmax = axis <> axis # rotate (90 @@ deg)
    where axis = arrowBetween' (with & headLength .~ small)  (p2 (-xmax,0)) (p2 (xmax,0)) # lw thin

illustrate :: FilePath -> IO (Diagram B)
illustrate path = do
    coords <- map (map read . words) . tail . lines <$> readFile path
    k <- read . head . words <$> readFile (replaceExtension path ".ans")
    
    let xmax    = maximum $ map abs $ concat coords
        pairs   = [(-xmax,-xmax),(xmax,xmax)] ++ map (\[x,y] -> (x,y)) coords
        points  = map p2 pairs # scaleUToX 500 # drop 2
        nodes   = atPoints points (repeat (circle 10 # fc red))
    
    return $ (nodes {-<> axes 330-} <> polygons k points) # frame 50

main :: IO ()
main = mainWith illustrate
