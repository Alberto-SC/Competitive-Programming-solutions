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
polygons 0 _  = mempty
polygons n ps = letter rmin n # fc white <> letter rmax n # fc tomato
    where (rmin,rmax) = (minimum &&& maximum) $ map (polygonRadius n) ps

axes :: Double -> Diagram B
axes xmax = axis <> axis # rotate (90 @@ deg)
    where axis = arrowBetween' (with & headLength .~ global 30 & arrowHead .~ spike)  (p2 (-xmax,0)) (p2 (xmax,0))

illustrate :: FilePath -> Int -> IO (Diagram B)
illustrate path k = do
    coords <- map (map read . words) . tail . lines <$> readFile path
    
    let w       = if k < 2 then 500 else 350
        xmax    = maximum $ map abs $ concat coords
        pairs   = [(-xmax,-xmax),(xmax,xmax)] ++ map (\[x,y] -> (x,y)) coords
        points  = map p2 pairs # scaleUToX w # drop 2
        nodes   = atPoints points (repeat (circle 10 # fc red)) <> axes (0.7*w)
    
    let diagrams = [ alphabet # scaleUToX 250
                   , nodes 
                   , nodes <> polygons 3 points
                   , nodes <> polygons 6 points
                   ]

    return $ (diagrams !! k) # lwG 5 # frame 50

main :: IO ()
main = mainWith illustrate
