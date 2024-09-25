#ifndef QR_H
#define QR_H

#include <HardwareSerial.h>
#include <ArduinoJson.h>

#define RX2_PIN 16
#define TX2_PIN 17

class QR
{
  private:
    const char* desencriptarQr( String );

  public:
    void prenderQr( void );
    void apagarQr( void );
    const char* leerQr( void );
    
};

void QR :: prenderQr()
{
  //TODO: Agregar el comando para indicar al sensor que se prenda
}

void QR :: apagarQr()
{
  //TODO: Agregar comando para indicar al sensor que se apague
}

const char* QR :: leerQr()
{
  while( !Serial2.available() )
  {
    if(Serial2.available() > 0)
    {
      String QrString = Serial2.readString();
      Serial.println("Data received from UART2: " + QrString);

      const char* idElector = desencriptarQr(QrString); //Retorna el json Qr desencriptado
      //TODO: Mandarlo a Tasks.h para combinarlo con respuestas al lcd
      // if(idElector == "-1")
      // {
      //   continue;
      // }

      return idElector;

    }
  }
}

const char* QR :: desencriptarQr(String encryptedQr)
{
  // Declara un objeto DynamicJsonDocument
  DynamicJsonDocument decryptJson(1024);
  // Declara una variable para almacenar el error de deserialización
  DeserializationError error = deserializeJson(decryptJson, encryptedQr);

  
  // Verifica si ocurrió un error durante la deserialización
  if (error || !decryptJson.containsKey("id_votante")) {
      Serial.println("Error al deserializar JSON:");
      Serial.println(error.c_str());
      return "-1"; // Retorna nullptr si no es un JSON válido
  }

  const char* idElector = decryptJson["id_votante"];
  Serial.print("Este es el id: ");
  Serial.println(idElector);
  
  return idElector;

}

#endif