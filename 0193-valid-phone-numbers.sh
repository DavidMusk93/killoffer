#!/bin/bash

#set -x

FILE=/tmp/file.txt

cat>$FILE<<eof
987-123-4567
123 456 7890
(123) 456-7890
(001)  345-0000
eof

#filterLine(){
#    N3='[0-9]{3}'
#    N4='[0-9]{4}'
##    echo $* | egrep "^\($N3\) $N3-$N4$|^$N3-$N3-$N4$"
#    echo "$1" | egrep "^\($N3\) $N3-$N4$|^$N3-$N3-$N4$"
#}
#
#while IFS= read -r line;do
#    filterLine "$line"
#done<$FILE
N3='[0-9]{3}'
N4='[0-9]{4}'
#cat $FILE | egrep "^\($N3\) $N3-$N4$|^$N3-$N3-$N4$"
egrep "^\($N3\) $N3-$N4$|^$N3-$N3-$N4$" $FILE