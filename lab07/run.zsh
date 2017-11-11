#!/usr/bin/zsh

stack exec -- ghc -O2 -threaded --make lab7.hs -o lab7
./lab7 +RTS -N3
