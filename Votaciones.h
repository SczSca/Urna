#ifndef VOTACIONES_H
#define VOTACIONES_H


#include "RFID.h"

#include "Sonico.h"

#include "MQTT.h"

#include "JSON.h"

#include "Actuadores.h"
  Actuador myActu;

#include "MyRTC.h"
  
#include "Tasks.h"
  millis_tasks tasksAdmin;

#include "MicroSD.h"
  MyMicroSD mySD;

#include "Candidatos.h"
  CandidatoController candidatoController;

#include "QR.h"
  QR QrController;
  
#endif