#include <cstdio>

int main () {
	float a1,b1,c1,a2,b2,c2;
	float c_4,c_e;
	c_4 = 4.0;
	c_e = 1e-4;
	printf("por favor ingrese los coeficientes de las dos funciones\n");
	scanf("%f %f %f",&a1,&b1,&c1);
	scanf("%f %f %f",&a2,&b2,&c2);
	float a,b,c;
	__asm__ (
		 "fld %[a1];"
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
		 : [a1]"=m"(a1), [b1]"=m"(b1), [c1]"=m"(c1), [a2]"=m"(a2), [b2]"=m"(b2), [c2]"=m"(c2):[a]"m"(a), [b]"m"(b), [c]"m"(c));
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
		"fld %[cua];"
		"fmulp;"
		"fstp %[ac];"
		"fld1;"
		"fld1;"
		"faddp;"
		"fld %[a];"
		"fmulp;"
		"fstp %[den];"
		: [bb]"=m"(bb),[ac]"=m"(ac),[den]"=m"(den),[mb]"=m"(mb):[a]"m"(a),[b]"m"(b),[c]"m"(c), [cua]"m"(c_4));
	printf ("-b is %f, b2 is %f, ac is %f, den is %f\n",mb,bb,ac,den);
	float aabs;
	float dump;
	int tag;
	__asm__(
		"fld %[a];"
		"fabs;"
		"fstp %[aabs];"
		"fld %[aabs];"
		"fld %[c_e];"
		"fsubp;"
		"fstp %[dump];"
		"jbe menor;"
		"ja mayor;"
		"jmp fin;"
		"menor:"
		"mov $20,%[tag];"
		"jmp fin;"
		"mayor:"
		"mov $10,%[tag];"
		"jmp fin;"
		"fin:"
		: [dump]"=m"(dump),[aabs]"=m"(aabs), [tag]"=g"(tag) : [a]"m"(a), [c_e]"m"(c_e));
	printf("%d\n",tag);
	printf("%f %f %f\n",aabs,c_e,aabs-c_e);
}
