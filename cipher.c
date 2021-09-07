#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

int encrypt(char key[32]){
    char input[100];
    int flag = 1;
    int size,j=0;
    while(flag){
        printf("Inserta texto a encriptar (Maximo 100 caracteres)\n");
        fgets(input,100,stdin);
        //scanf("%s", input);
        size = strlen(key);
        if(size > 100){
            printf("El texto no debe pasar de 100 caracteres (%d caracteres tecleados)\n", size);
        }
        else flag = 0;
    }
    uchar aux;
    for (int i = 0; i < size; i++) //Substitucion
    {
        aux = input[i];
        aux = ~aux;  //Flipear los bits
        aux = aux ^ key[j];
        if(j==32){
            j=0;
        }
        else j++;
        input[i] = aux;
    }
    printf("%s\n", input);
    j=0;
    for (int i = 0; i < size; i++)
    {
        aux = input[i];
        aux = aux ^ key[j];
        aux = ~aux;  //Flipear los bits
        if(j==32){
            j=0;
        }
        else j++;
        input[i] = aux;
    }
    printf("%s\n", input);
}

int  getKey(char *key){
    int flag = 1;
    int size;
    while(flag){
        printf("Inserta llave (32 caracteres)\n");
        scanf("%s", key);
        size = strlen(key);
        if(size != 32){
            printf("La llave debe medir 32 caracteres (%d caracteres tecleados)\n", size);
        }
        else flag = 0;
    }
}



int main(int argc, char *argv[]){
    char key[32];
    int on = 1, in=0;
    getKey(key);
    while(on){
        printf("Menu\nLLave: %s\nTeclea un numero para la opcion que quieres usar\n 1. Encriptar\n 2. Desencriptar\n 3. Cambiar llave\n 4. Salir\n", key);
        scanf("%d%*c", &in);
        switch (in)
        {
        case 1:
            encrypt(key);
            break;
        case 2:
            //decrypt(key);
            break;
        case 3:
            getKey(key);
            break;
        case 4:
            on = 0;
            break;
        default:
            printf("Por favor teclea una respuesta valida\n");
            break;
        }
    }


    return 0;
}