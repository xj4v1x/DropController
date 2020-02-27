
void checkButton(){                                 //----------------------CHEQUEA LOS BOTONES
  static int pos = 0;                               //Inicia la posición en un valor de 0
  encoder.tick();
  int newPos = encoder.getPosition();               //La nueva posición del Encoder
  if (pos != newPos) {                              //Si la posición ha cambiado 
    if (pos<newPos) RotateLeft();                   //Dependiendo si el valor es mayor o menor al valor de referencia (0) sabemos si el giro ha sido hacia la derecha o izquierda
    else RotateRight();                                                                    
    pos = newPos;                                                                                       
  }
  if (!digitalRead(Boton)){                         //Al ser PULLUP hay que preguntar "lo contrario"
    delay(250);
    OK_Button();
  }
}


void RotateLeft(){                             //Giro a la izquierda
            Serial.println(menuPage);

  switch (Mode){                               //Dependiendo del Modo en el que estemos....
    case 0:                                    //Mode 0 -> Normal / Pantalla de menú
      if (Cursor>=1) Cursor--;                 
      if (Cursor<1){                           //Si tenemos un Cursor menor de 1, lo cambia a valor 3 y retrocede una página del menú
        Cursor=LCD_Util_Rows;                         
        menuPage--;    
      }
      if (menuPage<0){                         //Si hemos llegado a la primera página tiene que calcular cuantas páginas tiene el menú en total para llevarnos a la última
        menuPage=numberOfPages;
        //menuPage=(MainMenuItems%LCD_Util_Rows)+2;    
        Cursor = MainMenuItems%LCD_Util_Rows;
        if ((MainMenuItems%LCD_Util_Rows)==0) Cursor=LCD_Util_Rows;
        if (Cursor==0) Cursor=1;
      }
    break;
    case 1:                                    //Mode 1 -> Cambiar valores / Pantalla de menú
      action(menuPage, Cursor, resta);        //Envía el número de página, la posición del Cursor para saber exactamente en qué punto del menú estamos, y el valor que hay que restar
    break;
    case 2:                                                                   //Mode 2 -> Pantalla que nos muestra los valores de las fotos que hemos hecho
      if (showPhotosVal_first_element>1) showPhotosVal_first_element -= 4;    
      showPhotosVal(showPhotosVal_first_element);
    break;
  }
}

void RotateRight(){                             //Giro a la derecha
  switch (Mode){                               //Dependiendo del Modo en el que estemos....
    case 0:                                    //Mode 0 -> Normal / Pantalla de menú
      if (Cursor<=LCD_Util_Rows) Cursor++;            
      if (Cursor>LCD_Util_Rows){              //Si tenemos un Cursor mayor de 3, lo cambia a valor 3 y avanza una página del menú
        Cursor=1;
        menuPage++;    
      }
      if (((menuPage*LCD_Util_Rows)+Cursor)>MainMenuItems){        //Si hemos llegado a la última página nos manda a la primera y coloca el Cursor en la primera posición
        menuPage = 0;    
        Cursor = 1;
      }
    break;
    case 1:                                    //Mode 1 -> Cambiar valores / Pantalla de menú
      action(menuPage, Cursor, sum);          //Envía el número de página, la posición del Cursor para saber exactamente en qué punto del menú estamos, y el valor que hay que sumar
    break;
    case 2:                                                                            //Mode 2 -> Pantalla que nos muestra los valores de las fotos que hemos hecho            
      if (showPhotosVal_first_element < numPhotos) showPhotosVal_first_element += 4;        
      showPhotosVal(showPhotosVal_first_element);      
    break;
  }
}


void OK_Button(){                                     //Pulsación del botón
  if (Mode == 0){
    if (menuPage*LCD_Util_Rows+Cursor == MainMenuItems) {
      shootNow();      
    } else Mode = 1;     
  } else Mode = 0;
}
