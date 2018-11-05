/* Procedimento para abrir arquivo: modo de abertura
Objetivo: - Definir modo de abertura de um arquivo
*/
FILE* abreArquivo(char modo, char caminho[30])
{
	FILE *arquivo;
    	switch(modo)
	{
        	case 'g':
            		arquivo = fopen(caminho,"wt");
            		break;
        	case 'r':
            		arquivo = fopen(caminho,"rt");
            		break;
        	case 'a':
            		arquivo = fopen(caminho,"a");
            		break;
        	case 'l':
            		arquivo = fopen(caminho,"a+");
            		break;
    	}
    	if(arquivo == NULL)
	{      //Se houver algum erro, o ponteiro apontará para NULL
        	printf("Nao foi possivel abrir o arquivo\n");
        	exit(0);
    	}
    	return arquivo;
}
void fechaArquivo(FILE *arquivo)
{
	fclose(arquivo);
}
/* Procedimento para verificar se uma tabela existe
Objetivo: - Verificar se tabela existe
*/
int verificaTabelaExiste(char nome[30])
{
        char nome_prod[30];
        strcpy(nome_prod, nome);
        FILE *arquivo;
        arquivo= fopen(strcat(nome, ".frm"), "r");
        strcpy(nome, nome_prod);
        if(arquivo==NULL)
        {
                return 1;
        }else{
                fechaArquivo(arquivo);
		return 2;
        }
}
void tipoDado(char tipo_dado[7], int quant_campos, int i)
{
        while(1)
        {
                if(strcmp(tipo_dado,"int")==0)
                {
                        tipo[i]='i';
                }
                if(strcmp(tipo_dado,"string")==0)
                {
                        tipo[i]='s';
                }
                if(strcmp(tipo_dado,"double")==0)
                {
                        tipo[i]='d';
                }
                if(strcmp(tipo_dado,"float")==0)
                {
                        tipo[i]='f';
                }
                if(strcmp(tipo_dado,"char")==0)
                {
                        tipo[i]='c';
                }
                break;
        }
}


/* Procedimento para criar uma tabela
Objetivo: - Criar o arquivo de estrutura (<tabela>.frm) e o arquivo de dados (<tabela>.dat) 
Obs	: - A variavel nome_prod guarda o conteudo da variavel nome
*/
int criaTabela(char nome[30], char tipo[20])
{
	int verifica=verificaTabelaExiste(nome);
	if(verifica==2)
	{	
		printf("\nTabela existente, tente outro nome!\n");
		return 0;
	}else{	
		char nomeORIG[100];
		char nome_prod[30];
		char nome_campo[30];
		char nome_t[30];
		char tipo_dado[7];
		int i, n = 1;
		FILE *arquivo;
		FILE *arquivo1;
		FILE *arquivo2;

		strcpy(nomeORIG,nome);
		strcpy(nome_t,nome);
		
		strcpy(nome_prod, nome);
		arquivo = abreArquivo('a', strcat(nome, ".frm"));
		strcpy(nome, nome_prod);
		arquivo1 = abreArquivo('a', strcat(nome, ".dat"));
		strcpy(nome, nome_prod);
		arquivo2 = abreArquivo('a', strcat(nome, ".idx"));

		
		printf ("\nQuantidade de campos: ");
		scanf(" %d",&quant_campos);
		printf ("\n");
		printf ("Informe> ");
		
		for(i=0;i<quant_campos;i++)
		{
			if (n == 1)
			{
				printf("Chave Primaria: ");
				scanf("%s", nome_campo);
				strcpy(tipo_dado,"int");
				n++;
			}else{
				printf("         %do campo      : ", n);
				scanf("%s", nome_campo);
				printf("         Tipo (int/string/double/float/char) : ");
				scanf("%s", tipo_dado);
				n++;	
			}	 
			tipoDado(tipo_dado,quant_campos,i);
			fprintf(arquivo, "%s;%s\n", nome_campo,tipo_dado);
			fprintf(arquivo2, "%s;", nome_campo);
		}

		fechaArquivo(arquivo);
    		fechaArquivo(arquivo1);
    		fechaArquivo(arquivo2);
		criaListaTabelas(nome_t);
	}
	return 0;
}

/* Procedimento para criar arquivo com lista de tabelas (tabelas.itp)
Objetivo: - Criar um arquivo (tabelas.itp) que contenha a lista das tabelas do banco
*/
void criaListaTabelas(char nome[30])
{
	FILE *arquivo;
       	arquivo = abreArquivo('a', "tabelas.itp" );
       	fprintf(arquivo, "%s;\n", nome);
       	fechaArquivo(arquivo);
}



/* Procedimento para listar as tabelas do banco 
Objetivo: - Abrir o arquivo tabelas.itp e listar o seu conteúdo
Obs	: - A variável info1 guarda o conteúdo de cada linha do arquivo tabelas.itp
*/
void listaTabelas()
{
	FILE *arquivo;
        char info1[50];
	char * table;					
	arquivo = abreArquivo('l', "tabelas.itp" );
	printf ("\n");
        printf (" Tabela\n");
        printf (" -----------------------------\n");
	while (fgets (info1, sizeof (info1), arquivo) != NULL)
	{
		table = strtok (info1, ";");
		printf (" %s\n", table);
	}
	printf ("\n");
	fechaArquivo(arquivo);
}
