% Ex 1:

distance( (X1, Y1), (X2, Y2), D ) :- 
    D is sqrt((X2-X1)**2 + (Y2-Y1)**2).


% Ex 2:

fib(0, 1).
fib(1, 1).

fib(N, X) :-
    M is N-1,
    fib(M, Y),
    P is N-2,
    fib(P, Z),
    X is Y+Z.

% Eficient:

fib2(0, 0, 1).
fib2(1, 1, 1).
fib2(N, Y, X) :-
    M is N-1,
    fib2(M, Z, Y),
    X is Y+Z.

fib(N, X) :-
    fib2(N, _, X).


% Ex 3:

line(0, _).
line(N, C) :-
	write(C),
    M is N-1,
    line(M, C).

square2(0, _, _).
square2(N, NR, C) :-
    line(NR, C),
    nl,
    M is N-1,
    square2(M, NR, C).

square(0, _).
square(N, C) :- 
    square2(N, N, C).


% Ex 4:

% A)
all_a([]).
all_a([a|X]) :-
    all_a(X).

% B)
trans_a_b([], []).
trans_a_b([a|X], [b|Y]) :-
    trans_a_b(X, Y).


% Ex 5:

% A)
scalarMult(_, [], []).
scalarMult(N, [HL|L], [HR|R]) :-
    HR is HL*N,
    scalarMult(N, L, R).

% B)
dot([], [], 0).
dot([H1|T1], [H2|T2], R1) :-
    dot(T1, T2, R2),
    R1 is R2 + H1*H2.

% C)
max([], 0).

max([H|T], R) :-
    max(T, R),
    H =< R.

max([H|T], H) :-
    max(T, R),
    H > R.