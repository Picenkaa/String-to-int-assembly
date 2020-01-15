#include <stdio.h>
#include <string.h>


int main(int argc, char** argv ) {

	int stringtoint=0;
	char* argv1 = argv[1];
int ilgis=0;

	if( argc < 2 ) {
		printf("No argument*/\n");
		return( 0 );
	}


	__asm { 

		push eax
		push ebx
		push ecx
		push edx

		mov ebx, 1  
		xor eax,eax                   
		mov ecx, argv1       
		dec ecx  
		xor edx,edx          				  
	  
		sloop:                                                           
		inc ecx
		mov al, byte ptr [ecx]                   
		sub al,48  
		mov [eax],al 
		imul eax,ebx
		add edx,eax
	        imul ebx,10
		cmp argv1,ecx
                je exit_loop
		jmp sloop

exit_loop:    
mov [stringtoint], edx
		pop ecx
		pop ebx
		pop eax
		pop edx
		
		
        

	};

	printf("integer of string is %s is %d\n", argv[1], stringtoint );

	return(0);
}
