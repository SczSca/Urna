#ifndef ACTUADORES_H
#define ACTUADORES_H
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd (0x27, 16, 2);
class Actuador{
  private:
    byte MonegraIcon[8] = {
        B00000,
        B00000,
        B10001,
        B11011,
        B10101,
        B10001,
        B10001,
        B10001
      };
      byte BolilloIcon[8] = {
        B01110,
        B10001,
        B10101,
        B10101,
        B10101,
        B10101,
        B10001,
        B01110
      };
      byte PRIncessIcon[8] = {
        B00000,
        B10101,
        B11011,
        B10101,
        B10001,
        B11111,
        B00000,
        B00000
      };
  public:
    
    void lcd_init ( void );
    void print ( String , bool );
    void lcd_clear ( void );
    // void createCharacter ( int , byte );
    void printChar( int );
    void setCursor ( int, int );
    void createCharacterTodos( void );

};
void Actuador :: lcd_init( void ){
  
  lcd.init();
  lcd.backlight();

}

void Actuador :: print (String msg, bool fila){
  
  lcd.setCursor(0, fila);
  lcd.print(msg);
}

void Actuador :: lcd_clear ( void ){
  lcd.clear();
}

// void Actuador :: createCharacter( int posicion, byte caracter){
//   lcd.createChar( posicion, caracter );
// }

void Actuador :: createCharacterTodos( void ){
  lcd.createChar( 0, MonegraIcon );
  lcd.createChar( 1, BolilloIcon );
  lcd.createChar( 2, PRIncessIcon);
}
void Actuador :: printChar( int posicionChar ){
  lcd.write( posicionChar );
}
void Actuador :: setCursor ( int columna, int fila ){
  lcd.setCursor( columna, fila );
}
#endif