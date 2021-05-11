run:
	./sokoPlan.py level.soko_constraint

plan:
	./sokoPlan.py level.soko_constraint > level.pddl
	./downward/fast-downward.py --alias seq-sat-lama-2011 domain.pddl level.pddl

parse: plan
	./parse.py level.soko_constraint sas_plan.1
