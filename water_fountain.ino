char* menuStrings[] = {"\n Waterhinge debugger \n",
       "1.  Turn valve on/off",
       "2.  All valves on",
       "3.  All valves off",
       "4.  Enter text A-Z,0-9 < 36 Characters\n",
       "Enter 1 - 4->"};

int f_delay = 125;

// This array maps the digital output pin to the the valve number.
// For example, digital pin 24 connects to valve 0, pin 25 connects to valve 1,
// digital pin22 connects to valve 22, etc.
int pin_to_valve[] = {24, 25, 22, 23, 28, 29, 26, 32, 33, 30, 31, 36, 37, 34, 35};

//
// Choosing a 5 X 7 dot matrix font, valves "0-2 correlate to column 1 of the font,
// valves 3-5 correlate to column 2, valves 6-9 correlate to column 3 (Notice that this
// column has 4 valves instead of 3. The extra valve is necessary in order to translate
// the five font columns into 16 valve columns. Sticking the extra valve in the middle 
// column maintains symetry.), valves A-C correlate to column 4 and columns D-F correlate
// to column 5. Translating the 5 X 7 fonts into bit maps that the valves can display now
// becomes trivial albiet tidious to construct.
//
//              valve "0123456789ABCDEF     Time tics

String char_AZ09[] = {"1110000000000111",  // tic 1 letter A
                      "1110000000000111",  // tic 2
                      "1111111111111111",  // tic 3
                      "0111000000001110",  // tic 4
                      "0011100000011100",  // tic 5
                      "0000111111110000",  // tic 6
                      "0000001111000000",  // tic 7

                      "1111111111111000",  // letter B 
                      "0111000000000111",   
                      "0111000000000111",   
                      "0111111111111000",   
                      "0111000000000111",   
                      "0111000000000111",   
                      "1111111111111000",  

                      "0001111111111000",  // letter C
                      "1110000000000111",   
                      "1110000000000000",   
                      "1110000000000000",   
                      "1110000000000000",   
                      "1110000000000111",   
                      "0001111111111000",  

                      "1111111111111000",  // letter D
                      "0111000000001110",   
                      "0111000000000111",  
                      "0111000000000111",  
                      "0111000000000111",  
                      "0111000000001110",   
                      "1111111111111000",  

                      "1111111111111111",  // letter E
                      "1110000000000000",
                      "1110000000000000",
                      "1111111111110000",
                      "1110000000000000",
                      "1110000000000000",
                      "1111111111111111",

                      "1110000000000000",  // letter F
                      "1110000000000000",
                      "1111111111110000",
                      "1110000000000000",
                      "1110000000000000",
                      "1111111111111111",
           
                      "0001111111111000",  // letter G
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000111111",
                      "1110000000000000",
                      "1110000000000000",
                      "0001111111111000",
            
                      "1110000000000111",  // letter H
                      "1110000000000111",
                      "1110000000000111",
                      "1111111111111111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
            
                      "0001111111111000",  // letter I
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "1111111111111111",
                      
                      "0001111111000000",  // letter J
                      "1110000000111000",
                      "1110000000111000",
                      "0000000000111000",
                      "0000000000111000",
                      "0000000000111000",
                      "0000000111111111",
            
                      "1110000000000111",  // letter K
                      "1110000000111000",
                      "1110000111100000",
                      "1111111000000000",
                      "1110000111100000",
                      "1110000000111000",
                      "1110000000000111",
            
                      "1111111111111111",  // letter L
                      "1110000000000000",
                      "1110000000000000",
                      "1110000000000000",
                      "1110000000000000",
                      "1110000000000000",
                      "1110000000000000",
            
                      "1110000000000111",  // letter M
                      "1110000000000111",
                      "1110001111000111",
                      "1110001111000111",
                      "1110011111100111",
                      "1111110000111111",
                      "1110000000000111",
            
                      "1110000000000111",  // letter N
                      "1110000000111111",
                      "1110000011100111",
                      "1110000111000111",
                      "1110001110000111",
                      "1110011100000111",
                      "1111100000000111",
            
                      "0001111111111000",  // letter O
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "0001111111111000",
            
                      "1110000000000000",  // letter P
                      "1110000000000000",
                      "1110000000000000",
                      "1111111111111000",
                      "1110000000000111",
                      "1110000000000111",
                      "1111111111111000",
            
                      "0001111111111000",  // letter Q
                      "1110000011100111",
                      "1110000111000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "0001111111111000",
            
                      "1110000000000111",  // letter R
                      "1110000000011100",
                      "1110000000111000",
                      "1111111111111000",
                      "1110000000000111",
                      "1110000000000111",
                      "1111111111111000",
            
                      "0001111111111000",  // letter S
                      "1110000000000111",
                      "1110000000000000",
                      "0001111111111000",
                      "0000000000000111",
                      "1110000000000111",
                      "0001111111111000",
            
                      "0000001111000000",  // letter T
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "1111111111111111",
            
                      "0001111111111000",  // letter U
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
                      "1110000000000111",
            
                      "0000001111000000",  // letter V
                      "0000011111100000",
                      "0000111001110000",
                      "0001110000111000",
                      "0011100000011100",
                      "0111000000001110",
                      "1110000000000111",

                      "1110000000000111",  // letter W        
                      "1111110000111111",          
                      "1110011111100111",        
                      "1110001111000111",
                      "1110001111000111",
                      "1110000000000111",
                      "1110000000000111",
            
                      "1110000000000111",  // letter X
                      "0001110000111000",
                      "0000001111000000",
                      "0000001111000000",
                      "0000001111000000",
                      "0001110000111000",
                      "1110000000000111",
       
                      "0000000111000000",  // letter Y
                      "0000000111000000",
                      "0000001111100000",
                      "0000111000111000",
                      "0001110000011100",
                      "0011100000001110",
                      "1110000000000111",
            
                      "1111111111111111",    // letter Z
                      "0000000000011100",
                      "0000000001110000",
                      "0000000111000000",
                      "0000011100000000",
                      "0001110000000000",
                      "1111111111111111"};                    
        
