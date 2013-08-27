#include <cstdio>

int main () {
	float a1,b1,c1,a2,b2,c2;
	printf("por favor ingrese los coeficientes de las dos funciones\n");
	scanf("%f %f %f",&a1,&b1,&c1);
	scanf("%f %f %f",&a2,&b2,&c2);
	float a,b,c;
	__asm__ ("fld %[a1];"
		 "fld %[a2];"
		 "fsubp;"
		 "fstp %[a];"
		 "fld %[b1];"
		 "fld %[b2];"
		 "fsubp;"
		 "fstp %[b];"
		 "fld %[c1];"
		 "fld %[c2];"
		 "fsubp;"
		 "fstp %[c]"
		 : [a1]"+m"(a1), [b1]"+m"(b1), [c1]"+m"(c1), [a2]"+m"(a2), [b2]"+m"(b2), [c2]"+m"(c2):[a]"m"(a), [b]"m"(b), [c]"m"(c));
	printf("finding roots of: %f %f %f\n",a,b,c);

	float bb,ac,den,mb;
	__asm__(
		"fld %[b];"
		"fld %[b];"
		"fld %[b];"
		"faddp;"
		"fsubrp;"
		"fstp %[mb];"
		"fld %[b];"
		"fld %[b];"
		"fmulp;"
		"fstp %[bb];"
		"fld %[a];"
		"fld %[c];"
		"fmulp;"
		"fld1;"
		"fld1;"
		"fld1;"
		"fld1;"
		"faddp;"
		"faddp;"
		"faddp;"
		"fmulp;"
		"fstp %[ac];"
		"fld1;"
		"fld1;"
		"faddp;"
		"fld %[a];"
		"fmulp;"
		"fstp %[den]"
		: [a]"+m"(a),[b]"+m"(b),[c]"+m"(c),[bb]"+m"(bb),[ac]"+m"(ac),[den]"+m"(den),[mb]"+m"(mb));
	printf ("-b is %f, b2 is %f, ac is %f, den is %f\n",mb,bb,ac,den);
	
}
