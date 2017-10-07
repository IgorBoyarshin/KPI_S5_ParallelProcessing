#!/usr/bin/zsh

gcc -c lab1.adb -gnatl=lab1.lst
gcc -c data.adb -gnatl=data.lst
# gcc -c data.ads -gnatl=data_s.lst

gnatmake lab1 -gnatl=lst.lst
