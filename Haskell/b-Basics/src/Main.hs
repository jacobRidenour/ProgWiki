module Main (main) where

-- import Data.Bits (complement, (.&.), (.|.), xor)

main :: IO ()
main = do
    -- Numerical operations
    let addResult = 5 + 3 -- 
    let subtractResult = 5 - 3
    let multiplyResult = 5 * 3
    let divideResult = 5 / 3
    let intDivideResult = 5 `div` 3 -- floor division
    let modulusResult = 5 `mod` 3

    putStrLn $ "Addition: " ++ show addResult
    putStrLn $ "Subtraction: " ++ show subtractResult
    putStrLn $ "Multiplication: " ++ show multiplyResult
    putStrLn $ "Division (floating): " ++ show divideResult
    putStrLn $ "Division (integer): " ++ show intDivideResult
    putStrLn $ "Modulus: " ++ show modulusResult

    -- TODO fix
    -- Logical operations
    -- let andResult = True && False
    -- let orResult = True || False
    -- let notResult = not True

    -- putStrLn $ "Logical AND: " ++ show andResult
    -- putStrLn $ "Logical OR: " ++ show orResult
    -- putStrLn $ "Logical NOT: " ++ show notResult

    -- Bitwise operations
    -- let bwAndResult = 5 .&. 3
    -- let bwOrResult = 5 .|. 3
    -- let bwXorResult = 5 `xor` 3
    -- let bwNotResult = complement 2

    -- putStrLn $ "Bitwise AND: " ++ show bwAndResult
    -- putStrLn $ "Bitwise OR: " ++ show bwOrResult
    -- putStrLn $ "Bitwise XOR: " ++ show bwXorResult
    -- putStrLn $ "Bitwise NOT: " ++ show bwNotResult
