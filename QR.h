#ifndef QR_H
#define QR_H

#include <HardwareSerial.h>
#include <ArduinoJson.h>

#define RX2_PIN 16
#define TX2_PIN 17

class QR
{
  private:
    HardwareSerial& _Serial2;
    DynamicJsonDocument desencriptarQr( String );

  public:
    QR() : _Serial2(Serial2)
    {
      _Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
    }
    void prenderQr( void );
    void apagarQr( void );
    DynamicJsonDocument leerQr( void );
    DynamicJsonDocument desencriptarQr( DynamicJsonDocument );
    
};

void QR :: prenderQr()
{
  //TODO: Agregar el comando para indicar al sensor que se prenda
}

void QR :: apagarQr()
{
  //TODO: Agregar comando para indicar al sensor que se apague
}

DynamicJsonDocument QR :: leerQr()
{
  bool isCorrectQr = false;
  while( !isCorrectQr )
  {
    if(_Serial2.available()) 
    {
      String QrString = _Serial2.readString();
      DynamicJsonDocument decryptQrJson = desencriptarQr(QrString); //Retorna el json Qr desencriptado
      //si el campo "validacion" tiene valor true, hacer algo
      if(decryptQrJson.containsKey("error"))
      {
        continue;
      }
      else if(decryptQrJson.containsKey("validacion") && decryptQrJson["validacion"] == true) //condicion para validar que sea un json con datos de INE
      {
        return decryptQrJson;
      }
      Serial.println("Data received from UART2: " + QrString);
    }
  }
}

DynamicJsonDocument QR :: desencriptarQr(DynamicJsonDocument encryptedQr)
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