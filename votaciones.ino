#include "Votaciones.h"
#include "Libraries.h"

//pines del RFID aparecen en RFID.h
#define trigPin 16
#define echoPin 35
#define relayPin 13 //TODO asignar un pin adecuado
#define inicioBtnPin 25
#define izquierdaBtnPin 26
#define derechaBtnPin 33
#define cancelarBtnPin 34
#define aceptarBtnPin 15

  bool inicioFlag = false;
  bool izqFlag = false;
  bool derFlag = false;
  bool cancelFlag = false;
  bool acceptFlag = false;
  //Sonico mySonico(trigPin, echoPin, relayPin);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myMQTT.setup_WiFi ( );
  myMQTT.set_MQTT_server ( );
  myMQTT.set_MQTT_callback (  );
  myRTC.RTC_init();
  myActu.lcd_init();
  //TODO encontrar la falla y solucionarlo
  //Falló la inicialización
  //mySD.init();

  //SPI.begin(); // init SPI bus
  //rfid.PCD_Init(); // init MFRC522

  /** Setup del sonico*/
  pinMode( trigPin, OUTPUT);
  digitalWrite ( trigPin, LOW);
  pinMode( echoPin, INPUT );
  pinMode( relayPin, OUTPUT);

  pinMode( inicioBtnPin, INPUT );
  pinMode( izquierdaBtnPin, INPUT );
  pinMode( derechaBtnPin, INPUT );
  pinMode( cancelarBtnPin, INPUT );
  pinMode( aceptarBtnPin, INPUT );
  
  // byte** iconosCandidatos = candidatoController.getIconos();
  // int lengthIconos = sizeof(iconosCandidatos) / sizeof(iconosCandidatos[0]);


  // for(int i = 0; i < lengthIconos; i++){
  //   myActu.createCharacter( i, iconosCandidatos[i]);
  // }
  myActu.createCharacterTodos();
  // randomSeed(analogRead(0));
  // delete[] iconosCandidatos;
  // lengthIconos = 0;
}

void loop() {
  //TODO: cambiar el inicio por tarjeta RFC
  //inicioFlag = true;
  bool votacionFlag, inicioFlag = true;

  myActu.print("Acerque su", 0);
  myActu.print( "tarjeta", 1 );

  QrController.prenderQr();
  bool isElector = mySD.CheckElector(QrController.leerQr());

  //while(!myRC522.ReadRFID_NFC()){
    //ciclo que espera a que lea y obtenga la id de un rfid
      //mySonico.tarea_sonico();
  //}

  candidatoController.setVotante( "12345" );

  //myRC522.eraseUidString();
  while( inicioFlag ){// ciclo que espera que se eliga un candidato

    //LCD text
    myActu.lcd_clear();
    myActu.print("Use botones", 0);
    myActu.print("Izq | Der", 1);

    //declaration var
    String candidatoActual;
    int8_t posicionChar;

    while( votacionFlag ){//ciclo que espera respuesta de los botones
      //mySonico.tarea_sonico();

      int direccionFlag;
      bool izqBtn = digitalRead(izquierdaBtnPin);
      bool derBtn = digitalRead(derechaBtnPin);
      bool acceptBtn = digitalRead(aceptarBtnPin);
      bool cancelBtn = digitalRead(cancelarBtnPin);

      if (  izqBtn != derBtn ){ //si el estado de los botones es diferente, significa que uno fue presionado 
        Serial.println(derBtn);
        // Serial.println(izqBtn);

        direccionFlag = derBtn;
        candidatoActual = candidatoController.elegirCandidato( direccionFlag );
        posicionChar = candidatoController.getPos();

        myActu.lcd_clear();
        myActu.print(candidatoActual, 0);
        myActu.setCursor(0,1);
        myActu.printChar( posicionChar );
        //TODO terminar de implementar el icono de los partidos
        delay(300);
      }else if( acceptBtn ){
        myActu.lcd_clear();
        
        while( acceptBtn ){ //ciclo que permite imprimir un tiempo de espera
          if(tasksAdmin.tarea_LCD2()){
            break;
          }
        }
        myActu.lcd_clear();
        if(candidatoActual.isEmpty()){
          myActu.lcd_clear();
          myActu.print("Use botones", 0);
          myActu.print("Izq | Der", 1);
          continue;
        } 
        myActu.print("Eligio "+ candidatoActual,0);
        myActu.print("No  | Si", 1);
        while(1){//ciclo que espera la confirmación de la votación o cancelación
          //mySonico.tarea_sonico();

          acceptBtn = digitalRead(aceptarBtnPin);
          cancelBtn = digitalRead(cancelarBtnPin);
          if(acceptBtn){
            candidatoController.aceptarEleccion();//metodo que manda y guarda votacion
            myActu.lcd_clear();
            myActu.print("Votacion",0);
            myActu.print("con exito", 1);
            inicioFlag = false;//hace que el primer while se rompa
            break;
          }else if(cancelBtn)  break; //si se presiona cancelar, regresa al ciclo que espera la selección de un candidato
          
        }
      break;
    }
  }

  if( !inicioFlag ){
    while(!tasksAdmin.tarea_mensajeConExito()){ //ciclo que ejecuta un tiempo de espera donde no se recibe ninguna interacción

    }
    myActu.lcd_clear();
  }


  }
}
