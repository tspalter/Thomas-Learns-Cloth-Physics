# Thomas-Learns-Cloth-Physics
Cloth Physics simulation learned for CS 560.

CONTROLS
----------------
Camera:
Left Click = Rotate camera position

Sphere Movement (movement is relative to global space, not camera orientation):
W = Up
S = Down
A = Left
D = Right
Q = Up
E = Down

Simulation Controls:
1 = Start simulation
2 = Pause simulation
3 = Restart simulation

Toggle controls:
P = toggle mass points
T = toggle texture
R = toggle wireframe
F = toggle flat shade
B = toggle springs
K = toggle Verlet/Runge-Kutta

Value controls:
M = increase point mass (max 3)
N = decrease point mass (min 0.5)
(Mass point resolution means the total of mass points in the system.  A resolution N yields a system where there are NxN total mass points evenly distributed across
the plane of the cloth.  The default resolution value is 30.)
+ = increase mass point resolution (max 80)
- = decrease mass point resolution (min 20)

COMPILATION
Compile through the .sln file in Visual Studio

IMPORTANT ALGORITHMS
Point.cpp
I implemented Verlet Integration and a very slow moving 2nd-order Runge-Kutta methods in this file in respective functions that can be toggled through the program.
There is also a relevant function called CheckCollisions which detects sphere-sphere collisions based on the location of a point and the solid sphere in system.

Spring.cpp
The Update function contains the use of the spring force that gets applied to the two mass points connected by the spring.  This is what creates the elastic movement
of the cloth.