package de.cas.futurelabs.sokoban;

public enum SokobanTile {
	empty(' '), 
	wall('#'), 
	player('@'), 
	box('$'), 
	goal('.'), 
	box_on_goal('*'), 
	player_on_goal('+'),
	possible_player_wall_box('0'), 
	possible_player('1'), 
	possible_wall('2'), 
	possible_box('3'),
	possible_player_wall('4'), 
	possible_player_box('5'), 
	possible_wall_box('6');

	char symbol;

	SokobanTile(char symbol) {
		this.symbol = symbol;
	}

	public boolean isTemplateTile() {
		return "0123456".contains(Character.toString(this.symbol));
	}

	public static SokobanTile valueForSymbol(char symbol) {
		for (SokobanTile tile : SokobanTile.values()) {
			if (tile.symbol == symbol) {
				return tile;
			}
		}
		throw new IllegalArgumentException("Unknown symbol: " + symbol);
	}

	@Override
	public String toString() {
		return Character.toString(symbol);
	}

}