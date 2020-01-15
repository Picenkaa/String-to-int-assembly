#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	char* argv1 = argv[1];
	string name = argv[1];
	int ilgis = name.length();
	int res = 0;
	__asm {
		push eax
		push ebx
		push ecx
     
		mov ecx, argv1    
		dec ecx   

		for_loop:
			// elemneto nuskaitymas
			inc ecx
			mov al, byte ptr[ecx]

				mov ebx, ilgis 
				dec ebx

				// switchas
				cmp al, '0'
				je forend // nukelia i ciklo pabaiga kad nieko nedarytu toliau
				cmp al, '1'
				je var1
				cmp al, '2'
				je var2
				cmp al, '3'
				je var3
				cmp al, '4'
				je var4
				cmp al, '5'
				je var5
				cmp al, '6'
				je var6
				cmp al, '7'
				je var7
				cmp al, '8'
				je var8
				cmp al, '9'
				je var9
				// switcho pabaiga

				// pagal switcha priskiriama reiksme
				var1:
				mov eax, 1
				cmp eax, 1
				je cont
				var2:
				mov eax, 2
				cmp eax, 2
				je cont
				var3:
				mov eax, 3
				cmp eax, 3
				je cont
				var4:
				mov eax, 4
				cmp eax, 4
				je cont
				var5:
				mov eax, 5
				cmp eax, 5
				je cont
				var6:
				mov eax, 6
				cmp eax, 6
				je cont
				var7:
				mov eax, 7
				cmp eax, 7
				je cont
				var8:
				mov eax, 8
				cmp eax, 8
				je cont
				var9:
				mov eax, 9
				// priskiriamu reiksmiu pabaiga

				cont: // count skirtas switcho reiksmiu priskirimus
				cmp ilgis, 1 // kai ilgis buna 1 tada nereikia dauginti o tik prideti prie res
					je plius
				daugyba: // daugyba 10^(ilgis -1) 
				imul eax, 10 // vis padaugina is 10 kol ilgis nelygus 0
				dec ebx // sumazina ilgi
				cmp ebx, 0
					jg daugyba
				// daugybos paaiga
				plius: // elemento pridejimas jei ilgis 1 arba tiesiog islipus is daugybos, pridedama reiksme prie res
				add res, eax
			forend: // ciklo pabaiga
			dec ilgis
		cmp ilgis, 0
			je for_exit
			jg for_loop
		for_exit:
		pop ecx
		pop ebx
		pop eax
	};
	
	cout << res;
	return 0;
}