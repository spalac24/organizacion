#SimuProc 1.4.2.0


MOV FF5,FF4
MSG "This program is designed to check the roots of a cuadratic function in a given interval"

MSG "Please write the coefficients a,b,c in ax^2+bx+c"

IN AX,1
STF F00
IN AX,1
STF F02
IN AX,1
STF F04


MSG "Please write the interval limits [l,r]"
IN AX,1
STF F10
STF F14
IN AX,1
STF F12



JMP 30
#30

LDF F10
SUBF F12
JMA 150
JMP 40

#40

LDF F10
MSG "x = "
OUT 1,AX
MULF F10
MULF F00
STF E00
LDF F10
MULF F02
STF E02
LDF F04
STF E04
ADDF E00
ADDF E02
MSG "f(x) = "
OUT 1,AX
LDF F10
ADDF FC1
STF F10
JMP 30



#150

LDF F00
MULF FCD
STF B10

LDF F02
MULF F02
STF B00
LDF F00
MULF F04
MULF FC4
STF B02
LDF B00
SUBF B02
STF B04
LDF F02
SUBF F02
SUBF F02
STF B08
DIVF B10
STF B12
LDF B04
JMP 200


;X = (-B +- SQRT(B*B - 4*A*C))/(2*A)



;En el registro 200 almacenare la raiz
;En el registro 202 el numero al que le calculamos

;newton method
; x_n = x_(n-1) + f(x_(n-1))/(2*x_(n-1))


;calcula la raiz cuadrada del numero
;almacenado en BX,AX
#200
STF A04      ;Guardo el x original
LDF C10      ;Cargo el 100.0 (guess inicial)
STF A00      ;lo guardo como x0
LDF A00      ;Cargo el xn-1
MULF A00     ;lo elevo al cuadrado
SUBF A04     ;le resto x original
STF A06      ;xi*xi-x
;msg f
;out 1,ax
LDF FCD      ;cargo 2.0
MULF A00     ;lo multiplico por x
STF A08      ;f'(xi)
;msg fp
;out 1,ax
LDF A06      ;f
DIVF A08     ;f/f'
STF A10
;msg divi
;out 1,ax
LDF A00      ;xi
SUBF A10     ;xi - f/f'
STF A00
MOV CX,FF5
DEC CX
MOV FF5,CX

LOOP 203

STF B06
DIVF B10
STF B14
MSG "The set of roots of the function in the interval is {"
LDF B12
SUBF B14
STF AB2
SUBF F14
JME 250
LDF AB2
SUBF F12
JMA 250
LDF AB2
OUT 1,AX
LDA AB0
ADD FB1
STA AB0
JMP 250

#250
LDF B12
ADDF B14
STF AB2
SUBF F14
JME DDD
LDF AB2
SUBF F12
JMA DDD
LDF AB2
OUT 1,AX
LDA AB0
ADD FB1
STA AB0
JMP DDD


#DDD
LDA AB0
MUL AB0
JEQ DCD
MSG "}"
MSG "The program has finished"
HLT
#DCD
MSG "}"
MSG "(There are no roots in the interval)"
MSG "The program has finished"
HLT

#DEB
LDF B00
OUT 1,AX
LDF B02
OUT 1,AX
LDF B04
OUT 1,AX
LDF B06
OUT 1,AX
LDF B08
OUT 1,AX
LDF B10
OUT 1,AX
LDF B12
OUT 1,AX
LDF B14
OUT 1,AX


#FB1
;1 Int
0000000000000001

#FC1
;1.0 en flotante
0011111110000000
0000000000000000

#FCD
;2.0
0100000000000000
0000000000000000

#FC4
;4.0
0100000010000000
0000000000000000

#C10
;100.0
0100001011001000
0000000000000000

#CE0
;epsilon 9.9E-6
0011011100100111
0000000000000000

#FF4
100000

#FFE
;SQUARE TEST
0011101111001000
0000000000000000
