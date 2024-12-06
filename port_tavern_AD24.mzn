%%%%%%%%%% Instance 01

int : k = 4;  %%% Rooms
int : t = 4;  %%% Tables per room
int : n = 10; %%% People

array[1..n,1..n] of 0..1 : same_table =  
[| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 1, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
|];

array[1..n,1..n] of 0..1 : hate =  
[| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
|];

array[1..n] of 0..1 : dangerous = [ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, ];

array[1..k] of 0..1 : security_cameras = [ 0, 1, 0, 1, ];


%%%% FEBRUARY 2024.
%%%% Encoded by AD. Instances by Matteo Guiotto


 

%%% vectors to store in which table of a room the people are sit
array [1..n] of var  1..k : assign_room;
array [1..n] of var  1..t : assign_table;

var 1..k : used_rooms;

%%% Constraint same table:
constraint
    forall (i,j in 1..n)
         (same_table[i,j] = 1 -> (assign_room[i]=assign_room[j] /\  assign_table[i]=assign_table[j]));
         
%%% Constraint hate:
constraint 
    forall (i,j in 1..n)
         (hate[i,j] = 1 -> assign_room[i]!=assign_room[j]);
         
%%% Constraint dangerous:
constraint 
    forall (p in 1..n)
       ((dangerous[p] = 1) -> 
         (security_cameras[assign_room[p]] = 1));

%%% At most 4 people in a table
constraint forall (i in 1..k, j in 1..t) 
       (sum(p in 1..n)(assign_room[p]=i /\ assign_table[p]=j) <= 4 );

%%% Count the number of used rooms
constraint 
        used_rooms = count (i in 1..k) (exists (p in 1..n) (assign_room[p] = i ) );  

solve minimize used_rooms;