void setup() {
  while(!Serial){
    delay(10);
  }
  Serial.begin(9600);
  Serial.print("> ");
}

void loop () {
  char val = -1;
  while(val == -1) {
    if(val != -1) command += val;
    delay(5);
    val = Serial.read();
  }
  handleCharacter(val);
  
  delay(5);
}

void red(boolean state) {
  digitalWrite(pin("D2"), state ? HIGH : LOW);
}

void green(boolean state) {
  digitalWrite(pin("D3"), state ? HIGH : LOW);
}

void blue(boolean state) {
  digitalWrite(pin("D4"), state ? HIGH : LOW);
  digitalWrite(pin("D5"), state ? HIGH : LOW);
}

int pin(String name) {
  if (name == "a0") return A0;
  else if(name == "a1") return A1;
  else if(name == "a2") return A2;
  else if(name == "a3") return A3;
  else if(name == "a4") return A4;
  else if(name == "a5") return A5;
  else if(name == "d0") return 0;
  else if(name == "d1") return 1;
  else if(name == "d2") return 2;
  else if(name == "d3") return 3;
  else if(name == "d4") return 4;
  else if(name == "d5") return 5;
  else if(name == "d6") return 6;
  else if(name == "d7") return 7;
  else if(name == "d8") return 8;
  else if(name == "d9") return 9;
  else if(name == "d10") return 10;
  else if(name == "d11") return 11;
  else if(name == "d12") return 12;
  else if(name == "d13") return 13;
  else return -1;
}


String splitString(String s, char parser,int index){
  String rs='\0';
  int parserIndex = index;
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;

  while(index>=parserCnt){
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);

    if(index == parserCnt){
      if(rToIndex == 0 || rToIndex == -1){
        return '\0';
      }
      return s.substring(rFromIndex,rToIndex);
    }
    else{
      parserCnt++;
    }

  }
  return rs;
}

void handleCharacter(char chr) {
  if(chr == 13) {
    runCommand(command + " ");
    command = "";
    pos = 0;
    Serial.print("> ");
  } else if(chr == 27) {
    delay(2);
    Serial.read();
    delay(2);
    Serial.read();
   return;
  } else if(chr == 4) {
    Serial.end();
    delay(10);
    Serial.begin(9600);
  } else if(chr == 127) {
    if(command.length() > 0) {
      command = command.substring(0, command.length() - 1);
      Serial.print(char(8));
      Serial.print(char(32));
      Serial.print(char(8));
      pos--;
    }
  } else {
    command += chr;
    Serial.print(chr);
    pos++;
  }
  
}

void runCommand(String command) {
  command.toLowerCase();
  Serial.println();
  String action = splitString(command, ' ', 0);
  if(action == "set") {
    set(splitString(command, ' ', 1), splitString(command, ' ', 2));
  } else if(action == "get") {
    get(splitString(command, ' ', 1));
  } else if(action == "help") {
    help();
  } else {
    Serial.println("ERROR: UNKNOWN COMMAND");
  }
}

void set(String pinno, String state) {
  int pinnumber = pin(pinno);
  if(pinnumber == -1) {
   Serial.println("ERROR: UNKNOWN PIN");
   return;
  } 
  if(state == "on") {
    digitalWrite(pinnumber, HIGH);
  } else if(state == "off") {
    digitalWrite(pinnumber, LOW);
  } else if(state.toInt() >= 0) {
    digitalWrite(pinnumber, state.toInt());
  } else {
    Serial.println("ERROR: UNKNOWN STATE");
  }
}

void get(String pinno) {
  Serial.println(analogRead(pin(pinno)));
}

void help() {
  Serial.println("----------------------------------------------------------------");
  Serial.println("---- HELP FOR ARDUINO SHELL ------------------------------------");
  Serial.println("----------------------------------------------------------------");
  Serial.println("Commands:");
  Serial.println("  set");
  Serial.println("    Syntax: get [pinname (eg D2 or A0)] [on/off]");
  Serial.println("    Set the status of a Pin");
  Serial.println("  get");
  Serial.println("    Syntax: get [pinname (eg D2 or A0)]");
  Serial.println("    Get the current status of a Pin");
  Serial.println("  help");
  Serial.println("    Syntax: help");
  Serial.println("    This short help");
  Serial.println("----------------------------------------------------------------");
}



