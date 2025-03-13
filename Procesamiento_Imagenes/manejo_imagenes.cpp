#include "Image.h"
#include <iostream>
int main(){
    Image test("test.jpg"); //cogemos la imagen para analizar
    Image prueba = test; //hacemos copia del test
    for (int i=0; i< prueba.w*prueba.h*prueba.channels; i++){
        if(prueba.data[i]%2==0){
            prueba.data[i]=prueba.data[i]*100;
        } else{
            prueba.data[i]=prueba.data[i]*10;
        }
    }
    prueba.write("pruebita.png");
    printf("color de pixel: %d, %d, %d \n", prueba.data[27], prueba.data[28], prueba.data[29] );
    system("pause");
    return 0;
}