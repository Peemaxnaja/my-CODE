#include <Arduino.h>

const int btns[] = {14, 27, 26, 25};
const int relays[] = {33, 32, 13, 15};

// เก็บค่าสถานะก่อนหน้าเพื่อเช็คการกด
int lastStates[] = {1, 1, 1, 1}; 

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(btns[i], INPUT_PULLUP);
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], LOW);
    // อ่านค่าเริ่มต้นเก็บไว้
    lastStates[i] = digitalRead(btns[i]);
  }
  Serial.println("HandySense Button Toggle Ready!");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int currentState = digitalRead(btns[i]);

    // ถ้าสถานะเปลี่ยนไปจากเดิม (มีการกดหรือปล่อย)
    if (currentState != lastStates[i]) {
      delay(50); // Debounce ป้องกันปุ่มเด้ง
      
      // เช็คอีกครั้งเพื่อความชัวร์
      if (digitalRead(btns[i]) == currentState) {
        
        // เงื่อนไข: ถ้าเป็น SW0 (ปกติเป็น 1) ให้ทำงานเมื่อเป็น 0
        // หรือถ้าเป็น SW1-3 (ปกติเป็น 0) ให้ทำงานเมื่อเป็น 1
        if ((i == 0 && currentState == LOW) || (i > 0 && currentState == HIGH)) {
          Serial.print("Button "); Serial.print(i); Serial.println(" PRESSED!");
          
          // สั่ง Toggle Relay (ถ้าเปิดอยู่ให้ปิด ถ้าปิดอยู่ให้เปิด)
          digitalWrite(relays[i], !digitalRead(relays[i]));
        }
        
        lastStates[i] = currentState; // อัปเดตสถานะล่าสุด
      }
    }
  }
}