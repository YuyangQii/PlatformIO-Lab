#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void blinkLEDAndVibrate(int number);
void displayDiceRoll(int number, sensors_event_t a);
void turnOffLED();
void displayEnvironmentalData();
void printEnvironmentalData();

// 定义引脚
#define MOTOR_PIN A0
#define LED_PIN A2

// 初始化传感器
Adafruit_MPU6050 mpu;
Adafruit_BME280 bme;
Adafruit_SSD1306 display(128, 64, &Wire);

void setup() {
  Serial.begin(9600);
  while(!Serial);    // 等待串行端口初始化
  Serial.println("Init");

  // 初始化MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050未找到");
    while (1);
  }

  // 初始化BME280
  if (!bme.begin(0x76)) {
    Serial.println("BME280未找到");
    while (1);
  }

  // 初始化OLED显示
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 OLED未找到");
    while (1);
  }

  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  display.display(); // 显示Adafruit logo
  delay(2000);
  display.clearDisplay();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 检测非Z轴方向的运动
  if (abs(a.acceleration.x) > 10 || abs(a.acceleration.y) > 10) {
    int diceRoll = random(1, 7); // 生成1到6的随机数
    blinkLEDAndVibrate(diceRoll); // 控制LED和马达
    displayDiceRoll(diceRoll, a);    // 显示点数
  } 
  // 检测Z轴方向的运动
  else if (abs(a.acceleration.z - 9) > 10) {
    turnOffLED();
    displayEnvironmentalData(); // 显示环境数据
  } else {
    // 在每次循环中打印环境数据
    printEnvironmentalData();
  }

  delay(100); // 延时以避免过快的响应
}

void blinkLEDAndVibrate(int number) {
  for (int i = 0; i < number; i++) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(MOTOR_PIN, HIGH);
    delay(500); 
    digitalWrite(LED_PIN, LOW);
    digitalWrite(MOTOR_PIN, LOW);
    delay(500); 
  }
}

void turnOffLED() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);
  display.clearDisplay();
  display.display();
}

void displayDiceRoll(int number, sensors_event_t a) {
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Dice: ");
  display.println(number);
  display.display(); 
}

void displayEnvironmentalData() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Hum: "); display.print(humidity); display.println("%");
  display.print("Press: "); display.print(pressure); display.println("hPa");
  display.display(); 
}

void printEnvironmentalData() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" ");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" ");
}