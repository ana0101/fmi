% Ex 1:
reverse([], []).
reverse([H|T], L1) :-
    reverse(T, L2),
    append(L2, [H], L1).

palindrome(L) :-
    reverse(L, L).


% Ex 2:
remove_duplicates([], []).

remove_duplicates([H|T], R) :-
    remove_duplicates(T, R),
    member(H, R).

remove_duplicates([H|T], [H|R]) :-
    remove_duplicates(T, R),
    not(member(H, R)).


% Ex 3:
atimes(_, [], 0).

atimes(N, [N|T], X) :-
    atimes(N, T, Y),
    X is Y+1.

atimes(N, [H|T], X) :-
    atimes(N, T, X),
    N \== H.


% Ex 4:
insert(X, [], [X]).
insert(X, [H|T], R) :- append([X], [H|T], R), X < H.
insert(X, [H|T], [H|R]) :- insert(X, T, R), X > H.
insert(X, [H|T], [H|R]) :- insert(X, T, R), X == H.
                         
insertsort([], []).
insertsort([H|T], L) :- insertsort(T, L1), insert(H, L1, L).


% Ex 5:
split(_, [], [], []).
split(P, [H|T], [H|A], B) :- split(P, T, A, B), H < P.
split(P, [H|T], A, [H|B]) :- split(P, T, A, B), H >= P.

quicksort([], []).
quicksort([H|T], L) :- split(H, T, A, B), quicksort(A, M), quicksort(B, N), append(M, [H|N], L).