% Ex 2:

female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(dony).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

father_of(Father, Child):- parent(Father, Child), male(Father).
mother_of(Mother, Child):- parent(Mother, Child), female(Mother).

grandfather_of(G, C):- parent(G, P), parent(P, C), male(G).
grandmother_of(Gm, C):- parent(Gm, P), parent(P, C), female(Gm).

sister_of(Sister, Person):- parent(P, Sister), parent(P, Person), female(Sister), Sister\==Person.
brother_of(Brother, Person):- parent(P, Brother), parent(P, Brother), male(Brother), Brother\==Person.

aunt_of(Aunt, Person):- sister_of(Aunt, P), parent(P, Person).
uncle_of(Uncle, Person):- brother_of(Uncle, P), parent(P, Person).


% Ex 3:

not_parent(X,Y) :- (male(X); female(X)), (male(Y); female(Y)), X\=Y, not(parent(X, Y)).