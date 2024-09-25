#ifndef VOTACIONES_H
#define VOTACIONES_H


// #include "RFID.h"

#include "Sonico.h"


#include "Actuadores.h"
  Actuador myActu;
  
#include "Tasks.h"
  millis_tasks tasksAdmin;

#include "Candidatos.h"
  CandidatoController candidatoController;

#include "QR.h"
  QR QrController;
  
#endif