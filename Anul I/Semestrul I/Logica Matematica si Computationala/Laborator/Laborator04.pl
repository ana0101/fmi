% Ex 1:
listaNelem(_, 0, []).
listaNelem(L, N, [H|T]) :- N > 0, member(H, L), M is N-1, listaNelem(L, M, T).


% Ex 2:
word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).
word(enhance,e,n,h,a,n,c,e).

crossword(V1, V2, V3, H1, H2, H3) :-
    word(V1, _, L1, _, L2, _, L3, _),
    word(V2, _, L4, _, L5, _, L6, _),
    word(V3, _, L7, _, L8, _, L9, _),
    word(H1, _, L1, _, L4, _, L7, _),
    word(H2, _, L2, _, L5, _, L8, _),
    word(H3, _, L3, _, L6, _, L9, _).

bagof((V1, V2, V3, V4, V5, V6), crossword(V1, V2, V3, V4, V5, V6), L).
findall((V1, V2, V3, V4, V5, V6), crossword(V1, V2, V3, V4, V5, V6), L).


% Ex 3:
path(X, X, [X]).
path(X, Y, [X|L]) :- connected(X, Z), path(Z, Y, L). 
pathc(X, Y) :- path(X, Y, _).


% Ex 4:
word_letters(X,Y) :- atom_chars(X,Y).

liminus([C|L],C,L).
liminus([D|L],C,[D|M]) :- D\==C, liminus(L,C,M).

cover([],_).
cover([H|T],L) :- liminus(L,H,M), cover(T,M).

solution(Letters, Word, Len) :- word(Word), word_letters(Word,WordLetters), length(WordLetters,Len), cover(WordLetters, Letters).

search_solution(_,'no solution',0).
search_solution(ListLetters,Word,X) :- X > 0, solution(ListLetters,Word,X).
search_solution(ListLetters,Word,X) :- X > 0, not(solution(ListLetters,Word,X)), Y is X-1, search_solution(ListLetters,Word,Y).

topsolution(ListLetters,Word) :- length(ListLetters, MaxScore), search_solution(ListLetters,Word,MaxScore).