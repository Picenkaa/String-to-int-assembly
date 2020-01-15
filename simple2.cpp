#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    __declspec(align(16)) float arrVal1[4], * pVal1(arrVal1);
    __declspec(align(16)) float arrVal2[4], * pVal2(arrVal2);
    __declspec(align(16)) int   arrVal3[4], * pVal3(arrVal3);

    ofstream rf("Pitagoro_skaiciai.txt");

    for (float i = 1; i <= 1000; i += 4)
    {
        for (int k = 0; k < 4; k++) arrVal1[k] = i + k;

        for (float j = i + 1; j <= 1000; j++)
        {
            for (int k = 0; k < 4; k++) arrVal2[k] = j + k;

            __asm
            {
                // perkeliame pirmasias 4 reiksmes i registra xmm0
                mov         eax, pVal1
                movaps      xmm0, [eax]

                // perkeliame antrasias 4 reiksmes i registra xmm1
                mov         eax, pVal2
                movaps      xmm1, [eax]

                // perkeliame xmm0 i xmm2 ir rezultata pakeliame kvadratu
                movaps      xmm2, xmm0
                mulps       xmm2, xmm2

                // perkeliame xmm1 i xmm3 ir rezultata pakeliame kvadratu
                movaps      xmm3, xmm1
                mulps       xmm3, xmm3

                // gautu kvadratu suma perkeliame i registra xmm4
                movaps      xmm4, xmm2
                addps       xmm4, xmm3

                // istraukiame sakni is kvadratu sumos ir rezultata issaugome i xmm5
                sqrtps      xmm5, xmm4

                // gauta rezultata paverciam integer tipu tam, kad atmestume trupmenine dali
                cvttps2dq   xmm5, xmm5

                // perkeliam gautus sveikuosius skaicius i masyva arrVal3 (i kuri rodo pVal3) spausdinimui
                mov         eax, pVal3
                movdqa[eax], xmm5

                // gauta rezultata vel atverciam i float tipa, kad galetume atlikti veiksmus
                cvtdq2ps    xmm5, xmm5

                // pakeliame rezultata kvadratu
                mulps       xmm5, xmm5

                // paskaiciuojame skirtuma tarp xmm5 ir xmm4, gauta rezultata issaugome i xmm5
                subps       xmm5, xmm4

                // gauta rezultata velesniam apdorojimui perkeliame i arrVal2 (i kuri rodo pVal2)
                mov         eax, pVal2
                movaps[eax], xmm5
            }

            for (int k = 0; k < 4; k++)
            {
                // isvedame i faila tik tuos skaiciu trejetus, kur gautas xmm ir xmm4 skirtumas buvo 0
                if (arrVal2[k] == 0)
                {
                    rf << i + k << " " << j + k << " " << arrVal3[k] << '\n';
                }
            }
        }
    }

    printf("Rezultatas atspausdintas faile Pitagoro_skaiciai.txt.\n");

    return 0;
}