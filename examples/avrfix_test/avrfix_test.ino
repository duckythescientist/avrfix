/*  
  Example usage of the AVRfix library
*/



// AVRfix is a c-style library. It must be included this way
extern "C"{
  #include <avrfix.h>
}


void setup() {
  Serial.begin(115200);
  Serial.println("starting");

  // This example will use the "long" fixed type (s7.24 bit format)
  lfix_t foo = ftolk(3.1);  // float to lfix_t
  lfix_t bar = ftolk(2.2);

  Serial.print("3.1 == ");
  Serial.println(lktod(foo));  // lfix_t to double conversion



  lfix_t baz = lmullk(foo, bar);  // multiply two lfix_t and return an lfix_t

  Serial.print("3.1x2.2 = ");
  Serial.println(lktod(baz));


  baz = lsinlk(baz);  // in radians

  Serial.print("sin(6.82) == ");
  Serial.println(lktod(baz));
  
  Serial.println("finished");
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
