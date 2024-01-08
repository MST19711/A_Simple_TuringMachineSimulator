
#Q = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,c,_,I,l,e,g,a,n,p,u,t}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {24}

; the number of tapes
#N = 2

; the transition functions

;2 : Illegal_Input
;

;
2 *_ __ l* 2 ;t
2 __ __ r* 3; s
3 __ I_ r* 4   ;asd
4 __ l_ r* 5
5 __ l_ r* 6
6 __ e_ r* 7
7 __ g_ r* 8
8 __ a_ r* 9
9 __ l_ r* 10
10 __ __ r* 11
11 __ I_ r* 12
12 __ n_ r* 13
13 __ p_ r* 14
14 __ u_ r* 15
15 __ t_ r* 16


;25 : clear and then Illegal_Input

25 ** ** l* 25
25 *_ *_ l* 25
25 _* _* r* 26
25 __ __ r* 26

26 *_ __ r* 26
26 ** _* r* 26
26 _* _* ** 2
26 __ __ ** 2

;main
0 __ __ ** 25
0 a_ a_ ** 1
0 b_ b_ ** 25
1 a_ a_ r* 1
1 __ __ l* 25
1 b_ b_ r* 17

17 b_ b_ r* 17
17 __ __ l* 27
17 a_ a_ ** 25

27 *_ *_ l* 27
27 __ __ r* 18


18 a_ __ r* 19
18 b_ b_ ** 22

19 a_ a_ r* 19
19 b_ b_ ** 20

20 b_ bc rr 20
20 __ __ l* 21

21 *_ *_ l* 21
21 __ __ r* 18

22 b_ __ r* 22
22 __ __ *l 23

23 _c cc ll 23
23 __ __ ll 24