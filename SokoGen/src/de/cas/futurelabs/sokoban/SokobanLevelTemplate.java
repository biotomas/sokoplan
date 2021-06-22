package de.cas.futurelabs.sokoban;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class SokobanLevelTemplate {
	public SokobanTile[][] tilemap;
	public int walls;
	public int boxes;
	public int minimalPushes;
	public Map<SokobanTile, Integer> tileCount = new HashMap<>();
	public boolean invalid;

	public SokobanLevelTemplate(String path) throws FileNotFoundException {
		File level = new File(path);
		Scanner scanner = new Scanner(level);
		List<SokobanTile[]> rows = new ArrayList<SokobanTile[]>();
		while (scanner.hasNextLine()) {
			String line = scanner.nextLine();
			if (line.startsWith(";")) {
				// comments are ignored
				continue;
			}
			if (line.startsWith("p sokogen")) {
				String[] parts = line.split(" ");
				this.walls = Integer.parseInt(parts[2]);
				this.boxes = Integer.parseInt(parts[3]);
				this.minimalPushes = Integer.parseInt(parts[4]);
				continue;
			}
			SokobanTile[] row = new SokobanTile[line.length()];
			for (int index = 0; index < line.length(); index++) {
				SokobanTile tile = SokobanTile.valueForSymbol(line.charAt(index));
				row[index] = tile;
				tileCount.compute(tile, (k, v) -> v == null ? 1 : v + 1);
			}
			rows.add(row);
		}
		this.tilemap = new SokobanTile[rows.size()][];
		this.tilemap = rows.toArray(this.tilemap);
		scanner.close();
		validateTemplate();
	}

	public void validateTemplate() {
		invalid = false;
		if (countOf(SokobanTile.player, SokobanTile.player_on_goal) > 1) {
			error("Multiple players on the map are not allowed");
		}
		if (boxes > countOf(SokobanTile.possible_box, SokobanTile.possible_player_box, SokobanTile.possible_wall_box)) {
			error("There is not enough options to place the required amount of boxes");
		}
		if (walls > countOf(SokobanTile.possible_wall, SokobanTile.possible_player_wall, SokobanTile.possible_wall_box)) {
			error("There is not enough options to place the required amount of walls");
		}
		if (boxes + countOf(SokobanTile.box) != countOf(SokobanTile.goal, SokobanTile.player_on_goal)) {
			error("Number of boxes does not match the number of goals.");
		}
		if (countOf(SokobanTile.player, SokobanTile.player_on_goal, SokobanTile.possible_player,
				SokobanTile.possible_player_box, SokobanTile.possible_player_wall,
				SokobanTile.possible_player_wall_box) == 0) {
			error("There is no player and no option to place a player");
		}
		
		if (invalid) {
			throw new RuntimeException("Level template is invalid");
		}
	}

	public int countOf(SokobanTile... tiles) {
		int totalCount = 0;
		for (SokobanTile tile : tiles) {
			totalCount += tileCount.getOrDefault(tile, 0);
		}
		return totalCount;
	}

	private void error(String message) {
		System.err.println("ERROR: " + message);
		invalid = true;
	}

	@Override
	public String toString() {
		return "SokobanLevelTemplate [walls=" + walls + ", boxes=" + boxes + ", minimalPushes=" + minimalPushes + "]\n"
				+ printTilemap(tilemap);
	}

	public static String printTilemap(SokobanTile[][] tilemap) {
		StringBuilder builder = new StringBuilder();
		for (SokobanTile[] row : tilemap) {
			for (SokobanTile tile : row) {
				builder.append(tile.symbol);
			}
			builder.append("\n");
		}
		return builder.toString();
	}

}