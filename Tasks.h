#ifndef TASK_H
#define TASK_H


//TODO CHECAR COMO ACOMODAR EL LLAMADO DE LIBRERIAS
#include "Libraries.h"

/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/

#define TIEMPO1 1000                 // Constante para indicar 1 segundo (1000 ms).
#define TIEMPO2 2000                 // Constante para indicar 2 segundos (2000 ms).
#define TIEMPO3 3000                 // Constante para indicar 3 segundos (3000 ms).
#define TIEMPO_RTC 5000              // Constante para indicar tiempo para RTC
#define TIEMPO_LCD 4000



class millis_tasks {

  private:
    uint64_t tiempo_anterior_rtc = 0,
             tiempo_anterior_lcd = 0,
             tiempo_anterior_lcd2 = 0,
             tiempo_anterior_MsgExito = 0,
             tiempo_anterior_errorQR = 0,
             tiempo_actual = 0,     // Contador de tiempo que tendrá múltiplos de TIEMPO.
             contador_espera = 3;
  public:
    // void tarea_sonico( void );
    void tarea_RTC ( void );
    // bool tarea_LCD ( void );
    bool tarea_LCD2 ( void );
    bool tarea_mensajeConExito ( void );
    bool tarea_mensajeError( void );
    void actualizar_tareas ( void );  // Función que actualiza el conteo obtenido de la función "millis()".
 
};

/*
   Al arranque del sistema la variable "tiempo_anterior1" tendrá el valor de 0, 
   cuando "tiempo_actual" sea igual a "TIEMPO1" es decir cuando hayan pasado
   1000 ms, "tiempo_anterior" tomará el valor de "tiempo_actual", para que la
   diferencia entre ellos siempre se cumpla cuando pase el tiempo asignado en "TIEMPO1".
*/
  /*
      _____________________________________________
      | tiempo_actual | tiempo_anterior1 | TIEMPO1 |
      ----------------------------------------------
      |       0       |       0          |  1000   |
      ----------------------------------------------
      |       1       |       0          |  1000   |
      ----------------------------------------------
      |       2       |       0          |  1000   |
      ----------------------------------------------
      ----------------------------------------------
      |       3       |       0          |  1000   |
      ----------------------------------------------
      ----------------------------------------------
      | . . 1000      |       0          |  1000   |   Se cumple la condicional 1000 - 0 = 1000.
      ----------------------------------------------
      ----------------------------------------------
      |    10001      |       1000       |  1000   |
      ----------------------------------------------

  */



/*~~~~~~~~~~~~~~~~~~~~~~~~ tareaRTC - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
// void millis_tasks :: tarea_RTC ( void ) {

  // if ( ( tiempo_actual - tiempo_anterior_rtc ) >= TIEMPO_RTC ){

  //   myRTC.cleanPointer_time(pointerTiempo);
  //   myRTC.get_time();
  //   myDateTime = myRTC.show_time('-');
  //   tiempo_anterior_rtc = tiempo_actual;

  // }
  
// }

/*~~~~~~~~~~~~~~~~~~~~~~~~ tareaRTC - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
// bool millis_tasks :: tarea_LCD ( void ) {
//   bool flag = false;
//   if ( ( tiempo_actual - tiempo_anterior_lcd) >= TIEMPO_LCD ){

//     //myRTC.cleanPointer_time(pointerTiempo);
//     myActu.lcd_clear();
//     myRTC.get_time();
//     myDateTime = myRTC.show_time('-');
//     myActu.print(myDateTime.fecha, 0);
//     myActu.print(myDateTime.tiempo, 1);
//     tiempo_anterior_lcd = tiempo_actual;
//     flag = true;
//   }
//   return flag;
// }
// void millis_tasks :: tarea_sonico( void ){
//   actualizar_tareas();

//   if((tiempo_actual - tiempo_anterior_sonico) >= TIEMPO1 ){
//     mySonico.leerDistancia();
//     mySonico.detectarVotante();
//     tiempo_actual = 0;
//   }
// }
/*~~~~~~~~~~~~~~~~~~~~~~~~ tareaRTC - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
bool millis_tasks :: tarea_LCD2 ( void ) {
  actualizar_tareas();
  if ( contador_espera > 0 && ( tiempo_actual - tiempo_anterior_lcd2) >= TIEMPO1 ){

    myActu.lcd_clear();
    myActu.print(String(contador_espera), 0);
    tiempo_anterior_lcd2 = tiempo_actual;
    contador_espera--;

  }else if( !contador_espera ){

    contador_espera = 3;
    tiempo_actual = 0;
    return true;
    
  }

  return false;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~ tareaRTC - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
bool millis_tasks :: tarea_mensajeConExito ( void ) {
  actualizar_tareas();
  if( contador_espera >= 0 && ( tiempo_actual - tiempo_anterior_MsgExito) >= TIEMPO3 ){
    
    tiempo_anterior_MsgExito = tiempo_actual;
    contador_espera--;

  }else if( !contador_espera ){

    contador_espera = 3;
    tiempo_actual = 0;
    return true;

  }
  return false;

}

bool millis_tasks :: tarea_mensajeError ( void ) {
  actualizar_tareas();
  if( contador_espera >= 0 && ( tiempo_actual - tiempo_anterior_errorQR) >= TIEMPO1 ){
    
    tiempo_anterior_MsgExito = tiempo_actual;
    contador_espera--;

  }else if( !contador_espera ){

    contador_espera = 3;
    tiempo_actual = 0;
    return true;

  }
  return false;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {

  tiempo_actual = millis( );

}

#endif