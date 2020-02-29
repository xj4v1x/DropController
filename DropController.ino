
//                                                              xJ4V1x
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/ 
/*******************************************************************************************************************************************/ 
//                         ____                              ____                   _                    _   _               
//                        |  _ \   _ __    ___    _ __      / ___|   ___    _ __   | |_   _ __    ___   | | | |   ___   _ __               //
//                        | | | | | '__|  / _ \  | '_ \    | |      / _ \  | '_ \  | __| | '__|  / _ \  | | | |  / _ \ | '__|              //
//                        | |_| | | |    | (_) | | |_) |   | |___  | (_) | | | | | | |_  | |    | (_) | | | | | |  __/ | |                 //
//                        |____/  |_|     \___/  | .__/     \____|  \___/  |_| |_|  \__| |_|     \___/  |_| |_|  \___| |_|                 //
//                                                                                                                                         //   
//                                              ____    _           __  __           _                                                     //                                                 
//                                             / ___|  | |_   ____ |  \/  |   __ _  | | __   ___   _ __   ___                              //
//                                             \___ \  | __| |_  / | |\/| |  / _` | | |/ /  / _ \ | '__| / __|                             //
//                                              ___) | | |_   / /  | |  | | | (_| | |   <  |  __/ | |    \__ \                             //
//                                             |____/   \__| /___| |_|  |_|  \__,_| |_|\_\  \___| |_|    |___/                             //                                                               
//                                                                                                                                         //                                                                                        
/*******************************************************************************************************************************************/ 
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/

 
//----------------------LIBRERIAS----------------------------------
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

//-----------------------------------------------------------------

LiquidCrystal_I2C lcd(0x27,20,4);

//----------------------VARIABLES GLOBALES----------------------------------
RotaryEncoder encoder(8, 9);  //TAMBIEN PUEDEN IR EN A2 y A3
#define Boton 7               //BOTON DEL ENCODER
#define Valvula 5             //VALVULA
#define Camara 6              //CAMARA

//Número de filas y columnas de la pantalla
byte LCD_Rows = 4;
byte LCD_Cols = 20;
byte marginTop = 1;   //La primera línea no se usa porque es donde va la cabecera
byte LCD_Util_Rows = LCD_Rows-marginTop;   //Número de filas útiles

//Distintos modos para saber qué tiene que hacer el Rotary Encoder en cada situación
byte Mode = 0;                    //---------------------Mode = 0  -> Normal
                                 //----------------------Mode = 1  -> Cambiando los valores
                                 //----------------------Mode = 2  -> Viendo los valores de las últimas fotos                                 
byte antMode = 1;                //----------------------Posicion anterior de Mode, para controlar cambios en pantalla

//Para controlar en qué punto de la pantalla está el cursor ">"
byte Cursor = 1;                  //----------------------Posicion actual del Cursor
int antCursor = 1;               //----------------------Posicion anterior del Cursor, para controlar cambios en pantalla


//Para saber el número de elementos que tiene el menú
const byte MainMenuItems = 11;

//Los textos del menú
String MainMenu[MainMenuItems] = {                                          //Se pueden añadir más elementos al menú, habría que actualizar el valor de MainMenuItems y GO!!! siempre tiene que estar el último
                                "D1 SIZE",
                                "D2 SIZE",
                                "D1< >D2",
                                "D. CAMERA",
                                "PHOTOS",
                                "D1 SIZE +",
                                "D2  SIZE +",
                                "D1<  >D2 +",
                                "D.CAMERA +",
                                "D. FLASH",                                
                                "GO!!!"
};

String cursorText = ">";


//Diferentes páginas dentro del menú
int menuPage = 0;              //Salto de página en los menús
int antmenuPage = 1;
byte numberOfPages = 0;        //Número de páginas del menú, se calcula en Setup



//                                                                                                                          

//Valores iniciales
int drop_1_size_init = 30;      //Tamaño de la gota 1 en ms
int drop_2_size_init = 18;      //Tamaño de la gota 2 en ms
int dropsDelay_init = 52;       //Espacio de tiempo entre gota 1 y gota 2 en ms
int cameraDelay_init = 142;     //Tiempo de retardo del disparo de la cámara respecto a la gota 2 en ms
int numPhotos_init = 1;         //Número de fotos a realizar

//Pone los valores iniciales a las variables de trabajo
int drop_1_size = drop_1_size_init;
int drop_2_size = drop_2_size_init;
int dropsDelay = dropsDelay_init;
int cameraDelay = cameraDelay_init;
int numPhotos = numPhotos_init;

//Si se hacen varias fotos se puede elegir un incremento de cada valor entre foto, aquí se pone el valor inicial de este incremento, por defecto es 0
int drop_1_sum = 0;
int drop_2_sum = 0;
int dropsDelay_sum = 0;      
int cameraDelay_sum = 0;      

//Cuánto tiene que aumentar o disminuir cada valor por cada giro del Encoder
int sumPhotos = 5;  //Las fotos van de 5 en 5 
int sum = 5;        //El resto de valores sube de 5 en 5 
int resta = -1;      //y bajan de 1 en 1

//Tiempo de reposo entre foto y foto para dar tiempo a recargar los flashes
int delay_between_pictures = 2000;     
int delay_between_pictures_sum = 1000;

//Al terminar de hacer la secuencia de fotos muestra en pantalla los valores usados en cada foto, con esto se controla qué número de foto tiene que aparecer en pantalla
int showPhotosVal_first_element = 1;  

//Para calcular tiempo y no usar delay
unsigned long temp;
unsigned long temp_drop1;

void setup() { 
  Serial.begin(9600);                     
  pinMode(Boton, INPUT_PULLUP);           //Botón del Rotary Encoder  
  pinMode(Valvula, OUTPUT);               //Válvula
  pinMode(Camara, OUTPUT);                //Cámara

  lcd.init();                             //Inicia la pantalla
  lcd.backlight();                        //Activa la luz
  lcd.clear();                            //Limpia la pantalla  

  //Calculamos el número de páginas que va a tener en total el menú
  numberOfPages = (MainMenuItems/LCD_Util_Rows)-1; 
  if ((MainMenuItems%LCD_Util_Rows)>0) numberOfPages++;  
  
}


void loop() {   
  if ((Mode!=antMode) or (Cursor!=antCursor) or (menuPage!=antmenuPage)) showMenu();       //Si hay algún cambio de Modo, Cursor o Pantalla refresca el menú  
  checkButton();                                                                           //Comprueba los giros y/o pulsaciones del Rotary Encoder
}
