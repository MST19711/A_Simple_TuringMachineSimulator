
#Q = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}

; the finite set of input symbols
#S = {a,b,c}

; the complete set of tape symbols
#G = {a,b,c,_,t,r,u,e,f,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {15}

; the number of tapes
#N = 2

; the transition functions

; 1 : false
1 ** ** r* 1
1 *_ *_ r* 1
1 _* _* l* 2
1 __ __ l* 2

2 *_ __ l* 2
2 ** _* l* 2
2 _* _* ** 3
2 __ __ ** 3

3 _* f* r* 4
3 __ f_ r* 4

4 _* a* r* 5
4 __ a_ r* 5

5 _* l* r* 6
5 __ l_ r* 6

6 _* s* r* 7
6 __ s_ r* 7

7 _* e* r* 8
7 __ e_ r* 8

; 9 : true
9 ** ** r* 9
9 *_ *_ r* 9
9 _* _* l* 10
9 __ __ l* 10

10 *_ __ l* 10
10 ** _* l* 10
10 _* _* r* 11
10 __ __ r* 11

11 *_ t_ r* 12
11 ** t* r* 12
11 __ t_ r* 12
11 _* t* r* 12

12 *_ r_ r* 13
12 ** r* r* 13
12 __ r_ r* 13
12 ** r* r* 13

13 *_ u_ r* 14
13 ** u* r* 14
13 __ u_ r* 14
13 _* u* r* 14

14 *_ e_ r* 15
14 ** e* r* 15
14 __ e_ r* 15
14 _* e* r* 15

;main
0 a_ aa rr 0
0 b_ bb rr 0
0 _* _* ** 1
0 __ __ ** 1
0 c_ c_ *l 16

16 ** ** *l 16
16 *_ *_ rr 17
16 _* _* rr 17

17 aa aa rr 17
17 bb bb rr 17
17 __ __ ** 9

17 ab ab ** 1
17 ba ba ** 1
17 ac ac ** 1
17 ca ca ** 1
17 cb cb ** 1
17 bc bc ** 1
17 a_ a_ ** 1
17 b_ b_ ** 1
17 c_ c_ ** 1
17 _a _a ** 1
17 _b _b ** 1
17 _c _c ** 1

