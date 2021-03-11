String komplett;
String encoded;
int x = 7548;
int y = 4321;
String x_pos = String(x);
String y_pos = String(y);


void decoding(int x_val, int y_val) {
    
}

void setup(){
  komplett = x_pos + y_pos;
  for(int i = 0; i < 4; i++) {
   encoded = komplett[i];
  }
  int encod_int = encoded.toInt();
}


void loop() {
  
}
