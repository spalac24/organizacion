#include <cstdio>
#include <string>

using namespace std;


int main () {

	int flag = 0;
	float f1,f2;
	f1 = 10.0;
	f2 = 9.0;
	__asm__(
		"flds %[f1];"
		"flds %[f2];"
		"fcomi;"
		"jb leb;"
	        "mov $3, %[flag];"
		"jmp end;"
		"leb:"
		"mov $5, %[flag];"
		"end:"
		:[flag]"+g"(flag):[f1]"m"(f1), [f2]"m"(f2));
	printf("%d\n",flag);
}
