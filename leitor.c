#include <string.h>
#include <stdio.h>

struct Eletro
{
    //os teus campos
};

struct Eletro eletro[100];

int main()
{
   const char s[2] = ",";
   char *token;
   char linha[90];
   char *result;

   FILE *arq;
   if((arq = fopen("lista-musicas.txt", "r")) == NULL)
   {
       printf("Erro ao abrir o arquivo.\n");
   }
   token = strtok(arq, s);

   int i = 0;
   while (!feof(arq) && i<1) //para garantir que não passa do tamanho da lista.
   {
      result = fgets(linha, 90, arq);

      if (result) {
		// Printando o nome da música  
        token = strtok(result, s);
		printf( " %s\n", token );

		// Printando o nome do autor
		token = strtok(NULL, s);
		printf( " %s\n", token );

		//  Printando a duração da música
        token = strtok(NULL, s);
		printf( " %s\n", token );

		// Printando o gênero da música
		token = strtok(NULL, s);
		printf( " %s\n", token );
      }
      //passas aqui para o próximo elemento da tua lista.
      i++;
  }
  fclose(arq);

  return(0);
}