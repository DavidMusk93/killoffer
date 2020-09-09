#!/bin/bash

#MEMO=/tmp/build.memo
#
#case $1 in
#0 | get-memo)
#  echo -n $MEMO
#  ;;
#1 | run)
#  [ -f $MEMO ] && bash $MEMO
#  ;;
#esac
#
#exit 0

sun::run(){
  g++ -std=c++17 $1 -I.. && ./a.out
}
