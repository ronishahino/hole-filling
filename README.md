
Instruction for operating the command line utility:
=============================

1. OpenCV needs to be installed   
a. version >= 3.1.    
b. The bin directory (something like - C:\opencv\build\x64\vc14\bin) - needs to be added to (Environment Variables->Path).

2. Run the utility command line (interview_excercise_hole_filling.exe) with parameters as follows
a. image path (example in : submission_files\input_files_for_example\image1.jpg ).
b. mask path  (example in : submission_files\input_files_for_example\mask1.jpg ).
c. Z.
d. Epsilon.
e. conectivity type (expected values: 4 or 8).

Example of running:
>>cd "the path to submission_files"\submission_files

>>interview_excercise_hole_filling.exe input_files_for_example\\image1.jpg input_files_for_example\\mask1.jpg 3 0.001 8

The output file is saved under the folder from which the command line was operated.


Directory path for code review
=============================

· all "library" related files (.h and .cpp) are grouped under directory : hole_filling_'library'.

· all command line utility related files (.h and .cpp) are grouped under directory : command_line_utility.


Questions
=============================

 
### Question A.

If there are m boundary pixels and n pixels inside the hole. the complexity of the algorithm is: 
  **O(n*m)**.  for each hole pixel we sum over all pixels in the  boundary. 

Express m by n:

The worst case is when every pixel in the hole is connecting only with another 2 
hole pixels in a way that they share as little neighbors as possible:
For 4-conectivity its simply a line. and for 8-conectivity its a diagonal line.
In this case **m = O(n)**. every hole pixel adds k neighbors to boundary. so we
have n*k boundary pixels.

The best case is a hole shape that has the smallest perimeter per area -> a circle.
If the hole pixels arranged in a circle like shape. with area of O(n).
The perimeter ( boundary ) is  **m = Omega(sqrt(n))**. 
  
So total run time is:

**Omega(n*sqrt(n)).**

**O(n^2).**

-----------------------------------------------------------------------------

### Question B.

Approximate algorithm in O(n):
 
Every hole pixel is estimated only by its neighbors. Instead of all boundary pixels.
We visit from the most outer pixels ( closest to boundary) up to the most internal,
So that a pixel closer to the boudary fills before a pixel farther from the boundary.
  
Algorithm:

1. We go over the boundary pixels. And find the hole pixels that connect (neighbor) to them.
Those hole pixels filled only by their neighbors (the boundary).
2. Now the hole is shrinking. And we update the new boundary - ( all the pixels we just filled).
3. We will repeat this process (1 + 2) until the entire hole is filled.

Run time is O(n). explanation:
For each pixel, we visit all of its neighbors to see whether to put them in the new boundary for the next iteration.
and in addition, to estimating the value of the pixel, we average over its neighbors.
=> Every pixel require x (num neighbors) calculations.

(This algorithm is also implemented in the code).
