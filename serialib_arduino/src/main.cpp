#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 5
#define LED_NUM 50

bool parseInput(String input);
void printMessage();
void setRGB(int i, int r, int g, int b, int a);
 
struct Message {
  int R;
  int G;
  int B;
  int A;
  int IndexStart;
  int IndexEnd;
};

Message receivedMessage;
CRGB leds[LED_NUM];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(255);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');

    if (!data.startsWith("[Testing];")) {
      // Parse the input and show the LED colors only if parsing is successful
      if (parseInput(data)) {
        printMessage();

        for (int i = receivedMessage.IndexStart; i < receivedMessage.IndexEnd; i++) {
          if (i >= 0 && i < LED_NUM) {
            setRGB(i, receivedMessage.R, receivedMessage.G, receivedMessage.B, receivedMessage.A);
          }
        }
        FastLED.show();
      }
    } else {
      Serial.println(data);
    }
  }
}

void setRGB(int i, int r, int g, int b, int a) {
  // Apply alpha effect for brightness control
  a = constrain(a, 0, 250); // Ensure 'a' is within limits
  leds[i].setRGB(r * (a / 250.0), g * (a / 250.0), b * (a / 250.0));
}

bool parseInput(String input) {
  const int max = 6;
  int values[max];

  // Split the input string by commas
  int prevIndex = 0;
  int index = 0;

  while (index < max) {
    int nextComma = input.indexOf(',', prevIndex);
    String value;

    if (nextComma == -1) {
      // No more commas; take the rest of the string
      value = input.substring(prevIndex);
      values[index++] = value.toInt();
      break;
    } else {
      value = input.substring(prevIndex, nextComma);
      values[index++] = value.toInt();
      prevIndex = nextComma + 1; // Update index for next comma
    }
  }

  // Fill the structure if all values were parsed
  if (index == max) {
    receivedMessage.R = values[0];
    receivedMessage.G = values[1];
    receivedMessage.B = values[2];
    receivedMessage.A = values[3];
    receivedMessage.IndexStart = values[4];
    receivedMessage.IndexEnd = values[5];

    // Validate IndexStart and IndexEnd
    if (receivedMessage.IndexStart < 0 || receivedMessage.IndexEnd > LED_NUM || receivedMessage.IndexStart > receivedMessage.IndexEnd) {
      Serial.println("Неверные значения индексов. Убедитесь, что они в пределах 0 и " + String(LED_NUM));
      return false; // Return false if the indices are invalid
    }

    return true; // Successful parsing
  } else {
    Serial.println("Неверное количество значений. Ожидались " + String(max) + " чисел.");
    return false; // Return false for unsuccessful parsing
  }
}

void printMessage() {
  Serial.print("Полученное сообщение: R=");
  Serial.print(receivedMessage.R);
  Serial.print(", G=");
  Serial.print(receivedMessage.G);
  Serial.print(", B=");
  Serial.print(receivedMessage.B);
  Serial.print(", A=");
  Serial.print(receivedMessage.A);
  Serial.print(", IndexStart=");
  Serial.print(receivedMessage.IndexStart);
  Serial.print(", IndexEnd=");
  Serial.print(receivedMessage.IndexEnd);
  Serial.println(";");
}
