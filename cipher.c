#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

int encrypt(char key[32]){
    char input[100];
    char matrix[10][10];
    int x,y;
    int flag = 1;
    int size,j=0;
    while(flag){
        printf("Inserta texto a encriptar (Maximo 100 caracteres)\n");
        fgets(input,100,stdin);
        //scanf("%s", input);
        size = strlen(input);
        if(size > 100){
            printf("El texto no debe pasar de 100 caracteres (%d caracteres tecleados)\n", size);
        }
        else flag = 0;
    }
    uchar aux;
    //fill char with x for permutation
    //printf("\n%s %d\n", input,size);
    for (x = size-1; x < 100; x++){
       input[x]='x';
    }
    //printf("\n%d %s\n", size, input);
    for (int i = 0; i < 100; i++) //Substitucion
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
    int count=0;
    //Create matrix for permutation
    for(x=0;x<10;x++){
        for(y=0;y<10;y++){
            matrix[x][y] = input[count];
            //printf("%c ", matrix[x][y]);
            count++;
        }
        //printf("\n");
    }
    
    char auxRow[10];
    int auxKey;
    int auxFlag = 1;
    //Permutacion con llave
    for (int i = 0; i < 32; i++)
    {
        auxKey=key[i]%10;
        if(auxFlag){
            strncpy(auxRow, matrix[auxKey],10);
            strncpy(matrix[auxKey], matrix[1],10);
            strncpy(matrix[1], auxRow,10);
            auxFlag = 0;
        }
        else{
            for (int i2 = 0; i2 < 10; i2++)
            {
                auxRow[0] = matrix[auxKey][i2];
                matrix[auxKey][i2] = matrix[1][i2];
                matrix[1][i2] = auxRow[0];
            }
            
            auxFlag = 1;
        }
        
    }
    //Convertir matriz en string y poner los caracteres alreves
    count=99;
    for(x=0;x<10;x++){
        for(y=0;y<10;y++){
            input[count] = matrix[x][y];
            //printf("%c ", matrix[x][y]);
            count--;
        }
        //printf("\n");
    }
    printf("Encrypet message: %s\n", input);
    // Decrypt
    count=99;
    for(x=0;x<10;x++){
        for(y=0;y<10;y++){
            matrix[x][y] = input[count];
            //printf("%c ", matrix[x][y]);
            count--;
        }
        //printf("\n");
    }
    for (int i = 31; i > -1; i--)
    {
        auxKey=key[i]%10;
        if(!auxFlag){
            strncpy(auxRow, matrix[auxKey],10);
            strncpy(matrix[auxKey], matrix[1],10);
            strncpy(matrix[1], auxRow,10);
            auxFlag = 1;
        }
        else{
            for (int i2 = 0; i2 < 10; i2++)
            {
                auxRow[0] = matrix[auxKey][i2];
                matrix[auxKey][i2] = matrix[1][i2];
                matrix[1][i2] = auxRow[0];
            }
            
            auxFlag = 0;
        }
    }
    count=0;
    for(x=0;x<10;x++){
        for(y=0;y<10;y++){
            input[count]  = matrix[x][y];
            printf("%c ", matrix[x][y]);
            count++;
        }
        printf("\n");
    }
    j=0;
    for (int i = 0; i < 100; i++)
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