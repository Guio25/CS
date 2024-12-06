
%room(1..k).
%table(1..4 * k).
%person(1..n).


%%%%%%%%%%%%%%%%%%%%%%%

1{is_in(T,R) : room(R)}1 :- table(T).

4{is_in(T,R): table(T)}4 :- room(R).

1{assign(X,T,R) : table(T), room(R), is_in(T,R)}1 :- person(X).

equal(T1,T2,R1,R2) :- table(T1), table(T2), room(R1), room(R2), is_in(T1,R1), is_in(T2,R2), T1 = T2, R1 = R2.

:- person(X), person(Y), X != Y, same_table(X,Y), assign(X,T1,R1), assign(Y,T2,R2), not equal(T1,T2,R1,R2), table(T1), table(T2), room(R1), room(R2), is_in(T1,R1), is_in(T2,R2).  

:- person(X), person(Y), X != Y, hate(X,Y), assign(X,_,R), assign(Y,_,R), room(R).

:- person(X), dangerous(X), assign(X,_,R), room(R), not security_cameras(R).
 
count_seats_occupied(R,T,S) :-  table(T), room(R), is_in(T,R) ,S = #count{ X: person(X),assign(X,T,R) }. 

bad_assignment :- table(T), room(R), is_in(T,R), count_seats_occupied(R,T,S), S > 4.

:- bad_assignment.

room_used(C) :- C = #count{K : room(K), assign(_,_,K) }.

#minimize {C : room_used(C)}.



#show count_seats_occupied/3.
%#show is_in/2.
#show assign/3.
%#show security_cameras/1.
