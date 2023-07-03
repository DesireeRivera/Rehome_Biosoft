
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x7F, 0x7F, 0x0C};
const int MPU_address = 0x68;
MPU6050 sensor{MPU_address};
// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int16_t ax, ay, az;
int16_t gx, gy, gz;
uint8_t Err;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  float ID;
  //float Err;
  float ax, ay, az;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}


void setup() {
  // Init Serial Monitor


  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

              
  Wire.begin(0,2);           //Iniciando I2C  
  sensor.initialize();     //Iniciando el sensor
  if (sensor.testConnection()){
    Err = 0;
    //sensor.setXAccelOffset (-2300);
    //sensor.setYAccelOffset (-200);
  }
    else{
    Err=1000;
  }
  
 
  
}


 //libreia MPU6050_light 
void loop() {
  
  sensor.getAcceleration(&ax, &ay, &az);
//  uint8_t axx = ax;  
//  uint8_t ayy = ay;
//  uint8_t azz = az;

//  
//  accel_ang_x = atan(axx/sqrt(pow(ayy,2) + pow(azz,2)))*(180.0/3.14);
//  accel_ang_y=atan(ayy/sqrt(pow(axx,2) + pow(azz,2)))*(180.0/3.14);

    float accel_ang_x = atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0);
float accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0);

  //Serial.println("");
  delay(500);
  //if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    myData.ID = 1;
    myData.ax = accel_ang_x;
    myData.ay = accel_ang_y;
    //myData.Err=Err;

  

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   //lastTime = millis();
  }
