#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100 // Limite maximo de alunos

typedef struct {
    int matricula;
    char nome[50];
    float media_final;
} Aluno;

// Incluir alunos pré-definidos na inicialização
void inicializar_alunos(Aluno alunos[], int *quantidade) {
    Aluno lista_inicial[20] = {
        {516384, "Luiz Eduardo", 9.00},
        {552568, "Carlos Jeferson", 9.00},
        {516387, "Francisco Igo", 8.00},
        {552728, "Atila Calisto", 8.00},
        {508627, "Antonio Miguel", 7.00},
        {516383, "Marcos Lucas", 5.00},
        {504021, "Maria Clara", 8.50},
        {523675, "Ana Beatriz", 7.80},
        {518943, "Joao Pedro", 6.70},
        {512345, "Lucas Silva", 8.30},
        {529874, "Fernando Oliveira", 9.10},
        {522145, "Paulo Vitor", 7.00},
        {517234, "Juliana Santos", 8.80},
        {514879, "Roberto Souza", 6.90},
        {526789, "Matheus Lima", 7.50},
        {511234, "Patricia Andrade", 6.80},
        {520987, "Camila Costa", 7.60},
        {515679, "Gustavo Nogueira", 9.20},
        {521564, "Sara Mendes", 8.90},
        {530123, "Diego Carvalho", 7.40}
    };

    for (int i = 0; i < 20; i++) {
        alunos[i] = lista_inicial[i];
    }
    *quantidade = 20;
}

// Incluir um novo aluno
void incluir_aluno(Aluno alunos[], int *quantidade) {
    if (*quantidade >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo_aluno;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &novo_aluno.matricula);
    
    // Verificar se matricula ja existe
    for (int i = 0; i < *quantidade; i++) {
        if (alunos[i].matricula == novo_aluno.matricula) {
            printf("Matricula ja cadastrada.\n");
            return;
        }
    }

    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno.nome);  // Leitura de string com espacos
    printf("Digite a media final do aluno: ");
    scanf("%f", &novo_aluno.media_final);

    alunos[*quantidade] = novo_aluno;
    (*quantidade)++;
}

// Funcao para remover aluno por matricula
void remover_aluno(Aluno alunos[], int *quantidade, int matricula) {
    for (int i = 0; i < *quantidade; i++) {
        if (alunos[i].matricula == matricula) {
            for (int j = i; j < *quantidade - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*quantidade)--;
            printf("Aluno removido com sucesso.\n");
            return;
        }
    }
    printf("Aluno com matricula %d nao encontrado.\n", matricula);
}

void selection_sort_media(Aluno alunos[], int n, int indice);
void selection_sort_matricula(Aluno alunos[], int n, int indice);

// Listar alunos e ordenar
void listar_alunos(Aluno alunos[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int opcao_ordenacao;
    printf("Escolha a ordenacao:\n");
    printf("1. Ordenar por matricula\n");
    printf("2. Ordenar por media final\n");
    printf("Opcao: ");
    scanf("%d", &opcao_ordenacao);

    if (opcao_ordenacao == 1) {
        selection_sort_matricula(alunos, quantidade, 0);
    } else if (opcao_ordenacao == 2) {
        selection_sort_media(alunos, quantidade, 0);
    } else {
        printf("Opcao invalida.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Matricula: %d, Nome: %s, Media Final: %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].media_final);
    }
}

void selection_sort_media(Aluno alunos[], int n, int indice) {
    if (indice == n - 1) return;

    int maior = indice;
    for (int j = indice + 1; j < n; j++) {
        if (alunos[j].media_final > alunos[maior].media_final) {
            maior = j;
        }
    }
    
    Aluno temp = alunos[indice];
    alunos[indice] = alunos[maior];
    alunos[maior] = temp;

    selection_sort_media(alunos, n, indice + 1);
}

void selection_sort_matricula(Aluno alunos[], int n, int indice) {
    if (indice == n - 1) return;

    int menor = indice;
    for (int j = indice + 1; j < n; j++) {
        if (alunos[j].matricula < alunos[menor].matricula) {
            menor = j;
        }
    }
    
    Aluno temp = alunos[indice];
    alunos[indice] = alunos[menor];
    alunos[menor] = temp;

    selection_sort_matricula(alunos, n, indice + 1);
}

// Busca binaria por matricula
int busca_binaria(Aluno alunos[], int matricula, int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }

    int meio = (inicio + fim) / 2;

    if (alunos[meio].matricula == matricula) {
        return meio;
    } else if (alunos[meio].matricula > matricula) {
        return busca_binaria(alunos, matricula, inicio, meio - 1);
    } else {
        return busca_binaria(alunos, matricula, meio + 1, fim);
    }
}

// Menu interativo
int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidade = 0;
    int opcao, matricula, indice;

    // Inicializa a lista de alunos
    inicializar_alunos(alunos, &quantidade);

    do {
        printf("\nMenu:\n");
        printf("1. Incluir aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Listar alunos\n");
        printf("4. Buscar aluno por matricula\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluir_aluno(alunos, &quantidade);
                break;
            case 2:
                printf("Digite a matricula do aluno a remover: ");
                scanf("%d", &matricula);
                remover_aluno(alunos, &quantidade, matricula);
                break;
            case 3:
                listar_alunos(alunos, quantidade);
                break;
            case 4:
                printf("Digite a matricula do aluno a buscar: ");
                scanf("%d", &matricula);
                selection_sort_matricula(alunos, quantidade, 0); // Garantir que esta ordenado
                indice = busca_binaria(alunos, matricula, 0, quantidade - 1);
                if (indice == -1) {
                    printf("Aluno nao encontrado.\n");
                } else {
                    printf("Aluno encontrado: Matricula: %d, Nome: %s, Media Final: %.2f\n", alunos[indice].matricula, alunos[indice].nome, alunos[indice].media_final);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
