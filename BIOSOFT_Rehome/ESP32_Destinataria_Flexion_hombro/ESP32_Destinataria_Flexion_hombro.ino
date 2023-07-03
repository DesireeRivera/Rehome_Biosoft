#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  float ID;
  float ax;
  float ay;
  float az;
  //uint8_t Err;

} struct_message;

// Create a struct_message called myData
struct_message myData;


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 memcpy(&myData, incomingData, sizeof(myData));

  //Serial.print("ID: ");
  //Serial.print(myData.ID);
  int ax1;
  int ax2;
  int ax3;
  int id = myData.ID;
  switch(id)
  {
    case 1: {
      //Serial.print ("Entra en id = 1");
      //Serial.print(myData.ax);
      //Serial.println(" ");
      float ax1 = myData.ax;
      
    break;
    }
    case 2:{
    //  Serial.print ("Entra en id = 2");
     //Serial.print(myData.ax);
     //Serial.println(" ");
     
     float ax2 = myData.ax;
    
     // if(ax1 & ax2 )
     //{ 
     
      
     //}
    break;
    }
    case 3:{
      //Flexion de hombro 
     float ax3 = myData.ax;
     float ax1 = ax3 - ax1;
     float ax2 = ax3 - ax2;
      Serial.print(ax1);
      Serial.print(" ");
      Serial.print(ax2);
    Serial.print(" ");
     Serial.print(ax3);
     Serial.println(" ");

    
   // else
   //  {Serial.print ("nah");}
   // break;
    }
    //default:
      //break;
      
  }

  //Serial.print("ay: ");
 // Serial.print(myData.ay);
 // Serial.print("Err: ");
 // Serial.println(myData.Err);
}
 
void setup() {
 // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
