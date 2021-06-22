(define (domain sokoban)
	(:requirements :strips :typing)
	(:types
		tile count box wall - object
	)

	(:predicates
		;rigid
		(above ?a ?b - tile)
		(left ?a ?b - tile)
		(opt_wall ?to - tile)
		(opt_box ?to - tile)
		(opt_player ?to - tile)
		(next_count ?previous ?next - count)

		(box_placed ?b - box)
		(wall_placed ?w - wall)
		(count_push ?val - count)

		; what is placed
		(wall_at ?s - tile)
		(box_at ?s - tile)
		(player_at ?s - tile)

		; phases
		(making_level)
		(playing)
	)

	(:action place_wall
		:parameters(?w - wall ?to - tile)
		:precondition(and
			(making_level)
			(opt_wall ?to)
			(not (wall_placed ?w))
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(wall_at ?to)
			(wall_placed ?w)
		)
	)

	(:action place_box
		:parameters(?b - box ?to - tile)
		:precondition(and
			(making_level)
			(opt_box ?to)
			(not (box_placed ?b))
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(box_at ?to)
			(box_placed ?b)
		)
	)

	(:action place_player_and_start
		:parameters(?to - tile)
		:precondition (and
			(making_level)
			(opt_player ?to)
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(player_at ?to)
			(not (making_level))
			(playing)
		)
	)


	(:action start_play
		:parameters()
		:precondition(and
			(making_level)
		)
		:effect(and
			(not (making_level))
			(playing)
		)
	)

	(:action move_up
		:parameters(?from ?to - tile)
		:precondition(and
			(playing)
			(above ?to ?from)
			(player_at ?from)
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(not (player_at ?from))
			(player_at ?to)
		)
	)

	(:action move_down
		:parameters(?from ?to - tile)
		:precondition(and
			(playing)
			(above ?from ?to)
			(player_at ?from)
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(not (player_at ?from))
			(player_at ?to)
		)
	)

	(:action move_left
		:parameters(?from ?to - tile)
		:precondition(and
			(playing)
			(left ?to ?from)
			(player_at ?from)
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(not (player_at ?from))
			(player_at ?to)
		)
	)

	(:action move_right
		:parameters(?from ?to - tile)
		:precondition(and
			(playing)
			(left ?from ?to)
			(player_at ?from)
			(not (wall_at ?to))
			(not (box_at ?to))
		)
		:effect(and
			(not (player_at ?from))
			(player_at ?to)
		)
	)

	(:action push_up
		:parameters(?from - tile ?to ?newBox - tile ?old ?new - count)
		:precondition(and
			(playing)
			(next_count ?old ?new)
			(count_push ?old)
			(not (wall_at ?newBox))
			(not (box_at ?newBox))
			(above ?newBox ?to)
			(above ?to ?from)
			(player_at ?from)
			(box_at ?to)
		)
		:effect(and
			(not (count_push ?old))
			(count_push ?new)
			(not (player_at ?from))
			(player_at ?to)
			(not (box_at ?to))
			(box_at ?newBox)
		)
	)

	(:action push_down
		:parameters(?from - tile ?to ?newBox - tile ?old ?new - count)
		:precondition(and
			(playing)
			(next_count ?old ?new)
			(count_push ?old)
			(not (wall_at ?newBox))
			(not (box_at ?newBox))
			(above ?from ?to)
			(above ?to ?newBox)
			(player_at ?from)
			(box_at ?to)
		)
		:effect(and
			(not (count_push ?old))
			(count_push ?new)
			(not (player_at ?from))
			(player_at ?to)
			(not (box_at ?to))
			(box_at ?newBox)
		)
	)

	(:action push_left
		:parameters(?from - tile ?to ?newBox - tile ?old ?new - count)
		:precondition(and
			(playing)
			(next_count ?old ?new)
			(count_push ?old)
			(not (wall_at ?newBox))
			(not (box_at ?newBox))
			(left ?newBox ?to)
			(left ?to ?from)
			(player_at ?from)
			(box_at ?to)
		)
		:effect(and
			(not (count_push ?old))
			(count_push ?new)
			(not (player_at ?from))
			(player_at ?to)
			(not (box_at ?to))
			(box_at ?newBox)
		)
	)

	(:action push_right
		:parameters(?from - tile ?to ?newBox - tile ?old ?new - count)
		:precondition(and
			(playing)
			(next_count ?old ?new)
			(count_push ?old)
			(not (wall_at ?newBox))
			(not (box_at ?newBox))
			(left ?from ?to)
			(left ?to ?newBox)
			(player_at ?from)
			(box_at ?to)
		)
		:effect(and
			(not (count_push ?old))
			(count_push ?new)
			(not (player_at ?from))
			(player_at ?to)
			(not (box_at ?to))
			(box_at ?newBox)
		)
	)
)
