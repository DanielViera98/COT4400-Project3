# COT4400-Project3
This project was for COT4400, completed solo. The maze.cpp file takes input from a file (specified in the code on line 32) and processes it as a 3-d matrix.
Basically, it finds a route for a "mouse" beginning at a certain point on the maze, and routes it to an end point. The first line of the input is the size of the maze.
The second is the start point, the third is the end point. Each "cell" of the matrix consists of a series of 0s and 1s which tell the program what direction is allowed.
Once the program finishes, it outputs to a file the directions it took. The program is optimal, so it will find the best solution. In this case, my program found a
shorter path than the one provided in example solutions.

To run, just make sure the input file name is correct, compile, and run.
