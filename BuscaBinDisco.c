#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char const *argv[]){
	FILE *f;
	int beg, fin, hal, achei;
	int cont=0;
	long tam;
	if(argc!=2){
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	Endereco buffer;
	f = fopen("cep_ordenado_novo.dat", "r");
	beg = 0; 
	fseek(f, 0, SEEK_END); 
	tam = ftell(f); 
	rewind(f); 
	fin = (tam/sizeof(Endereco));
	printf("\n\nTamanho do arquivo total em bytes: %ld\nTamanho de cada registro: %ld\nQtd de registros: %d\n", tam, sizeof(Endereco), fin);  
	while (beg <= fin){
		cont=cont+1;
		hal = (fin+beg)/2; 
		fseek(f, hal * sizeof(Endereco), SEEK_SET); 
		fread(&buffer, sizeof(Endereco), 1, f); 
		if(strncmp(argv[1],buffer.cep, 8) == 0){ 
			achei = 0;
			printf("\n\nAchei.\nPosicao Atual: %ld\n", ftell(f));
		}else{ 
			if (strncmp(argv[1],buffer.cep, 8) < 0){
				fin = hal - 1;
			}else{
				beg = hal + 1;
			}
		}
		printf("\n\nQuantidade de comparações: %d\n",cont);
		if(achei != 0) printf("Não Achou o CEP desejado.\n");
	}
	fclose(f);
}
