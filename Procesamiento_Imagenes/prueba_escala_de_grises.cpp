#include "Image.h"
#include <iostream>
int main(){
    Image test("test.jpg");
    Image escala_grises = test;
    test.grayscale_promedio();
    test.write("escala_grises.png");
    printf("canales %d  \n", test.channels);
    //for (int i=0; i<test.size ; i++){
      //  printf("%d", test.data[i]);
    //}
    system("pause");
   
    return 0;
    
}