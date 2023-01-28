% Ex 1:
vars(X, [X]) :- atom(X).
vars(non(X), L) :- vars(X, L).
vars(si(X, Y), L) :- vars(X, L1), vars(Y, L2), union(L1, L2, L).
vars(sau(X, Y), L) :- vars(X, L1), vars(Y, L2), union(L1, L2, L).
vars(imp(X, Y), L) :- vars(X, L1), vars(Y, L2), union(L1, L2, L).


% Ex 2:
val(V, [(V, A) | _], A).
val(V, [_ | T], A) :- val(V, T, A).


% Ex 3:
bnon(0, 1).
bnon(1, 0).

bsi(0, 0, 0).
bsi(0, 1, 0).
bsi(1, 0, 0).
bsi(1, 1, 1).

bsau(0, 0, 0).
bsau(0, 1, 1).
bsau(1, 0, 1).
bsau(1, 1, 1).

bimp(0, 0, 1).
bimp(0, 1, 1).
bimp(1, 0, 0).
bimp(1, 1, 1).

% X -> Y = (non X) sau Y
bimp(X,Y,Z) :- bnon(X,NX), bsau(NX,Y,Z).


% Ex 4:
eval(X, E, A) :- atom(X), val(X, E, A).
eval(non(X), E, A) :- eval(X, E, B), bnon(B, A).
eval(si(X, Y), E, A) :- eval(X, E, B), eval(Y, E, C), bsi(B, C, A).
eval(sau(X, Y), E, A) :- eval(X, E, B), eval(Y, E, C), bsau(B, C, A).
eval(imp(X, Y), E, A) :- eval(X, E, B), eval(Y, E, C), bimp(B, C, A).


% Ex 5:
evals(_, [], []).
evals(X, [E | Es], [A | As]) :- eval(X, E, A), evals(X, Es, As).


% Ex 6:
evs([], [[]]).
evs([V|S], Es) :- evs(S, Es1), adauga(V, Es1, Es).
adauga(_, [], []).
adauga(V, [E|T], [[(V,0)|E], [(V,1)|E] | Es]) :- adauga(V, T, Es).


% Ex 7:
all_evals(X, As) :- vars(X, Lv), evs(Lv, Es), evals(X, Es, As).


% Ex 8:
all_ones([]).
all_ones([1|T]) :- all_ones(T).
taut(X) :- all_evals(X, As), all_ones(As).