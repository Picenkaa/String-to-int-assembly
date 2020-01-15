#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 1) {
        cout << "no argument" << endl;
        return(0);
    }

    char* argv1 = argv[1];

    int rez=0;

    __asm {
        push eax
        push ebx
        push ecx

        xor eax, eax
        mov ecx, argv1
        dec ecx

        sloop :
            inc ecx
            movzx ebx, byte ptr[ecx] /* byte of string to ebx, zero extend   */
            cmp ebx, 0  /* compare to zero (string end ) */ 
            jz exit_loop /*Jump short if zero (ZF = 1) CF =0  if zero byte (string end) then exit  */
				         
            sub ebx, '0'
            add eax, ebx
            mul eax, 10
            jmp sloop
         exit_loop :
            div eax, 10
            mov rez, eax
            pop ecx 
            pop ebx
            pop eax
    }
    cout << "int: " << rez;
}