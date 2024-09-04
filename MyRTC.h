#ifndef MYRTC_H
#define MYRTC_H
#include <Wire.h>               /* Librería para el uso del protocolo I2C. */

/*RTClib.h, requiere de la instalación de dos librerías:
RTClib: Permite el uso de varios relojes del fabricante Adafruit.
Adafruit BusIO: Es necesaria cargarla para configurar ciertos elementos de los componentes electrónicos de Adafruit.*/
#include "RTClib.h"
  RTC_DS1307 rtc;

struct DateTimeStruct {
  String date;
  String time;
};

class DS1307_RTC {
  
  private:
      uint8_t hour = 0, minute = 0, second = 0, day = 0, month = 0;
      uint16_t year = 0;
      String date = " ", time = " ";
      DateTimeStruct DateTimeRTC;
      
  public:
    DateTimeStruct getDateTimeRTC( void ) const;
    void RTC_init ( void );
    void get_time ( void );
    void format_date ( char );
    void format_time ( void ) ;
    // DateTime show_time ( char );
    void generate_time ( char );

  };
DateTimeStruct DS1307_RTC :: getDateTimeRTC ( void ) const {
  return DateTimeRTC;
} 

/* Función que configura lo necesario para que el reloj se inicialice */
void DS1307_RTC :: RTC_init ( void ) {

   while ( ! rtc.begin ( ) ) {                  /* Mientras que el reloj no se ha iniciado. */
    Serial.println ( F ( "Hay un error de reconocimiento del RTC, revisa conexiones y alimentación" ) );
    Serial.flush ( );                           /* Espera a que se transmita la información serial correctamente. */
    delay ( 3000 );
    //abort ( );
    
  }
  if ( ! rtc.isrunning ( ) ) {      /* Si el reloj no está ejecutándose*/

    Serial.println ( F ( "El reloj se está configurando con la date y hour de la computadora" ) );
    /*__DATE__ y __TIME__ Son macros que retornan la date y hour de la computadora.*/
    rtc.adjust( DateTime ( F ( __DATE__ ), F ( __TIME__ ) ) );      /* Función que ajusta automáticamente la date y hour. */
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));                  /* Función que ajusta manualmente la date y hour. */
    /* Esta instrucción solo debe usarse una sola vez, para que el reloj actualice la hour, una vez hecho esto, se puede comentar y volver a subir el código. */
    
  }
  }

/* Función que configura lo necesario para que el reloj se inicialice */
void DS1307_RTC::get_time ( void ) {

      DateTime now = rtc.now();
      second = now.second ( );
      minute = now.minute ( );
      hour = now.hour ( );
      day = now.day ( );
      month = now.month ( );
      year = now.year ( );
      
  }

/* Función que le da un formato legible a la date. */
void DS1307_RTC::format_date ( char specialChar ) {

  date = "";
    if ( day < 10 ) date += '0';
  date += day;
  date += specialChar;
    if ( month < 10 ) date += '0';
  date += month;
  date += specialChar;
  date += year;
  
}

/* Función que le da un formato legible al time. */
void DS1307_RTC::format_time ( void ) {

  time = "";
  if ( hour < 10 ) time += '0';
    time += hour;
    time += ':';
  
  if ( minute < 10 ) time += '0';
    time += minute;
    time += ':';

  if ( second < 10 ) time += '0';
    time += second;
   
}

/* Función que muestra en la consola serial la date y la hour. */
// DateTime DS1307_RTC :: show_time ( char specialChar ) {
//   DateTime myDateTimeRTC;
//   format_time ( );                    /* Dar formato al time */
//   Serial.print ( F ( "hour: " ) );
//   Serial.println ( time );
//   format_date ( specialChar );
//   Serial.print ( F ( "date: " ) );
//   delay(200);
//   Serial.println ( date );          /* Dar formato a la date */
//   myDateTimeRTC.date = date;
//   myDateTimeRTC.time = time; 
//   return myDateTimeRTC;
// }
/* Función que muestra en la consola serial la date y la hour. */
void DS1307_RTC :: generate_time ( char specialChar ) {
  get_time ( );
  format_time ( );                    /* Dar formato al time */
  // Serial.print ( F ( "hour: " ) );
  // Serial.println ( time );
  format_date ( specialChar );
  // Serial.print ( F ( "date: " ) );
  delay(200);
  // Serial.println ( date );          /* Dar formato a la date */
  DateTimeRTC.date = date;
  DateTimeRTC.time = time;
}

/*  Declaracion de obj RTC */
DS1307_RTC myRTC;
#endif