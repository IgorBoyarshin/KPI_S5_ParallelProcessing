module Data where
-- import Data.List

type Vector = [Int]

type Matrix = [[Int]]

-- data Data = Int | Vector | Matrix
--
---------------------------------------------------------------------

createVector :: Int -> Int -> Vector
createVector = replicate

createVectorOnes :: Int -> Vector
createVectorOnes = flip createVector 1

createMatrix :: Int -> Int -> Matrix
createMatrix size filler = replicate size $ replicate size filler

createMatrixOnes :: Int -> Matrix
createMatrixOnes = flip createMatrix 1

addVectors :: Vector -> Vector -> Vector
addVectors = zipWith (+)

addMatrices :: Matrix -> Matrix -> Matrix
addMatrices = zipWith $ zipWith (+)

mulMatrixVector :: Matrix -> Vector -> Vector
mulMatrixVector m v = map (sum . zipWith (*) v) m

mulVectorMatrix :: Vector -> Matrix -> Vector
mulVectorMatrix = flip mulMatrixVector
-- mulVectorMatrix v = map (sum . zipWith (*) v)

mulMatrices :: Matrix -> Matrix -> Matrix
-- mulMatrices m1 m2 = map ((flip mulVectorMatrix) m2) m1
mulMatrices m1 = map $ mulMatrixVector m1

transposeMatrix :: Matrix -> Matrix
transposeMatrix = id

findMin :: Vector -> Int
findMin = minimum

findMax :: Vector -> Int
findMax = maximum


---------------------------------------------------------------------

func1 :: Vector -> Vector -> Vector -> Matrix -> Matrix -> Int
func1 a b c ma me = e1 + e2
    where e1 = findMax $ addVectors b c
          e2 = findMin $ addVectors a $ mulVectorMatrix b $ mulMatrices ma me

func2 :: Matrix -> Matrix -> Matrix -> Matrix
func2 ma mb mz = addMatrices (mulMatrices ma $ mulMatrices ma mz) (transposeMatrix mb)


func3 :: Vector -> Vector -> Matrix -> Matrix -> Matrix -> Vector
func3 p s mo mr ms = addVectors (mulMatrixVector mo p) (mulMatrixVector (mulMatrices mr ms) s)

---------------------------------------------------------------------



