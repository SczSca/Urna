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
  DynamicJsonDocument doc(1024);

  // Deserializa el JSON
  DeserializationError error = deserializeJson(doc, encryptedQr);
  if (error) 
  {
    Serial.print(F("Error al deserializar: "));
    Serial.println(error.f_str());
    // Crear un documento vacío para devolver en caso de error
    DynamicJsonDocument errorDoc(1024);
    errorDoc["error"] = "Deserialización fallida";
    errorDoc["message"] = error.f_str();
    return errorDoc;
  }
  return doc;
}

#endif