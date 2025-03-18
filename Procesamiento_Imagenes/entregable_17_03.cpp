#include "Image.h"
#include <iostream>
int main(){
    Image planta("plant2.jpg");
    Image planta_usable = planta;
    printf("tamaño del vector para la imagen nueva: %d", planta_usable.w*planta_usable.h);
    Image planta_vectorizada(planta_usable.w,planta_usable.h,1); //creamos imagen donde se creará la nueva imagen binarizada solo detectando las hojas 

    for (int i = 0, j = 0; i < planta_usable.size; i += planta_usable.channels, j++){
        int  R = planta_usable.data[i];
        int  G = planta_usable.data[i+1];
        int  B = planta_usable.data[i+2];
        float ExG = 1.9 * G - R - B; //filtrado por exceso de verdes con un peso de 1.9
        if(ExG > 50){
            planta_vectorizada.data[j]=255;
        } else{
            planta_vectorizada.data[j]=0;
        }

    }

    planta_vectorizada.write("planta_generada2.png"); 
    
    system("pause");
    return 0;
}