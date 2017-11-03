#!/usr/bin/zsh

mpiCC -o lab6 lab6.cpp Data.cpp
mpirun -np 4 ./lab6
