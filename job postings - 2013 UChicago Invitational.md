# Problem G: Job Posting

Your university has jobs available for students, and the administration needs for you to help them assign students to jobs. The goal is to have students select their desired positions, and then allocate each student to one of the positions so that the maximum satisfaction is achieved.

Each student selects four positions, in the order of desirability. First position is most wanted, next position is next most wanted, if the first position is not available for this student, and so on.

Students have seniority, based their year of study. Third-year students’ selections should have more weight than first-year students’ selections.

The administration wants for you to use the following satisfaction matrix:
Job/Position choice:    1st    2nd    3rd    4th
1st year student:        4     3       2      1
2nd year student:        8     7       6      5
1st year student:        12    11      10     9

Your task is to assign students to positions in a way that maximizes the sum of
all students’ satisfaction according to the above matrix. Each student must get a
position, but all positions may not be filled.

## Input:
There will be multiple test cases in the input. Each test case will begin with two integers, n (4≤n≤140) and m (1≤m≤70), where n is the number of postings and m is the number of students. Each of the next n lines will contain a single integer p (1≤p≤10), indicating the number of positions available for that job posting. The job postings are listed in order, from job 0 to job n-1.

Following the job postings will be m lines describing the students. Each student line will have five integers:
      y c1 c2 c3 c4
Where y (y=1, 2 or 3) is the student’s year of study, and c1, c2, c2 and c4 (0≤c1,c2,c3,c4<n, all four unique) indicating the student’s choice of job postings, in order of preference.

It is guaranteed for every test case that a solution exists where every student can get one of the positions on their choice list.

The input will end with a line with two 0s.

## Output:
For each test case, output a single integer, which indicates the maximum satisfaction achievable. Output no spaces, and do not output a blank line between answers.

## Sample Input
4 4 // 
1 // 
1 // 
1 // 
1 // 
1 0 1 2 3 // 
2 0 1 2 3 // 
3 0 1 2 3 // 
3 0 1 2 3 // 
4 4 // 
4 // 
4 // 
4 // 
4 // 
1 0 1 2 3 // 
2 0 1 2 3 // 
3 0 1 2 3 // 
3 0 1 2 3 // 
0 0 // 

## Sample Output
30 // 
36
