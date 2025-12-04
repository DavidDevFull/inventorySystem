#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 // Definindo o número maximo de itens do nosso inventário.

typedef struct // Estrutura base dos nossos itens
{
   char name[30], type[20];
} Itens;

void listOfRegisteredItems(Itens *allItens) {
    printf("\nItens registrados no inventário:\n");
    for(int i = 0; i < MAX; i++) {
        if(strlen(allItens[i].name) > 0) { // Quando o comprimento for  > 0 irá listar 1 item.
            printf("Item %d: %s - %s\n", i + 1, allItens[i].name, allItens[i].type);
        }
    }
}

void itemRegistration(Itens *allItens) {
    int userRequest, i = 0;

    do {
        printf("\nRegistro de itens\n [1] - Arma\n [2] - Munição\n [3] - Cura\n [4] - Sair\n");
        scanf("%d", &userRequest); // Número digitado pelo usuário.

        if (userRequest >= 1 && userRequest <= 3 && i < MAX) { 
            printf("Digite o nome do item: ");
            scanf("%s", allItens[i].name);
            // Insere a categoria e o texto de acordo com a opção escolhida pelo usuário.
            if (userRequest == 1) strcpy(allItens[i].type, "Arma");
            if (userRequest == 2) strcpy(allItens[i].type, "Munição");
            if (userRequest == 3) strcpy(allItens[i].type, "Cura");
            listOfRegisteredItems(allItens);
            i++;
        } else if (i >= MAX) { // Caso seja maior não irá adicionar mais itens na lista.
            printf("\nInventário cheio! 🚫\n");
            break;
        }

    } while (userRequest != 4); // Caso seja igual a 4 ou diferente irá sair do loop.
}

void removeItemRegistration(Itens *allItens) {
    char nameToRemove[30];
    int found = 0;

    listOfRegisteredItems(allItens); // Lista todos os itens adicionados.

    printf("\nDigite o nome do item que deseja remover ❌: ");
    scanf("%s", nameToRemove); // Lê o valor digitado pelo usuário.

    for(int i = 0; i < MAX; i++) {

        if(strcmp(allItens[i].name, nameToRemove) == 0) {
            found = 1;

            // Desloca todos os próximos itens uma posição para trás
            for(int j = i; j < MAX - 1; j++) {
                allItens[j] = allItens[j + 1];
            }

            // Limpa o último item (agora duplicado)
            allItens[MAX - 1].name[0] = '\0';
            allItens[MAX - 1].type[0] = '\0';

            printf("\nItem removido com sucesso ✅\n");
            break;
        }
    }

    if(!found) {
        printf("\nItem não encontrado no inventário 🚫\n");
    }

    listOfRegisteredItems(allItens);
}

int main() {
    Itens *maxItens = malloc(MAX * sizeof(Itens)); // Alocação de memória com o tamanho de MAX.
    int userRequest = 0; // Número digitado pelo usuário.

    if(maxItens == NULL) {
        printf("Erro ao alocar memória!");
        return 1;
    }

    // Inicializa o inventário com strings vazias
    for(int i = 0; i < MAX; i++) { // '\0' marcar o fim de uma string.
        maxItens[i].name[0] = '\0'; 
        maxItens[i].type[0] = '\0';
    }

    do {
        printf("\n===== MENU DO INVENTÁRIO =====\n");
        printf("[1] - Adicionar itens ao inventário.\n");
        printf("[2] - Listar itens.\n");
        printf("[3] - Remover itens.\n");
        printf("[4] - Sair\n");
        printf("Escolha: ");
        scanf("%d", &userRequest);

        if(userRequest == 1) itemRegistration(maxItens);
        if(userRequest == 2) listOfRegisteredItems(maxItens);
        if(userRequest == 3) removeItemRegistration(maxItens);

    } while(userRequest != 4); 

    free(maxItens); // Limpa memória alocada.
    return 0;
}