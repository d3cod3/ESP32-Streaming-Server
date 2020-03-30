/*********
 *  Laboluz spider - ESP32 streaming server code
 *  IVAM 2020
 *
   - Add https://dl.espressif.com/dl/package_esp32_index.json in Arduino preferences -> Additional URL board manager
   - Install ESP32 package
   - Select Board "AI Thinker ESP32-CAM"
   - GPIO 0 must be connected to GND to upload a sketch
   - After connecting GPIO 0 to GND, press the ESP32-CAM on-board RESET button to put your board in flashing mode
 *
 *
 *
*********/

#include "esp_camera.h"
#include <WiFi.h>

// Select camera model
#define CAMERA_MODEL_AI_THINKER
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_WROVER_KIT

#include "camera_pins.h"

// ----------------------------------------------------
//Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
// ----------------------------------------------------

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 159);
// Set your Gateway IP address (router)
IPAddress gateway(192, 168, 1, 1);
// Set tour Gateway IP subnet
IPAddress subnet(255, 255, 255, 0);

void startCameraServer();

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Camera settings
  sensor_t * s = esp_camera_sensor_get();
  // V flip
  s->set_vflip(s, 0);           // 0 = disable , 1 = enable
  // H mirror
  s->set_hmirror(s, 0);         // 0 = disable , 1 = enable
  // brillo
  s->set_brightness(s, 0);      // -2 to 2
  // contraste
  s->set_contrast(s, 0);        // -2 to 2
  // saturacion
  s->set_saturation(s, 0);      // -2 to 2
  // blanco y negro
  s->set_special_effect(s, 2);  // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)

  // Wi-Fi connection
  WiFi.begin(ssid, password);
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start streaming web server
  startCameraServer();

  Serial.print("Camera Stream Ready! Go to: http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

}

void loop() {
  delay(10000);
}
