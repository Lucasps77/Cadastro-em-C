#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESSOAS 100

typedef struct {
    char nome[50];
    char dataNascimento[50];
    char cpf[12];
    char rg[10];
} Pessoa;

Pessoa pessoas[MAX_PESSOAS];
int numPessoas = 0;

int menu();
int cadastrarPessoa(Pessoa pessoas[], int *numPessoas);
int procurarPessoa(Pessoa pessoas[], int numPessoas);
int excluirPessoa(Pessoa pessoas[], int *numPessoas);
int verificarCpfCadastrado(Pessoa pessoas[], int numPessoas, const char *cpf);
int verificarRgCadastrado(Pessoa pessoas[], int numPessoas, const char *rg);
int sairDoPrograma();

int main() {
    menu();
    return 0;
}

int menu() {
    int opcao;

    printf("Escolha uma opção\n");
    printf("1 - Cadastrar uma Pessoa\n");
    printf("2 - Procurar um Cadastro\n");
    printf("3 - Excluir Cadastro\n");
    printf("4 - Sair\n");

    scanf("%d", &opcao);
    getchar(); 

    switch(opcao) {
        case 1:
            cadastrarPessoa(pessoas, &numPessoas);
            break;
        case 2:
            procurarPessoa(pessoas, numPessoas);
            break;
        case 3:
            excluirPessoa(pessoas, &numPessoas);
            break;
        case 4:
            sairDoPrograma();
            break;
        default:
            printf("Opção inválida\n");
            menu();
            break;
    }

    return 0;
}

int cadastrarPessoa(Pessoa pessoas[], int *numPessoas) {
    if (*numPessoas < MAX_PESSOAS) {
        char cpf[12];
        char rg[10];

        do {
            printf("Nome:\n");
            fgets(pessoas[*numPessoas].nome, 50, stdin);
            pessoas[*numPessoas].nome[strcspn(pessoas[*numPessoas].nome, "\n")] = 0;

            if (strlen(pessoas[*numPessoas].nome) == 0) {
                printf("Nome não pode estar vazio!\n");
            }
        } while (strlen(pessoas[*numPessoas].nome) == 0);

        do {
            printf("Data de Nascimento:\n");
            fgets(pessoas[*numPessoas].dataNascimento, 50, stdin);
            pessoas[*numPessoas].dataNascimento[strcspn(pessoas[*numPessoas].dataNascimento, "\n")] = 0;

            if (strlen(pessoas[*numPessoas].dataNascimento) == 0) {
                printf("Data de Nascimento não pode estar vazia!\n");
            }
        } while (strlen(pessoas[*numPessoas].dataNascimento) == 0);

        do {
            printf("CPF (11 dígitos):\n");
            fgets(cpf, 12, stdin);
            cpf[strcspn(cpf, "\n")] = 0;

            if (strlen(cpf) != 11) {
                printf("CPF inválido! Deve conter 11 dígitos.\n");
            } else if (verificarCpfCadastrado(pessoas, *numPessoas, cpf)) {
                printf("CPF já cadastrado\n");
            }
        } while (strlen(cpf) != 11 || verificarCpfCadastrado(pessoas, *numPessoas, cpf));

        strcpy(pessoas[*numPessoas].cpf, cpf);
        
        do {
            printf("RG (9 dígitos):\n");
            fgets(rg, 10, stdin);
            rg[strcspn(rg, "\n")] = 0;

            if (strlen(rg) != 9) {
                printf("RG inválido! Deve conter 9 dígitos.\n");
            } else if (verificarRgCadastrado(pessoas, *numPessoas, rg)) {
                printf("RG já cadastrado\n");
            }
        } while (strlen(rg) != 9 || verificarRgCadastrado(pessoas, *numPessoas, rg));

        strcpy(pessoas[*numPessoas].rg, rg);

        (*numPessoas)++;
        printf("Pessoa cadastrada com sucesso! Total de pessoas cadastradas: %d\n", *numPessoas);
    } else {
        printf("Limite de pessoas atingido\n");
    }

    menu();
    return *numPessoas;
}

int procurarPessoa(Pessoa pessoas[], int numPessoas) {
    char cpfBusca[12];
    int encontrado = 0;

    if (numPessoas == 0) {
        printf("Sem pessoas cadastradas\n");
        menu();
        return 0;
    }

    printf("Digite o CPF da pessoa que deseja procurar: ");
    fgets(cpfBusca, 12, stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = 0; 

    if (strlen(cpfBusca) != 11) {
        printf("CPF inválido! Deve conter 11 dígitos.\n");
    } else {
        for (int i = 0; i < numPessoas; i++) {
            if (strcmp(pessoas[i].cpf, cpfBusca) == 0) {
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", pessoas[i].nome);
                printf("Data de Nascimento: %s\n", pessoas[i].dataNascimento);
                printf("CPF: %s\n", pessoas[i].cpf);
                printf("RG: %s\n", pessoas[i].rg);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Pessoa não encontrada.\n");
        }
    }
    menu();
    return 0;
}

int excluirPessoa(Pessoa pessoas[], int *numPessoas) {
    char cpfExcluir[12];
    int encontrado = 0;

    if (*numPessoas == 0) {
        printf("Sem pessoas cadastradas\n");
        menu();
        return 0;
    }

    printf("Digite o CPF da pessoa que deseja excluir: ");
    fgets(cpfExcluir, 12, stdin);
    cpfExcluir[strcspn(cpfExcluir, "\n")] = 0; 

    if (strlen(cpfExcluir) != 11) {
        printf("CPF inválido! Deve conter 11 dígitos.\n");
        return 0;
    }


    for (int i = 0; i < *numPessoas; i++) {
        if (strcmp(pessoas[i].cpf, cpfExcluir) == 0) {
           
            for (int j = i; j < *numPessoas - 1; j++) {
                pessoas[j] = pessoas[j + 1];
            }
            (*numPessoas)--; 
            printf("Pessoa com CPF %s foi excluída com sucesso.\n", cpfExcluir);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pessoa com CPF %s não encontrada.\n", cpfExcluir);
    }

    menu();
    return 0;
}

int verificarCpfCadastrado(Pessoa pessoas[], int numPessoas, const char *cpf) {
    for (int i = 0; i < numPessoas; i++) {
        if (strcmp(pessoas[i].cpf, cpf) == 0) {
            return 1; 
        }
    }
    return 0;
}

int verificarRgCadastrado(Pessoa pessoas[], int numPessoas, const char *rg) {
    for (int i = 0; i < numPessoas; i++) {
        if (strcmp(pessoas[i].rg, rg) == 0) {
            return 1; 
        }
    }
    return 0;
}

int sairDoPrograma() {
    char opc[3];

    printf("Você tem certeza que gostaria de sair do cadastro? ");
    printf("Digite S(sim) para sair ou N(não) para continuar: ");
    scanf("%s", opc);
    getchar(); 

    if (strcmp(opc, "S") == 0 || strcmp(opc, "s") == 0 || strcmp(opc, "Sim") == 0 || strcmp(opc, "sim") == 0) {
        printf("Programa fechando...\n");
        exit(0);
    } else if (strcmp(opc, "N") == 0 || strcmp(opc, "n") == 0 || strcmp(opc, "Não") == 0 || strcmp(opc, "não") == 0) {
        printf("Continuando no programa...\n");
        menu();
    }
}
