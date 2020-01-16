# Path Optimizer

This Path Optimizer algorithm is the final step in a Maze Solver project.

## Author

Younes Reda   
yreda@uwaterloo.ca

## TL;DR

This path optimizing algorithm takes in some headings and distances relating to the path travelled by a robot
inside a simply-connected maze. The algorithm outputs an abbreviated path with no-backtracking.

## Definitions

Simply Connected Maze: A 2-D maze with no outer-loops.

Optimized Path: A path that contains no back-tracking. (ie. never goes forwards and then backwards).

Right Hand Rule: An unoptimal maze solving method, in which the subject places their "hand" on the right wall and 
                walks along the maze.

Vector: A concise representation of a heading and direction that is stored as a cpp vector.
        Ex: Direction = North, Distance = 20, then vector = <0,20>
            Direction = South, Distance = 20, then vector = <0,-20>
            Direction = East, Distance = 20, then vector = <20,0>

## Context

This path optimizing algorithm is the final step in a Maze Solver project. A robot built on EV3 Mindstorm hardware
solves any simply connected maze by the right hand rule, and logs its path using motor encoders and a gyroscope.
Once the maze is solved and the data has been gathered, it relays the information to this Path Optimizing algorithm,
which runs on a separate computer.

The input of the algorithm are vectors relating to the distances travelled and the headings taken.
The output of the algorithm is an abbreviated form of the input, such that no back-tracking is involved.

The maze solving portion of the project was taken on by myself and 3 other group members. This path optimizing algorithm was
developed entirely by me.

## Rules

The input vectors containing the distances and headings are always equal in size.
The only headings allowed are {'N', 'S', 'E', 'W'}

## Algorithm Logic

The base case for this algorithm is very simple. If given a set of parallel vectors, optimizing is trivial. The optimized
version of this input is simply the sum of these vectors.

If we think of every other case in terms of the base case, the solution becomes simplified. Given a set of vectors that are not necessarily
parallel, we can break it down into parallel sets. We can call these parallel sets runs. More formally, a run is a subset of a vector that is composed of contiguous parallel vectors. These runs are then summed together and appended to our final answer.

## Algorithm Steps

1. Input 2 vectors corresponding to the distances and headings the robot took to solve the maze. These 2 vectors are condensed into a single vector made of 2 dimensional vectors. These 2 dimensional vectors are of the form {x,y}, where a positive x corresponds to travelling a distance |x| eastward, and a positive y corresponds to travelling a distance |y| northward. Alternatively, a negative x corresponds to travelling a distance |x| westward, and a negative y corresponds to travelling a distance |y| southward.

2. Identify the runs within that vector. Runs are defined in the second half of the Algorithm Logic section.

3. By definition, these runs are the base case of the algorithm, and their optimization is simply their sum. So, we sum up the runs and append the result to a vector.

4. Finally, we process the vector containing the optimized data such that we can return the optimized path information in the same form as it was received. We return a struct containing an optimized version of the headings and distances vectors.

## Example

```
INPUT: distances      = {100,20,40,10,20,20,80,30,20,10,30,10,5,5};
       headings       = {'N','S','W','N','E','W','S','W','N','E','N','W','S','W'};
OUTPUT: o_distances   = {80,40,10,80,30,20,10,30,10,5,5};
        o_headings    = {'N','W','N','S','W','N','E','N','W','S','W'}
```

## Short Comings/ Next Steps

There are some cases where the output of the algorithm is not entirely simplified. These cases arise when some run that used to separate parallel vectors cancels itself out. 
Ex:
```
INPUT: distances = {1,1,1,1}, headings = {'N','E','W','N'};
ALGORITHM'S OUTPUT: o_distances = {1,1}, o_headings = {'N','N'}
BETTER OUTPUT: o_distances = {2}, o_headings = {'N'}
```
A potential solution to this is to make the algorithm recursive and have it end once the size of the optimized vector does not change after optimizing.

The next step for this project is to add a GUI element to it, in order to make its presentation easier and more intuitive to understand.# robot_path_optimizer

## Short Comings/ Next Steps

Below are images of the robot and maze. (Size 12 shoe for reference!)
![] (images/maze.jpg)
![] (images/robot_side_profile.png)
![] (images/robot_side_profile.jpg)