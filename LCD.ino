void showMenu(){
  //Actualiza Modo, Cursor y Página
  antMode = Mode;                                     
  antCursor = Cursor;
  antmenuPage = menuPage;
  lcd.clear();        
                                                                                                                                  
  if (Mode!=2) showMenus();     //Si no estamos en Modo 2, muestra el menú
}


void pantalla(byte x, byte y, String texto){        //Muestra en pantalla el texto que le pasamos, en una posición determinada
  lcd.setCursor(x,y);
  lcd.print(texto);
}


void showMenus(){                                                         //Menú en pantalla
  pantalla(4, 0, "DROP CONTROLLER");
  for (int i=0;i<LCD_Util_Rows;i++){                                      //Muestra el texto de la tabla dependiendo en la página que estemos y teniendo en cuenta el número de líneas útiles del LCD
      if (i+(menuPage*LCD_Util_Rows)<MainMenuItems) pantalla(2,i+marginTop,MainMenu[i+(menuPage*LCD_Util_Rows)]);    
    } 

    //Posición de ">", dependiendo en qué modo estemos
    if (Mode == 0){                                      
      pantalla(0,Cursor, ">");
    } else {
      if (Mode == 1){                                 
        pantalla(13,Cursor, ">");
      }  
    }

    //Muestra unos valores diferentes según la página en la que estemos            
    switch (menuPage){                
      case 0:
        pantalla(14, 1, String(drop_1_size));
        pantalla(18,1,"ms");
        pantalla(14, 2, String(drop_2_size));
        pantalla(18,2,"ms");
        pantalla(14, 3, String(dropsDelay));
        pantalla(18,3,"ms");
      break;
      case 1:
        pantalla(14, 1, String(cameraDelay));
        pantalla(18,1,"ms");
        pantalla(14, 2, String(numPhotos));
        pantalla(18,2,"ms");
        pantalla(14, 3, String(drop_1_sum));
        pantalla(18,3,"ms");
      break;
      case 2:
        pantalla(14, 1, String(drop_2_sum));
        pantalla(18,1,"ms");
        pantalla(14, 2, String(dropsDelay_sum));
        pantalla(18,2,"ms");
        pantalla(14, 3, String(cameraDelay_sum));
        pantalla(18,3,"ms");
      break;
      case 3:
        pantalla(14, 1, String(delay_between_pictures/1000));
        pantalla(18,1,"s");
      break;
    }               
}



void showPhotosVal(byte n){                                                   //Saca en pantalla los valores de las fotos realizadas
  Mode = 2;                                                                   //Entramo en Modo 2
  lcd.clear();  
  int ii=n;
  for (int i=0;i<4;i++){
    if ((ii+i-1)<numPhotos){          
      lcd.setCursor(0,i);
      lcd.print(String(ii+i));                          
      lcd.print("> ");              
      lcd.print(String(((ii+i-1)*(drop_1_sum))+(drop_1_size_init)));          //Calcula los valores tomando como referencia el valor inicial, el incremento a realizar y el número de foto
      lcd.print("/");
      lcd.print(String(((ii+i-1)*(drop_2_sum))+(drop_2_size_init)));
      lcd.print("/");
      lcd.print(String(((ii+i-1)*(dropsDelay_sum))+(dropsDelay_init)));
      lcd.print("/");
      lcd.print(String(((ii+i-1)*(cameraDelay_sum))+(cameraDelay_init)));
      
    }
  }
    
}
