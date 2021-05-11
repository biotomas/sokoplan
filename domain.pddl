(define (domain sokoban)
  (:requirements :strips :typing)

  (:types
   square count_wall count_box count_goal - object
   )

  (:predicates
   ; ridgid
   (above ?a ?b - square)
   (left ?a ?b - square)
   (opt_wall ?to - square)
   (opt_box ?to - square)
   (opt_goal ?to - square)
   (opt_player ?to - square)
   (next_count_wall ?old ?new - count_wall)
   (next_count_box ?old ?new - count_wall)
   (next_count_goal ?old ?new - count_wall)

   (current_count_wall ?count - count_wall)
   (current_count_box ?count - count_wall)
   (current_count_goal ?count - count_wall)
   (current_count_player)
   (construction)
   (final)
   (wall ?s - square)
   (box ?s - square)
   (player ?s - square)
   (goal ?s - square)
   )

  (:action place_wall
           :parameters(?to - square ?old ?new - count_wall)
           :precondition(and
                         (construction)
                         (current_count_wall ?old)
                         (next_count_wall ?old ?new)
                         (opt_wall ?to)
                         (not (wall ?to))
                         (not (box ?to))
                         (not (player ?to))
                         )
           :effect(and
                   (wall ?to)
                   (not (current_count_wall ?old))
                   (current_count_wall ?new)
                    ))

  (:action place_box
           :parameters(?to - square ?old ?new - count_box)
           :precondition(and
                         (construction)
                         (current_count_box ?old)
                         (next_count_box ?old ?new)
                         (opt_box ?to)
                         (not (wall ?to))
                         (not (box ?to))
                         (not (player ?to))
                         )
           :effect(and
                   (box ?to)
                   (not (current_count_box ?old))
                   (current_count_box ?new)
                   ))

  (:action place_player
           :parameters(?to - square)
           :precondition(and
                         (construction)
                         (opt_player ?to)
                         (not (current_count_player))
                         (not (wall ?to))
                         (not (box ?to))
                         )
           :effect(and
                   (current_count_player)
                   (player ?to)
                   ))

  (:action finish_construction
           :parameters(?current - count_wall)
           :precondition(construction)
           :effect(not (construction)))

  (:action move_u
           :parameters(?from ?to - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?to))
                         (above ?to ?from)
                         (player ?from)
                         (not (box ?to))
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   ))

  (:action move_d
           :parameters(?from ?to - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?to))
                         (above ?from ?to)
                         (player ?from)
                         (not (box ?to))
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   ))

  (:action move_l
           :parameters(?from ?to - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?to))
                         (left ?to ?from)
                         (player ?from)
                         (not (box ?to))
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   ))

  (:action move_r
           :parameters(?from ?to - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?to))
                         (left ?from ?to)
                         (player ?from)
                         (not (box ?to))
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   ))


  (:action push_u
           :parameters(?from - square ?to ?newBox - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?newBox))
                         (above ?newBox ?to)
                         (above ?to ?from)
                         (player ?from)
                         (box ?to)
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   (not (box ?to))
                   (box ?newBox)
                   ))

  (:action push_d
           :parameters(?from - square ?to ?newBox - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?newBox))
                         (above ?from ?to)
                         (above ?to ?newBox)
                         (player ?from)
                         (box ?to)
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   (not (box ?to))
                   (box ?newBox)
                   ))

  (:action push_l
           :parameters(?from - square ?to ?newBox - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?newBox))
                         (left ?newBox ?to)
                         (left ?to ?from)
                         (player ?from)
                         (box ?to)
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   (not (box ?to))
                   (box ?newBox)
                   ))

  (:action push_r
           :parameters(?from - square ?to ?newBox - square)
           :precondition(and
                         (not (construction))
                         (not (final))
                         (not (wall ?newBox))
                         (left ?from ?to)
                         (left ?to ?newBox)
                         (player ?from)
                         (box ?to)
                         )
           :effect(and
                   (not (player ?from))
                   (player ?to)
                   (not (box ?to))
                   (box ?newBox)
                   ))

  (:action set_final
           :parameters()
           :precondition(not (final))
           :effect(final))

  (:action place_goal
           :parameters(?to - square ?old ?new - count_goal)
           :precondition(and
                         (final)
                         (current_count_goal ?old)
                         (next_count_goal ?old ?new)
                         (opt_goal ?to)
                         (not (goal ?to))
                         (box ?to)
                         )
           :effect(and
                   (goal ?to)
                   (not (current_count_goal ?old))
                   (current_count_goal ?new)
                   ))

  )
