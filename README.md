# sokoban-solver
Symbolic reasoning planner for the Sokoban game. 
Primary practical of course Introduction to Artificial Intelligence (T550000101).

## Game Representation
By default, the game  board is represented by 5 ASCII characters:
| Unit               | ASCII Character | 
|--------------------|-----------------|
| Walkable position. | `.`             |
| Wall               | `#`             |
| Agent              | `M`             |
| Box                | `J`             |
| Goal               | `G`             |

In this implementation, two additional ASCII characters are introduced:

| Unit               | ASCII Character | 
|--------------------|-----------------|
| Agent (on goal)    | `m`             |
| Box (on goal)      | `j`             |
