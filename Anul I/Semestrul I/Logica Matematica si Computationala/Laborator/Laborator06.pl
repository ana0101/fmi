% Ex 1:
flatten([], []).
flatten([H|T], [H|R]) :- not(is_list(H)), flatten(T, R).
flatten([H|T], R) :- is_list(H), flatten(H, R1), flatten(T, R2), append(R1, R2, R).

flattend(L, R) :- flattendh(L, (R, [])).
flattendh([], (R, R)).
flattendh([H|T], ([H|R], S)) :- not(is_list(H)), flattendh(T, (R, S)).
flattendh([H|T], (R, S)) :- is_list(H), flattendh(H, (R, N)), flattendh(T, (N, S)).


% Ex 2:
quicksort([], []).
quicksort([H|T], L) :- split(H, T, A, B), quicksort(A, M), quicksort(B, N), append(M, [H|N], L).
split(_, [], [], []).
split(X, [H|T], [H|A], B) :- H < X, split(X, T, A, B).
split(X, [H|T], A, [H|B]) :- H >= X, split(X, T, A, B).


quicksortd(L, R) :- quicksortdh(L, (R, [])).
quicksortdh([], (R, R)).
quicksortdh([H|T], (R, S)) :- split(H, T, A, B), quicksortdh(A, (R, [H|P])), quicksortdh(B, (P, S)).