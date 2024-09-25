#ifndef CANDIDATOS_H
#define CANDIDATOS_H

//Cambiar como se mandan a llamar las funciones
#include "MyRTC.h"
#include "MQTT.h"
#include "JSON.h"
#include "MicroSD.h"

class CandidatoController {
  private:
    
    // byte* iconos[3] = { MonegraIcon, BolilloIcon, PRIncessIcon };
    String candidatos[3] = { "Monegra", "Bolillo", "PRIncess" };
    int8_t posElegida = -1;
    const char* votante;

  public:
    // byte** getIconos ( void );
    int8_t getPos( void );
    void setVotante( const char* );
    String elegirCandidato ( bool );
    void aceptarEleccion ( void );

};

// byte** CandidatoController :: getIconos( void ){
//   return iconos;
// }
int8_t CandidatoController :: getPos( void ){
  return posElegida;
}
void CandidatoController :: setVotante( const char* uid ){
  votante = uid;
}
/**
  @param bool direccion: true (direccion a la derecha) | false (direccion a la izquierda)
  -Si se encuentra en el ultimo candidato y se elije ir al siguiente candidato, regresa el primer candidato
  -Al igual que si se encuentra en el primer candidato y se quiere retroceder, regresa el último candidato

*/
String CandidatoController :: elegirCandidato( bool direccion ){
  if (direccion) {
    posElegida = (posElegida + 1) % 3; // Avanzar al siguiente candidato circularmente
  } else {
    posElegida = (posElegida - 1 + 3) % 3; // Retroceder circularmente, evitando números negativos
  }
  
  return candidatos[posElegida];
}

void CandidatoController :: aceptarEleccion ( void ){
  DynamicJsonDocument jsonDATA ( 1024 );
  String jsonString = "";
  // int16_t votante= random(1000) + 1;
  //tasksAdmin.tarea_RTC();
  DateTimeStruct myDateTime;
  myRTC.generate_time('-');
  myDateTime = myRTC.getDateTimeRTC();
  JSON_fac.setData( myDateTime.date, myDateTime.time, candidatos[posElegida], votante );
  jsonDATA = JSON_fac.make_json();
  serializeJson( jsonDATA, jsonString );

  myMQTT.reconnect_MQTT();
  myMQTT.publish_MQTT(jsonString);
  mySD.SetFileName(myDateTime.date);
  mySD.SaveFile(jsonDATA);
  mySD.ReadFile();

  posElegida = -1;
  votante = "";
}
#endif