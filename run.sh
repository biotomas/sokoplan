java -jar sokogen.jar $1 > $1.pddl
#./downward/fast-downward.py --portfolio-single-plan --overall-time-limit 60 --alias seq-sat-fdss-2018 ./SokoGen/domain.pddl $1.pddl #> $1.solution
./downward/fast-downward.py --overall-time-limit 60 --alias seq-sat-lama-2011 ./SokoGen/domain.pddl $1.pddl > $1.solution
java -jar sokogen.jar $1 sas_plan.1 >> $1.solution
rm $1.pddl sas_plan.*
