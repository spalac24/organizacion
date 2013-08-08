#SimuProc 1.4.2.0


MOV FF5,FF4 ; Iteraciones que se harán para encontrar la raíz
MSG "This program is designed to check the roots of a cuadratic function in a given interval"

MSG "Please write the coefficients a,b,c in ax^2+bx+c"

IN AX,1
STF F00 ;a
IN AX,1
STF F02 ;b
IN AX,1
STF F04 ;c


MSG "Please write the interval limits [l,r]"
IN AX,1
STF F10 ;l
STF F14 ;copia de l
IN AX,1
STF F12 ;r


JMP 30


#30
;inicio del ciclo que itera sobre el intervalo

LDF F10   ;cargue l
SUBF F12  ;reste r
JMA 150   ;si l es mayor (el resultado es positivo) vaya a 150, termino de iterar
JMP 40    ;si es menor, vaya a 40

#40

LDF F10          ;cargue l
MSG "x = "
OUT 1,AX         ;imprima el valor sobre el que esta iterando
MULF F10         ;l^2, x = l, luego f(x) = l*l*a+l*b+c
MULF F00         ;a*l^2
STF E00          
LDF F10          ;l
MULF F02         ;b*l
STF E02
LDF F04          ;c
STF E04
ADDF E00         ;c+a*l^2
ADDF E02         ;c+b*l+a*l^2
MSG "f(x) = "
OUT 1,AX
LDF F10          ;l
ADDF FC1         ;l+1.0
STF F10          ;l <- l+1.0
JMP 30           ;reinicie el ciclo



#150

LDF F00    ;cargue a
MULF FCD   ; 2*a
STF B10

LDF F02   ;b
MULF F02  ;b^2
STF B00
LDF F00   ;a
MULF F04  ;a*c
MULF FC4  ;4*a*c
STF B02
LDF B00   ;b^2
SUBF B02  ;b^2-4*a*c
STF B04
LDF F02   ;b
SUBF F02  ;0
SUBF F02  ;-b
STF B08
DIVF B10  ;-b/2*a
STF B12
LDF B04   ;b^2-4*a*c
JMP 200   ;calcule la raiz


;X = (-B +- SQRT(B*B - 4*A*C))/(2*A)



;newtons method
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
LDF FCD      ;cargo 2.0
MULF A00     ;lo multiplico por x
STF A08      ;f'(xi)
LDF A06      ;f
DIVF A08     ;f/f'
STF A10
LDF A00      ;xi
SUBF A10     ;xi - f/f'
STF A00
MOV CX,FF5
DEC CX
MOV FF5,CX
LOOP 203

STF B06
DIVF B10      ;raiz/(2*a)
STF B14
MSG "The set of roots of the function in the interval is {"
LDF B12       ;-b/(2a)
SUBF B14      ;-b/(2a) - raiz/(2a)
STF AB2
SUBF F14      ;le resta l
JME 250       ;si es menor no esta en el intervalo, mire la otra raiz
LDF AB2       ;vuelva a cargar la raiz
SUBF F12      ;le resta r
JMA 250       ;si es mayor no esta en el intervalo
LDF AB2
OUT 1,AX
LDA AB0       ;cuenta de las raices
ADD FB1
STA AB0
JMP 250

#250
LDF B12      ;-b/(2a)
ADDF B14     ;-b/(2a) + raiz/(2a)
STF AB2      ;similar al anaterior analisis, si no esta salta al final      
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
















