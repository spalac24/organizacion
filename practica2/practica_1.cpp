#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main () {
	float a1,b1,c1,a2,b2,c2,sq;
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
		"fld %[ac];"
		"fld %[bb];"
		"fsubp;"
		"fsqrt;"
		"fstp %[sq];"
		: [sq]"+m"(sq),[bb]"=m"(bb),[ac]"=m"(ac),[den]"=m"(den),[mb]"=m"(mb):[a]"m"(a),[b]"m"(b),[c]"m"(c), [cua]"m"(c_4));
	printf ("-b is %f, b2 is %f, ac is %f, den is %f, sq is %f\n",mb,bb,ac,den,sq);
	float aabs;
	float r1,r2;
	int cr = -1;
	r1 = r2 = 0.0;
	__asm__(
		"fld %[a];"
		"fabs;"
		"fstp %[aabs];"
		"fld %[c_e];"
		"fld %[aabs];"
		"fcompi;"
		"jbe a0;"
		"ja an0;"
		"a0:"
		"fld %[c_e];"
		"fld %[b];"
		"fcompi;"
		"jbe ab0;"
		"ja a0bn0;"
		"ab0:"
		"fld %[c_e];"
		"fld %[c];"
		"fabs;"
		"fcompi;"
		"jbe equal;"
		"ja noroots;"
		"equal:"
	        "mov $3, %[cr];"
		"jmp end;"
		"noroots:"
		"mov $0, %[cr];"
		"a0bn0:"
		"fld %[b];"
		"fld %[c];"
		"fld %[c];"
		"fld %[c];"
		"fsubp;"
		"fsubp;"
		"fdivp;"
		"fstp %[r1];"
		"mov $1, %[cr];"
		"jmp end;"
		"an0:"
		"fld %[ac];"
		"fld %[bb];"
		"fcomi;"
		"jb ima;"
		"mov $2, %[cr];"
		"fld %[den];"
		"fld %[sq];"
		"fld %[mb];"
		"fsubp;"
		"fdivp;"
		"fstp %[r1];"
		"fld %[den];"
		"fld %[sq];"
		"fld %[mb];"
		"faddp;"
		"fdivp;"
		"fstp %[r2];"
		"fld %[c_e];"
		"fld %[r1];"
		"fld %[r2];"
		"fsubp;"
		"fabs;"
		"jbe oneroot;"
		"jmp end;"
		"oneroot:"
		"mov $1, %[cr];"
		"jmp end;"
		"ima:"
		"mov $0, %[cr];"
		"end:"
		: [cr]"+g"(cr),[aabs]"+m"(aabs), [r1]"+m"(r1), [r2]"+m"(r2) : [a]"m"(a), [b]"m"(b), [c]"m"(c), [c_e]"m"(c_e), [sq]"m"(sq), [bb]"m"(bb), [ac]"m"(ac), [mb]"m"(mb), [den]"m"(den));
	float lo,hi;
	lo = -10.0;
	hi = 10.0;
	switch(cr){
	case 0: printf("There are no intersections\n");
		break;
	case 1: printf("The only intersection is at x =  %f\n",r1);
		lo = r1-10.0;
		hi = r1+10.0;
		break;
	case 2: printf("The two intersections are at x = %f ,  and x = %f\n",r1,r2);
		lo = r1-10.0;
		hi = r2+10.0;
		break;
	case 3: printf("There are infinite intersections\n");
		break;
	default:
		printf("Unknown error\n");
		break;
	}
	
	freopen("in.txt","w",stdout);
	cout<<a1<<" "<<b1<<" "<<c1<<endl;
	cout<<a2<<" "<<b2<<" "<<c2<<endl;
	cout<<lo<<endl<<hi<<endl;
	system("python plotter.py < in.txt");
}
