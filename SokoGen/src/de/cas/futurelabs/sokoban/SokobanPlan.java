package de.cas.futurelabs.sokoban;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SokobanPlan {
	
	public enum ActionType {
		place, push, move
	}
	
	public static class Position {
		public final int x;
		public final int y;

		public Position(String string) {
			String[] parts = string.substring(1).split("-");
			x = Integer.parseInt(parts[0]);
			y = Integer.parseInt(parts[1]);
		}

		@Override
		public String toString() {
			return "[" + x + ", " + y + "]";
		}
		
		
	}
	
	public static class SokobanAction {
		public ActionType type;
		public SokobanTile tileToPlace;
		public Position from;
		public Position to;
		public Position pushTo;
		
		public static SokobanAction parseAction(String line) {
			SokobanAction action = new SokobanAction();
			line = line.strip();
			if (line.startsWith("(") && line.endsWith(")")) {
				line = line.substring(1, line.length()-1);
				String[] parts = line.split(" ");
				String actionName = parts[0].toLowerCase();

				switch (actionName) {
				case "place_wall":
					action.type = ActionType.place;
					action.tileToPlace = SokobanTile.wall;
					action.to = new Position(parts[2]);
					return action;
				case "place_box":
					action.type = ActionType.place;
					action.tileToPlace = SokobanTile.box;
					action.to = new Position(parts[2]);
					return action;
				case "place_player_and_transition_to_play":
					action.type = ActionType.place;
					action.tileToPlace = SokobanTile.player;
					action.to = new Position(parts[1]);
					return action;
				}
				if (actionName.startsWith("move")) {
					action.type = ActionType.move;
					action.from = new Position(parts[1]);
					action.to = new Position(parts[2]);
					return action;
				}
				if (actionName.startsWith("push")) {
					action.type = ActionType.push;
					action.from = new Position(parts[1]);
					action.to = new Position(parts[2]);
					action.pushTo = new Position(parts[3]);
					return action;
				}
			}
			return null;
		}
		
		public String toDisplayString() {
			return String.format("%s %s -> %s", this.type, this.from, this.to);
		}

		@Override
		public String toString() {
			return "SokobanAction [type=" + type + ", tileToPlace=" + tileToPlace + ", from=" + from + ", to=" + to
					+ ", pushTo=" + pushTo + "]";
		}
		
	}

	public List<SokobanAction> plan;
	
	public SokobanPlan(String path) throws FileNotFoundException {
		plan = new ArrayList<>();
		File level = new File(path);
		Scanner scanner = new Scanner(level);
		while (scanner.hasNextLine()) {
			SokobanAction action = SokobanAction.parseAction(scanner.nextLine());
			if (action != null) {
				plan.add(action);
			}
		}
		scanner.close();
	}
}
