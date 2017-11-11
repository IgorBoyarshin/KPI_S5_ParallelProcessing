#!/usr/bin/zsh

mpiCC -o lab6 lab6.cpp Data.cpp
mpirun -np 3 ./lab6