char incomingByte;
int valve_number;
boolean valid = false;

void write_letter();
void runProgram();
void valves();

void setup(){
  // initialize all the ports as outputs
  for (int i=0; i < 16; i++){
    pinMode((i+22),OUTPUT);
    digitalWrite((i+22), LOW);
  }
  Serial1.begin(9600);
}
  
void loop(){
  for (int m=0;m<6;m++){
    Serial1.println(menuStrings[m]);}
  
  while(Serial1.available()==0){};
  
  incomingByte = Serial1.read();
  switch (incomingByte){
      case '1':
         Serial1.println("\nTurn a valve on/off");      
         valid = false;
         while (valid == false){
            Serial1.println("\nEnter a valve number 0 - 15->");
            while(Serial1.available()==0){};
            valve_number = Serial1.parseInt();
            if ( valve_number >= 0 && valve_number <= 15){
                  digitalWrite(pin_to_valve[valve_number],!digitalRead(pin_to_valve[valve_number]));
                  valid = true;}
            else{
                  Serial1.println("\nInvalid input. Enter valve number 0 - 15 ->");
                  valid = false;} 
         }
         break;
      case '2':
         Serial1.println("\nAll valves on");
         valves(HIGH);
         break;
      case '3':
         Serial1.println("\n Turning all valves off");
         valves(LOW);
         break;
      case '4':
         runProgram();
      default:
         Serial1.println("\nInvalid input. Enter 1 - 4->");}
       } 

void runProgram(){
    int j, m = 0;
    boolean end_input = false;
    
    // The input string is converted to integers as the characters are read in
    int input_string[36];
    while(!end_input){
       while(Serial1.available()==0){};
       incomingByte = Serial1.read();
       if ((incomingByte >= 'A') && (incomingByte <= 'Z')){
          input_string[j++] = int(incomingByte) - 65;}
       else{
            if((incomingByte >= 'a') && (incomingByte <= 'z')){ 
                  input_string[j++] = int(incomingByte) - 97;}
           }
       // test for end of the buffer or a carriage return and end the input
       if((j == 35) || (int(incomingByte) == 13)){
          end_input = true;}
       }
       // output the text buffer to the valves
       while(m++ <= j){
            write_letter(input_string[m]*8);
       }
    }
       
void valves(boolean state){
    for(int k=0;k<16;k++){
           digitalWrite((k+22),state);}
    }       
         
void write_letter(int position_in_table){
    for (int g = position_in_table; g < (position_in_table+7); g++){
      for (int h=0; h<15; h++){
         if(char_AZ09[g].charAt(h) == '1'){
            digitalWrite(pin_to_valve[h], HIGH);}
         else{
            digitalWrite(pin_to_valve[h], LOW);}
      }
    }  
    valves(LOW);
}

