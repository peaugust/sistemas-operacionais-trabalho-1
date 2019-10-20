#include <stdio.h>

void EsperaEnter()  // Definição da função "EsperaEnter"
{
    int tecla;
    printf("Pressione ENTER\n");
    do
    {
        tecla = getchar();
        if (tecla !=13) // Se nao for ENTER
        {
            printf("Digite ENTER\n");
        }
    } while(tecla != 13); // 13 e' o codigo ASCII do ENTER
}

void main()   
{
    EsperaEnter();      // Chamada da função definida antes
    // ...........
    EsperaEnter();      // Chamada da função definida antes
    // ...........
    EsperaEnter();      // Chamada da função definida antes  
}

