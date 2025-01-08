module Main (main) where

main :: IO ()
main = do
  putStrLn "hello world"

-- Create project (folder must not exist)
-- stack new aHelloWorld simple 
-- Run program:
-- stack exec aHelloWorld