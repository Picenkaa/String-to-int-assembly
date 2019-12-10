#include <stdio.h>
#include <string.h>

int main(int argc, char** argv ) {

	int iLettersCount;
	char* argv1 = argv[1];

	if( argc < 2 ) {
		printf("Nepateiktas parametras*/\n");
		return( 0 );
	}


	__asm { 

		push eax
		push ebx
		push ecx

		mov ebx, 1                     
		mov ecx, argv1       /* Address of argv[1]            */ 
		mov edx, iLettersCount 
		dec ecx                /* loop increases ecx at start   */
							   /*so we decrease to compensate  */  
		sloop:                                                     
		inc ecx                /* ecx points to next char in string */
		mov al, byte ptr [ecx] /* byte of string to al          */                     
		sub al,'0'            /* skaicius              */ 
		imul al,ebx /* minus 48 is skaiciaus*/ 
		add edx,al/* dadedu int */ 
		imul ebx,10/*dauginu is 10 */ 
		dec ecx/* decreasu stringa*/ 
		cmp ecx,argv1/* copmaprinu */ 
		je exit_loop/* exitas*/ 
		jmp sloop/*else jump back */ 

exit_loop:    
mov [iLettersCount], edx
		pop ecx
		pop ebx
		pop eax
		pop edx
        

	};

	printf("integer of string is %s is %d\n", argv[1], iLettersCount );

	return(0);
}
