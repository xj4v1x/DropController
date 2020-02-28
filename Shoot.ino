void shootNow(){                                          //Modo Disparo
                                                          
                                                                                                                                  //Mode = 2;                                                     
  //Graba los valores de inicio para que después, cuando se vayan haciendo los incrementos (si los hay) no perdamos este dato                                                                                                                                  
  drop_1_size_init = drop_1_size;                         
  drop_2_size_init = drop_2_size;
  dropsDelay_init = dropsDelay;
  cameraDelay_init = cameraDelay;
  numPhotos_init = numPhotos;

  bool exit_for = false;                                //Para forzar la salida del for

  
  for (int i=1;i<=numPhotos;i++){                       //Secuencia de fotos
    lcd.clear();    
    pantalla(4, 0, "DROP CONTROLLER");     
    pantalla(1, 1, "SHOOTING");  
    pantalla(1, 2, String(i));  
    lcd.print ("/");  
    lcd.print (String(numPhotos));  
    pantalla(0, 3, String(drop_1_size));
    lcd.print("/");
    lcd.print(String(drop_2_size));
    lcd.print("/");
    lcd.print(String(dropsDelay));
    lcd.print("/");
    lcd.print(String(cameraDelay));
   
    digitalWrite(Valvula, HIGH);                //Abre la válvula   (GOTA 1)
    //No se usa delay para poder comprobar la pulsación del botón para salir del modo Disparo
    temp = millis();                            //En temp se graba el tiempo actual en ms          
    while (millis()<drop_1_size+temp){          //Mientras el tiempo actual AHORA MISMO sea menor al tiempo de espera (en este caso drop_1_size) + el tiempo antes de entrar en el while (temp)...
      if (!digitalRead(Boton)){                 //En cuanto pulsamos el botón, pone el valor true en exit_for y fuerza la salida del while
        exit_for = true;
        break;
      }
    }                       
    digitalWrite(Valvula, LOW);                 //Cierra la válvula

                                                //Pausa entre gotas
    temp = millis();
    while (millis()<dropsDelay+temp){
      if (!digitalRead(Boton)) {
        exit_for = true;
        break;
      }
    } 
          
    digitalWrite(Valvula, HIGH);                //Abre la válvula   (GOTA 2)
    temp = millis();
    while (millis()<drop_2_size+temp){
      if (!digitalRead(Boton)) {
        exit_for = true;
        break;
      }
    }       
    digitalWrite(Valvula, LOW);                 //Cierra la válvula    

    temp = millis();
    while (millis()<cameraDelay+temp){
      if (!digitalRead(Boton)) {
        exit_for = true;
        break;
      }
    }           
    //delay(cameraDelay);      
    
    digitalWrite(Camara, HIGH);                 //Activa el Optoacoplador (disparo de cámara)
    temp = millis();
    while (millis()<=50){
      if (!digitalRead(Boton)) {
        exit_for = true;
        break;
      }
    }     
    digitalWrite(Camara, LOW);                 //Desactiva el Optoacoplador (disparo de cámara)

    temp = millis();
    while (millis()<=delay_between_pictures+temp){
      if (!digitalRead(Boton)) {
        exit_for = true;
        break;
      }
    } 
    
    if (exit_for) break;                       //Si exit_for es true, porque se ha pulsado el botón, fuerza la salida del for
                                               //Suma los incrementos antes de la siguiente foto   
    drop_1_size+=drop_1_sum;
    drop_2_size+=drop_2_sum;
    dropsDelay+=dropsDelay_sum;
    cameraDelay+=cameraDelay_sum;         
  }
  delay (500);                                //Este delay asegura que no tenemos rebote con la pulsación del botón antes de pasar a la siguiente pantalla
  showPhotosVal(1);                           //Muestra en pantalla los valores de las fotos tomadas, pasamos el número de foto que queremos que aparezca en la primera línea
  while (Mode == 2){                          //Mientras sigamos en Modo 2 comprueba el Encoder
    checkButton();  
  }     

  //Vuelve a poner los valores al valor inicial que hemos usado antes de hacer la secuencia de fotos
  drop_1_size = drop_1_size_init;             
  drop_2_size = drop_2_size_init;
  dropsDelay = dropsDelay_init;
  cameraDelay = cameraDelay_init;
  numPhotos = numPhotos_init;

  //Volvemos a la página principal                                                                                              
  menuPage=0;
  Cursor=1;    
}
