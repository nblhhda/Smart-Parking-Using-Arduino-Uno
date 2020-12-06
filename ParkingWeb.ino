 
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):

EthernetServer server(80);

int ledPin1 = 5;
int ledPin2 = 6;
int ledPin3 = 3;

int trigPin1 = 13;
int echoPin1 = 12;

int trigPin2 = 8;
int echoPin2 = 7;

int trigPin3 = 4;
int echoPin3 = 2;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
 
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
   if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

 // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
void loop() {
  
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close"); // the connection will be closed after completion of the response
//client.println("Refresh: 10");  // refresh the page automatically every 10 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<style>html { font-family: Cairo; display: block; margin: 0px auto; text-align: center;color: #333333; background-color: ##f3ffee;}");
client.println("body{margin-top: 50px;}");
client.println("h1 {margin: 50px auto 30px; font-size: 50px; text-align: center;}");
client.println(".side_adjust{display: inline-block;vertical-align: middle;position: relative;}");
client.println(".text1{font-weight: 180; padding-left: 5px; font-size: 50px; width: 170px; text-align: left; color: #3498db;}");
client.println(".data1{font-weight: 180; padding-left: 1px; font-size: 50px;color: #3498db;}");
client.println(".data{padding: 1px;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div id=\"webpage\">");
client.println("<h1>SMART PARKING</h1>");
client.println("<h2>PARKING LOT 1!</h2>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Status:</div>");
 int duration1, distance1;
  digitalWrite (trigPin1, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;


  if (distance1 < 10) {  // Change the number for long or short distances.
    digitalWrite (ledPin1, HIGH);
  
    client.println("Not Available");
  } else {
    digitalWrite (ledPin1, LOW);
    
    client.println("Available");
     client.println("<input type=button value=BOOK onmousedown=location.href='http://abiykuomel.com/smartparkingwebsite/bookParking.html'>");
  } 

    
client.println("<h2>PARKING LOT 2!</h2>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Status:</div>");
 int duration2, distance2;
  digitalWrite (trigPin2, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;


  if (distance2 < 10) {  // Change the number for long or short distances.
    digitalWrite (ledPin2, HIGH);
   
    client.println("Not Available");
  } else {
    digitalWrite (ledPin2, LOW);
    
    client.println("Available");
   client.println("<input type=button value=BOOK onmousedown=location.href='http://abiykuomel.com/smartparkingwebsite/bookParking.html'>");
  }   
  client.println("<h2>PARKING LOT 3!</h2>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Status:</div>");
 int duration3, distance3;
  digitalWrite (trigPin3, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin3, LOW);
  duration3 = pulseIn (echoPin3, HIGH);
  distance3 = (duration3/2) / 29.1;


  if (distance3 < 10) {  // Change the number for long or short distances.
    digitalWrite (ledPin3, HIGH);
   
   client.println("Not Available");
  } else {
    digitalWrite (ledPin3, LOW);
     
    client.println("Available");
      client.println("<input type=button value=BOOK onmousedown=location.href='http://abiykuomel.com/smartparkingwebsite/bookParking.html'>");
  }   
      
   client.println("<div class=\"side_adjust data1\">");
client.println("<br />");
          
client.println("</div>");
client.println("</div>");
client.println("</body>");
client.println("</html>");


break;
}
}
    }

// give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  }
          
