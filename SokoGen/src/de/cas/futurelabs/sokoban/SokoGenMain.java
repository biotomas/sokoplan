package de.cas.futurelabs.sokoban;

import java.io.FileNotFoundException;

import de.cas.futurelabs.sokoban.SokobanPlan.ActionType;
import de.cas.futurelabs.sokoban.SokobanPlan.SokobanAction;

public class SokoGenMain {

	public static void main(String[] args) throws FileNotFoundException {
		if (args.length == 0) {
			System.out.println("USAGE: java -jar sokogen.jar <level-template.txt> [<plan.txt>] [-debug]");
			return;
		}
		if (args.length == 1) {
			SokobanLevelTemplate template = new SokobanLevelTemplate(args[0]);
			ProblemPDDLPrinter printer = new ProblemPDDLPrinter(System.out);
			printer.printProblemPddl(template);
			return;
		}
		boolean debug = false;
		if (args.length == 3) {
			debug = true;
		}

		SokobanLevelTemplate template = new SokobanLevelTemplate(args[0]);
		SokobanLevel level = new SokobanLevel(template);
		SokobanPlan plan = new SokobanPlan(args[1]);
		boolean inSolveMode = false;

		for (SokobanAction action : plan.plan) {
			if (debug) {
				System.out.println(level);
				System.out.println(action);
			}
			if (!inSolveMode && action.type != ActionType.place) {
				System.out.println(";The generated level:");
				System.out.println(level);
				System.out.println("The Solution:");
				inSolveMode = true;
			}
			if (inSolveMode) {
			System.out.println(action.toDisplayString());
			}
			level.applyAction(action);
		}
		System.out.println(";Solution verified: " + level.isInSolvedState());
	}

}
