void action(byte page, byte point, int valor){      
  switch(page){                                         //Según en qué página estemos....
    case 0:                                             //En página 0 (La primera)
      switch(point){                                    //Según donde esté el Cursor (Aquí es point)
        case 1:                                         //En la Primera línea
          drop_1_size+=valor;                           //Aumenta (o dismuye, según el valor recibido) el valor del tamaño de la gota 1
          if (drop_1_size<0) drop_1_size=0;
          pantalla(15, 1, String(drop_1_size));         //Actualiza en pantalla el nuevo valor         
        break;
        case 2:                                         //En la Segunda línea
          drop_2_size+=valor;                           //Aumenta (o dismuye, según el valor recibido) el valor del tamaño de la gota 2
          if (drop_2_size<0) drop_2_size=0;
          pantalla(15, 2, String(drop_2_size));  
        break; 
        case 3:                                         //En la Tercera línea
          dropsDelay+=valor;                            //Aumenta (o dismuye, según el valor recibido) el valor del tiempo entre gotas
          if (dropsDelay<0) dropsDelay=0;
          pantalla(15, 3, String(dropsDelay));           
        break;     
      }
    break;
    case 1:                                             //En la segunda página
      switch(point){
        case 1:          
          cameraDelay+=valor;                           //Aumenta (o dismuye, según el valor recibido) el valor del retardo de cámara
          if (cameraDelay<0) cameraDelay=0;
          pantalla(15, 1, String(cameraDelay));         
        break;
        case 2:                                         //Aumenta (o dismuye, según el valor recibido) el número de fotos
          if (valor>0) numPhotos+=sumPhotos;
          else numPhotos-=sumPhotos;
          if (numPhotos<1) numPhotos=1;
          if ((numPhotos>1) & (numPhotos%sumPhotos!=0)) numPhotos-=1;
          pantalla(15, 2, String(numPhotos));  
        break; 
        case 3:                                         //Incremento a realizar en el tamaño de la gota 1
          drop_1_sum+=valor;   
          if (dropsDelay_sum<0) dropsDelay_sum=0;
          pantalla(15, 3, String(dropsDelay_sum));           
        break;     
      }
    break;
    case 2:                                             //En la tercera página
      switch(point){
        case 1:                                         //Incremento a realizar en el tamaño de la gota 2          
          drop_2_sum+=valor;
          if (drop_2_sum<0) drop_2_sum=0;
          pantalla(15, 1, String(cameraDelay_sum));         
        break;
        case 2:                                         //Incremento a realizar en el tiempo entre gotas
          dropsDelay_sum+=valor;
          if (dropsDelay_sum<0) dropsDelay_sum=0;
          pantalla(15, 2, String(dropsDelay_sum));  
        break; 
        case 3:                                         //Incremento a realizar en el retardo de la cámara
          cameraDelay_sum+=valor;   
          if (cameraDelay_sum<0) cameraDelay_sum=0;
          pantalla(15, 3, String(cameraDelay_sum));           
        break;     
      }
    break;
    case 3:                                             //En la cuarta página
      switch (point){
        case 1:
          if (valor>0) delay_between_pictures += delay_between_pictures_sum;
          else delay_between_pictures -= delay_between_pictures_sum;
          if (delay_between_pictures<0) delay_between_pictures=0;
          pantalla(15, 1, String(delay_between_pictures/1000));         
        break;

      }
    break;
  }
  showMenu();                                     
}
