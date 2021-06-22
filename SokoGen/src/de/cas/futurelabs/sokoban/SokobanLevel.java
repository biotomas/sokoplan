package de.cas.futurelabs.sokoban;

import java.util.Arrays;

import de.cas.futurelabs.sokoban.SokobanPlan.Position;
import de.cas.futurelabs.sokoban.SokobanPlan.SokobanAction;

public class SokobanLevel {

	private SokobanTile[][] tilemap;

	private SokobanLevel() {
	}

	public SokobanLevel(SokobanLevelTemplate template) {
		tilemap = new SokobanTile[template.tilemap.length][];
		for (int i = 0; i < template.tilemap.length; i++) {
			tilemap[i] = Arrays.copyOf(template.tilemap[i], template.tilemap[i].length);
			for (int j = 0; j < tilemap[i].length; j++) {
				if (tilemap[i][j].isTemplateTile()) {
					tilemap[i][j] = SokobanTile.empty;
				}
			}
		}
	}
	
	public boolean isInSolvedState() {
		for (SokobanTile[] row : tilemap) {
			for (SokobanTile tile : row) {
				if (tile == SokobanTile.box) {
					return false;
				}
			}
		}
		return true;
	}

	public void applyAction(SokobanAction action) {
		switch (action.type) {
		case move:
			checkIs(action, action.from, SokobanTile.player, SokobanTile.player_on_goal);
			checkIs(action, action.to, SokobanTile.empty, SokobanTile.goal);
			if (get(action.from) == SokobanTile.player) {
				set(action.from, SokobanTile.empty);
			} else {
				set(action.from, SokobanTile.goal);
			}
			if (get(action.to) == SokobanTile.empty) {
				set(action.to, SokobanTile.player);
			} else {
				set(action.to, SokobanTile.player_on_goal);
			}
			break;
		case place:
			checkIs(action, action.to, SokobanTile.empty);
			set(action.to, action.tileToPlace);
			break;
		case push:
			checkIs(action, action.from, SokobanTile.player, SokobanTile.player_on_goal);
			checkIs(action, action.to, SokobanTile.box, SokobanTile.box_on_goal);
			checkIs(action, action.pushTo, SokobanTile.empty, SokobanTile.goal);
			if (get(action.from) == SokobanTile.player) {
				set(action.from, SokobanTile.empty);
			} else {
				set(action.from, SokobanTile.goal);
			}
			if (get(action.to) == SokobanTile.box) {
				set(action.to, SokobanTile.player);
			} else {
				set(action.to, SokobanTile.player_on_goal);
			}
			if (get(action.pushTo) == SokobanTile.empty) {
				set(action.pushTo, SokobanTile.box);
			} else {
				set(action.pushTo, SokobanTile.box_on_goal);
			}
			break;
		default:
			break;
		}
	}

	private void set(Position position, SokobanTile tile) {
		tilemap[position.x][position.y] = tile;
	}

	private SokobanTile get(Position position) {
		return tilemap[position.x][position.y];
	}

	private void checkIs(SokobanAction action, Position position, SokobanTile... tiles) {
		SokobanTile tile = get(position);
		for (SokobanTile t : tiles) {
			if (tile == t) {
				return;
			}
		}
		throw new RuntimeException(
				"Action is not applicable at the current state: " + action.toString() + " state: " + this.toString());
	}

	public SokobanLevel clone() {
		SokobanLevel level = new SokobanLevel();
		level.tilemap = new SokobanTile[tilemap.length][];
		for (int i = 0; i < tilemap.length; i++) {
			level.tilemap[i] = Arrays.copyOf(tilemap[i], tilemap[i].length);
		}
		return level;
	}

	@Override
	public String toString() {
		return SokobanLevelTemplate.printTilemap(tilemap);
	}
}
