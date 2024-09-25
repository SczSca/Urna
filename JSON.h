#ifndef JSON_h
#define JSON_h

#include "ArduinoJson.h"
class json_factory{
  private:
    String _final_json;
    String _fecha;
    String _tiempo;
    String _voto;
    String _votante;
    void eraseData ( void );
  
  public:
    DynamicJsonDocument make_json( void );
    void setData ( String, String, String, String);
};

void json_factory :: setData (String fechaParam, String tiempoParam,  String votoParam, String votanteParam){
  _fecha = fechaParam;
  _tiempo = tiempoParam;
  _voto = votoParam;
  _votante = votanteParam;

}

void json_factory :: eraseData ( void ){
  _fecha = "";
  _tiempo = "";
  _voto = "";
  _votante = "";

}

DynamicJsonDocument json_factory :: make_json( void ){

  DynamicJsonDocument JSON ( 1024 );
  if (!_votante)  return JSON;
  JSON["id_casilla"]=123;
  JSON["ciudad"] = "Colima",
  JSON["idVotante"]=_votante;
  JSON["voto"]=_voto;
  JSON["fecha"] = _fecha;
  JSON["hora"] = _tiempo;
  String json_response = "";
  serializeJsonPretty( JSON, json_response );
  eraseData();
  return JSON;
}


#endif