import Control.Monad (when)
import Control.DeepSeq
-- import Control.Parallel.Strategies
import Control.Concurrent.Async

import Data


thread1_func :: Int -> Int -> IO()
thread1_func n outputThreshold = do
    putStrLn ":> Starting Thread 1..."

    -- Initialization
    let a = createVectorOnes n
    let b = createVectorOnes n
    let c = createVectorOnes n
    let ma = createMatrixOnes n
    let me = createMatrixOnes n

    -- Computation
    let d = func1 a b c ma me
    deepseq d $ return ()

    -- Output
    when (n < outputThreshold) $ do
        putStrLn ""
        putStrLn $ "Result of func1: d = " ++ show d
        putStrLn ""

    putStrLn ":> Finished Thread 1"


thread2_func :: Int -> Int -> IO()
thread2_func n outputThreshold = do
    putStrLn ":> Starting Thread 2..."

    -- Initialization
    let ma = createMatrixOnes n
    let mb = createMatrixOnes n
    let mz = createMatrixOnes n

    -- Computation
    let mk = func2 ma mb mz
    deepseq mk $ return ()

    -- Output
    when (n < outputThreshold) $ do
        putStrLn ""
        putStrLn $ "Result of func2: MK = " ++ show mk
        putStrLn ""

    putStrLn ":> Finished Thread 2"


thread3_func :: Int -> Int -> IO()
thread3_func n outputThreshold = do
    putStrLn ":> Starting Thread 3..."

    -- Initialization
    let p = createVectorOnes n
    let s = createVectorOnes n
    let mo = createMatrixOnes n
    let mr = createMatrixOnes n
    let ms = createMatrixOnes n

    -- Computation
    let t = func3 p s mo mr ms
    deepseq t $ return ()

    -- Output
    when (n < outputThreshold) $ do
        putStrLn ""
        putStrLn $ "Result of func3: T = " ++ show t
        putStrLn ""

    putStrLn ":> Finished Thread 3"


main :: IO ()
main = do
    putStrLn "-----------------------------------------------------"
    putStrLn "Input N: "
    n <- readLn :: IO Int
    let outputThreshold = 7

    t1 <- async $ thread1_func n outputThreshold
    t2 <- async $ thread2_func n outputThreshold
    t3 <- async $ thread3_func n outputThreshold
    wait t1
    wait t2
    wait t3
