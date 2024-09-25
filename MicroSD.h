#ifndef MicroSD_h
#define MicroSD_h
/* Librerías fabricante necesarias para utilizar la MicroSD */
#include <SD.h>
#include <SPI.h>
//#include "Votaciones.h" puede que no sea necesario este include
#include "ArduinoJson.h"
#define MICROSD_PIN 5    /* Pin de control MicroSD */  
File MicroSD_File;       /* Archivo para escribir  o leer en la MicroSD */
class MyMicroSD  {
  // VARIABLES
  private:
    uint8_t contador = 0;      /* */
    String filename = "/electores.json";   /* Nombre de archivo que incluye "/" que indica la ubicación en raíz */
    // bool idExiste ( uint16_t , JsonArray& );
    DynamicJsonDocument electores;
  // MÉTODOS
  public:
    MyMicroSD() : electores(1024) {}
    void init ( void );
    void SaveFile ( const DynamicJsonDocument& );
    void ReadFile ( void );
    void SetFileName ( String );

    int8_t GetJson();   
    int8_t CheckElector ( const char* );
    void CreateDummy ( void );
  //  void guardarEnSD( const DynamicJsonDocument& );
};

// bool MyMicroSD :: idExiste(uint16_t id, JsonArray& arreglo) {
//     for (const auto& elemento : arreglo) {
//       if (elemento["idVotante"] == id) {
//         return true; // El ID ya existe
//       }
//     }
//     return false; // El ID no existe
// }

// void MyMicroSD :: guardarEnSD( const DynamicJsonDocument& jsonParaAgregar ) {
//   // Leer el contenido actual del archivo JSON
//   File archivo = SD.open(filename);
//   String jsonString = "";

//   if (archivo) {
//     while (archivo.available()) {
//       jsonString += archivo.read();
//     }
//     archivo.close();
//   }
//    // Parsear el JSON
//     DynamicJsonDocument jsonDoc(1024);
//     deserializeJson(jsonDoc, jsonString);
//     JsonArray jsonArray = jsonDoc.as<JsonArray>();
//     // Verificar si el ID ya existe en el arreglo
//     if (idExiste(jsonParaAgregar["idVotante"], jsonArray)) {
//       Serial.println("El ID ya existe, no se agrega el elemento.");
//       return;
//     }

//     // Agregar el JSON existente al arreglo
//     jsonDoc.add(jsonParaAgregar);

//     // Ordenar el arreglo en función de la ID
//     std::sort(jsonDoc.as<JsonArray>().begin(), jsonDoc.as<JsonArray>().end(), [](const JsonVariant& a, const JsonVariant& b) {
//       return a["idVotante"] < b["idVotante"];
//     });

//   // Escribir el arreglo ordenado en el archivo JSON
//   archivo = SD.open(filename, FILE_WRITE);

//   if (archivo) {
//     serializeJson(jsonDoc, archivo);
//     archivo.close();
//   } else {
//     Serial.println("Error abriendo el archivo en modo escritura");
//   }
// }

void MyMicroSD :: SetFileName( String fecha ){
  filename = "/";
  filename += fecha;
  filename += ".json";
}
void MyMicroSD::init ( void ){

   while ( !SD.begin ( MICROSD_PIN ) ) {
        Serial.println ( F ( "Falló la inicialización del módulo MicroSD"  ));
        delay(1000);
    }
    Serial.println ( F ( "La librería MicroSD ha inicializado con éxito" ) );
}

void MyMicroSD :: SaveFile ( const DynamicJsonDocument& jsonDoc ) {
    
    // Abrir o crear en caso de que no exista.
    MicroSD_File = SD.open ( filename, FILE_APPEND );
    if ( MicroSD_File ) {

        // Almacenar JSON en el archivo.
        //serializeJson(*doc, JSON);
        serializeJson( jsonDoc, MicroSD_File );
        // MicroSD_File.println ( txt );
        //MicroSD_File.println ( contador );
        contador++;
        MicroSD_File.close ( );
      
    } else {
        // if the file didn't open, print an error:
        Serial.print ( F ( "Error opening " ) );
        Serial.println ( filename );
 
       
    }
    Serial.println ( "Verificando si existe el archivo: ");
    if ( SD.exists ( filename ) ) {
    Serial.println ( filename );
    Serial.println( " existe" );
  } else {
        Serial.println ( filename );
    Serial.println( " no existe" );
  }
     // Esperar un segundo entre lecturas
      delay ( 1000 );
}
void MyMicroSD :: ReadFile ( void ) {

    //String filename = "/TestMicroSD.txt";
    // re-open the file for reading:
  MicroSD_File = SD.open( filename );
  if ( MicroSD_File ) {
    Serial.println( "Archivo:" );

    // read from the file until there's nothing else in it:
    while ( MicroSD_File.available ( ) ) {

      Serial.write ( MicroSD_File.read ( ) );

    }
    // close the file:
    MicroSD_File.close ( );
  } else {
    // if the file didn't open, print an error:
    Serial.println ( "Error abriendo el archivo" );
  }

}

int8_t MyMicroSD :: GetJson ( void )
{
  MicroSD_File = SD.open ( filename, FILE_READ );

  String jsonString = "";

  if ( MicroSD_File ) {

    while (MicroSD_File.available()) {
        jsonString += char(MicroSD_File.read());
    }

    MicroSD_File.close();

    electores.clear();

    DeserializationError error = deserializeJson(electores, jsonString);
    if (error) {
      // Si hay un error, establece un JSON con "error": true
      electores["error"] = true;
      Serial.println(F("Error al deserializar, clave 'error' agregada."));
      return -1;
    }

    return 0;
  }

  return 1; 
}

int8_t MyMicroSD :: CheckElector ( const char* idElector )
{
  int8_t hasVoted = 0;
  //{"1":{"name":"Juan Pérez","has_voted":false},"2":{"name":"Ana Gómez","has_voted":true},"3":{"name":"Carlos Rodríguez","has_voted":true},"4":{"name":"María López","has_voted":false},"5":{"name":"Pedro Sánchez","has_voted":true}}

  if(electores.containsKey(idElector))
  {//idElector = "2" | For some reason, this throws false. I dont know why!
    hasVoted = electores[idElector]["has_voted"];
  }

  return hasVoted;

}



void MyMicroSD :: CreateDummy ( void )
{
  // Crea un DynamicJsonDocument con suficiente espacio para almacenar los datos
  DynamicJsonDocument doc(1024);

  // Añade los electores y sus datos
  JsonObject elector1 = doc.createNestedObject("1");
  elector1["name"] = "Juan Pérez";
  elector1["has_voted"] = false;

  JsonObject elector2 = doc.createNestedObject("2");
  elector2["name"] = "Ana Gómez";
  elector2["has_voted"] = true;

  JsonObject elector3 = doc.createNestedObject("3");
  elector3["name"] = "Carlos Rodríguez";
  elector3["has_voted"] = true;

  JsonObject elector4 = doc.createNestedObject("4");
  elector4["name"] = "María López";
  elector4["has_voted"] = false;

  JsonObject elector5 = doc.createNestedObject("5");
  elector5["name"] = "Pedro Sánchez";
  elector5["has_voted"] = true;

  SetFileName("electores");

  SaveFile(doc);

}

#endif