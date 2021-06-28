#!/bin/bash

function contains {
   for f in $2
   do
	if [ "$f" == "$1" ]
	then
	    printf "."
	    return
	fi
   done
   printf " "
}

mkdir benchmark-templates

for input in meta-templates/*.txt
do
for psize in 1 2 3 4 5 6
do
for version in 1 2 3 4 5
do
outname=benchmark-templates/`basename $input`.$psize.$version.txt
echo "p sokogen $psize $psize $psize" >> $outname
goals=`tr -cd '.' < "$input" | wc -c`
selectedGoals=`seq 1 $goals | shuf | head -n $psize | tr '\n' ' '`
#echo $selectedGoals
currentGoal=1
cat $input | while IFS= read -rn1 a
do 
    c="${a:-$'\n'}"
    #printf %s "$c"
    if [ "$c" == "." ]
    then
	#echo $currentGoal $selectedGoals
	contains "$currentGoal" "$selectedGoals" >> $outname
        currentGoal=$((currentGoal+1))
    elif [ "$c" == " " ]
    then
	printf %s "0" >> $outname
    elif [ "$c" == "-" ]
    then
	printf %s " " >> $outname
    else
	printf %s "$c" >> $outname
    fi
    #echo $currentGoal
    #printf %s "${a:-$'\n'}"; 
done
done
done
done