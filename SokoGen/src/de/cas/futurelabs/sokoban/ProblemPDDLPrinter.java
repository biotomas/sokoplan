package de.cas.futurelabs.sokoban;

import java.io.PrintStream;

public class ProblemPDDLPrinter {
	
	private final PrintStream out;
	
	public ProblemPDDLPrinter(PrintStream out) {
		this.out = out;
	}


	public void printProblemPddl(SokobanLevelTemplate template) {
		out.println("(define (problem sokoban-1)");
		out.println(" (:domain sokoban)");
		out.println(" (:requirements :strips :typing)");
		out.println(" (:objects");

		printCounts(template);
		printTiles(template);
		printWalls(template);
		printBoxes(template);

		out.println(" )");
		out.println(" (:init");

		// rigid
		printCountNext(template);
		printLeftAndAboveAndItems(template);

		// fluent
		out.println("   (making_level)");
		out.println("   (count_push " + getCountAtom(0) + ")");

		out.println(" )");
		out.println(" (:goal (and");

		printSokobanGoals(template);
		printPlacementGoals(template);
		out.println("   (count_push " + getCountAtom(template.minimalPushes) + ")");

		out.println(" ))");
		out.println(")");
	}

	private void printPlacementGoals(SokobanLevelTemplate template) {
		for (int i = 1; i <= template.boxes; i++) {
			out.println("   (box_placed box" + i + ")");
		}
		for (int i = 1; i <= template.walls; i++) {
			out.println("   (wall_placed wall" + i + ")");
		}
	}


	private void printSokobanGoals(SokobanLevelTemplate template) {
		for (int rowId = 1; rowId < template.tilemap.length; rowId++) {
			SokobanTile[] row = template.tilemap[rowId];
			for (int columnId = 1; columnId < row.length; columnId++) {
				if (template.tilemap[rowId][columnId] == SokobanTile.goal || 
						template.tilemap[rowId][columnId] == SokobanTile.box_on_goal ||
						template.tilemap[rowId][columnId] == SokobanTile.player_on_goal) {
					out.println("   (box_at " + getTileAtom(rowId, columnId) + ")");
				}
			}
		}
	}

	private void printLeftAndAboveAndItems(SokobanLevelTemplate template) {
		for (int rowId = 1; rowId < template.tilemap.length; rowId++) {
			SokobanTile[] row = template.tilemap[rowId];
			for (int columnId = 1; columnId < row.length; columnId++) {
				if (template.tilemap[rowId][columnId] == SokobanTile.wall) {
					//out.println("   (wall_at " + getTileAtom(rowId, columnId) + ")");
					continue;
				}
				if (template.tilemap[rowId - 1][columnId] != SokobanTile.wall) {
					out.println("   (above " + getTileAtom(rowId - 1, columnId) + " "
							+ getTileAtom(rowId, columnId) + ")");
				}
				if (template.tilemap[rowId][columnId - 1] != SokobanTile.wall) {
					out.println("   (left " + getTileAtom(rowId, columnId - 1) + " "
							+ getTileAtom(rowId, columnId) + ")");
				}
				switch (template.tilemap[rowId][columnId]) {
				case box:
					out.println("   (box_at " + getTileAtom(rowId, columnId) + ")");
					break;
				case box_on_goal:
					out.println("   (box_at " + getTileAtom(rowId, columnId) + ")");
					break;
				case empty:
					// ignore
					break;
				case goal:
					// ignore
					break;
				case player:
					out.println("   (player_at " + getTileAtom(rowId, columnId) + ")");
					break;
				case player_on_goal:
					out.println("   (player_at " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_box:
					out.println("   (opt_box " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_player:
					out.println("   (opt_player " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_player_box:
					out.println("   (opt_player " + getTileAtom(rowId, columnId) + ")");
					out.println("   (opt_box " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_player_wall:
					out.println("   (opt_wall " + getTileAtom(rowId, columnId) + ")");
					out.println("   (opt_player " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_player_wall_box:
					out.println("   (opt_wall " + getTileAtom(rowId, columnId) + ")");
					out.println("   (opt_player " + getTileAtom(rowId, columnId) + ")");
					out.println("   (opt_box " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_wall:
					out.println("   (opt_wall " + getTileAtom(rowId, columnId) + ")");
					break;
				case possible_wall_box:
					out.println("   (opt_wall " + getTileAtom(rowId, columnId) + ")");
					out.println("   (opt_box " + getTileAtom(rowId, columnId) + ")");
					break;
				case wall:
					// already taken care of above
					break;
				default:
					break;

				}
			}
		}
	}

	private void printCountNext(SokobanLevelTemplate template) {
		for (int i = 0; i < template.minimalPushes; i++) {
			out.println("   (next_count " + getCountAtom(i) + " " + getCountAtom(i + 1) + ")");
		}
		out.println("   (next_count " + getCountAtom(template.minimalPushes) + " "
				+ getCountAtom(template.minimalPushes) + ")");
	}

	private void printTiles(SokobanLevelTemplate template) {
		out.print("   ");
		for (int rowId = 0; rowId < template.tilemap.length; rowId++) {
			SokobanTile[] row = template.tilemap[rowId];
			for (int columnId = 0; columnId < row.length; columnId++) {
				if (template.tilemap[rowId][columnId] != SokobanTile.wall) {
					out.print(getTileAtom(rowId, columnId) + " ");
				}
			}
		}
		out.println("- tile");
	}

	private String getTileAtom(int rowId, int columnId) {
		return String.format("s%d-%d", rowId, columnId);
	}

	private void printCounts(SokobanLevelTemplate template) {
		out.print("   ");
		for (int i = 0; i <= template.minimalPushes; i++) {
			out.print(getCountAtom(i) + " ");
		}
		out.println("- count");
	}

	private void printWalls(SokobanLevelTemplate template) {
		if (template.walls < 1) {
			return;
		}
		out.print("   ");
		for (int i = 1; i <= template.walls; i++) {
			out.print("wall" + i + " ");
		}
		out.println("- wall");
	}

	private void printBoxes(SokobanLevelTemplate template) {
		if (template.boxes < 1) {
			return;
		}
		out.print("   ");
		for (int i = 1; i <= template.boxes; i++) {
			out.print("box" + i + " ");
		}
		out.println("- box");
	}

	private String getCountAtom(int i) {
		return "c" + i;
	}

}
