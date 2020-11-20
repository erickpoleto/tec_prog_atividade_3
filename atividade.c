#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[30];
    char birthdate[10];
    float payd;
} Client;

typedef struct {
    Client *pClient;
    int qtdClient;
    int lastInsertedPos;
    int size;
} ListClient;

static int INITIAL_SIZE=1;
static int CURR_SIZE=1;

//aloc && realoc memory
void CreateEmptyList(ListClient *listC);
void realocListSize(ListClient *listC);
//verify if vector is full
int verifySizeBefInsert(ListClient *listC);
//client func's
void insertClient(ListClient *listC, Client *client);
Client constructClient();
void listClients(ListClient *listC);
int removeClient(ListClient *listC, int pos);
int updateClientPaydAmount(ListClient *listC, float value, int pos);
int verifyPos(ListClient *listC, int pos);
int resetAllClientPaydAmount(ListClient *listC);
int showBestBuyer(ListClient *listC);
int showClientPaydAmount(ListClient *listC, int pos);
int chosePos();
int choseValue();

int main(void){
    ListClient listClient;
    CreateEmptyList(&listClient);

    int option = 0;
    while(option != 7){
        printf("1 - insert client\n");
        printf("2 - remove client\n");
        printf("3 - update client amount \n");
        printf("4 - reset client amount\n");
        printf("5 - show best buyer\n");
        printf("6 - show client amount\n");
        printf("7 - exit\n");
        printf("choose an option: ");
        scanf("%d", &option);

        if(option < 1 || option > 7){
            printf("invalid option");
            break;
        }

        Client client;
        int pos;
        float value;

        switch(option){
            case 1:
                client = constructClient();
                insertClient(&listClient, &client);
                break;
            case 2:
                listClients(&listClient);
                pos = chosePos();
                removeClient(&listClient, pos);
                break;
            case 3:
                listClients(&listClient);
                pos = chosePos();
                value = choseValue();
                updateClientPaydAmount(&listClient, value, pos);
                break;
            case 4:
                resetAllClientPaydAmount(&listClient);
                break;
            case 5:
                showBestBuyer(&listClient);
                break;
            case 6:
                listClients(&listClient);
                pos = chosePos();
                showClientPaydAmount(&listClient, pos);
                break;
        }
    }


}


int choseValue() {
    float value;
    printf("type a value: ");
    scanf("%f", &value);
    return value;
}

int chosePos() {
    int pos;
    printf("chose a position: ");
    scanf("%d", &pos);
    return pos;
}

int showClientPaydAmount(ListClient *listC, int pos) {
    int verifyPosResult = verifyPos(listC, pos);
    if(verifyPosResult != 0) {
        return -1;
    }

    printf("client payd amount: %f\n", (listC->pClient + pos)->payd);
    return 0;

}

int showBestBuyer(ListClient *listC){
    if(listC->qtdClient==0) {
        printf("list is empty\n");
        return -1;
    }
    int higherVal = 0;
    Client bestBuyer;
    for(int i =0; i < listC->qtdClient; i++) {
        if((listC->pClient+i)->payd > higherVal) {
            higherVal = (listC->pClient+i)->payd;
            strcpy(bestBuyer.name, (listC->pClient+i)->name);
            bestBuyer.payd = (listC->pClient+i)->payd;
        }
    }
    printf("%s -- %f\n", bestBuyer.name, bestBuyer.payd);
    return 0;
}

Client constructClient() {
    Client client;
    printf("name: ");
    scanf("%s", client.name);
    printf("birthdate: ");
    scanf("%s", client.birthdate);
    printf("payd amount: ");
    scanf("%f", &client.payd);
    return client;
}

void listClients(ListClient *listC) {
    printf("-------Client List-------\n");
    for(int i = 0; i < listC->qtdClient; i++) {
        printf("name: %s pos: %d\n", (listC->pClient + i)->name, i);
    }
}

int verifyPos(ListClient *listC, int pos) {
    if(listC->qtdClient==0) {
        printf("list is empty\n");
        return -1;
    }else if(pos >= listC->qtdClient) {
        printf("pos is greater than the number os clients\n");
        return -2;
    }else {
        return 0;
    }
}

int resetAllClientPaydAmount(ListClient *listC) {
    if(listC->qtdClient==0) {
        printf("list is empty\n");
        return -1;
    }
    for(int i=0; i < listC->qtdClient; i++) {
        (listC->pClient+i)->payd = 0;
    }
    printf("All Clients payd amount was reseted\n");
    return 0;
}

int updateClientPaydAmount(ListClient *listC, float value, int pos) {
    int verifyPosResult = verifyPos(listC, pos);
    if(verifyPosResult != 0) {
        return -1;
    }

    (listC->pClient + pos)->payd = value;
    printf("%f\n", (listC->pClient + pos)->payd);
    return 0;
}

int removeClient(ListClient *listC, int pos) {
    int verifyPosResult = verifyPos(listC, pos);
    if(verifyPosResult != 0) {
        return -1;
    }

    for(int i = pos; i < listC->qtdClient-1; i++) {
        memcpy((listC->pClient+i), (listC->pClient +i+1), sizeof(Client));
    }
    (listC->qtdClient)--;
    return 0;
}

void insertClient(ListClient *listC, Client *client) {
    int i;
    verifySizeBefInsert(listC);
    int pos = listC->lastInsertedPos;
    memcpy((listC->pClient + pos), client, sizeof(Client));

    listC->qtdClient++;
    listC->lastInsertedPos++;
}

int verifySizeBefInsert(ListClient *listC) {
    if((listC->qtdClient) == listC->size) {
        realocListSize(listC);
        return 1;
    }
    return 0;
}

void realocListSize(ListClient *listC) {
    listC->size = listC->size + 10;
    listC->pClient = (Client *)realloc(listC->pClient, (listC->size)*sizeof(Client));
}

void CreateEmptyList(ListClient *listC) {
    listC->size=10;
    listC->pClient = (Client *)malloc(listC->size*sizeof(Client));
    listC->qtdClient = 0;
    listC->lastInsertedPos = 0;
}
