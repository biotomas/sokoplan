java -jar sokogen.jar $1 > $1.pddl
./downward/fast-downward.py --alias seq-sat-lama-2011 ./SokoGen/domain.pddl $1.pddl
java -jar sokogen.jar $1 sas_plan.1 | tee $1.solution
rm $1.pddl sas_plan.1
