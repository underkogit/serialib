#include <Arduino.h>

struct Message
{
  int R;
  int G;
  int B;
  int A;
  int IndexStart;
  int IndexEnd;
};
Message receivedMessage;
void parseInput(String input);
void printMessage();

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    if (!data.startsWith("[Testing];"))
    {
      parseInput(data);

      printMessage();
    }else{
      Serial.println(data);
    }
  }
}

void parseInput(String input)
{
  int max = 6;
  int values[max]; // Массив для хранения значений
  int prevIndex = 0;
  int index = 0;

  while (index < max)
  {
    int nextComma = input.indexOf(',', prevIndex);
    String value;

    if (nextComma == -1)
    {                                     // Если нет следующей запятой
      value = input.substring(prevIndex); // Берем остаток строки
      values[index++] = value.toInt();
      break;
    }
    else
    {
      value = input.substring(prevIndex, nextComma); // Подстрока до запятой
      values[index++] = value.toInt();
      prevIndex = nextComma + 1; // Обновляем индекс для следующей подстроки
    }
  }

  // Заполнение структуры
  if (index == max)
  {
    receivedMessage.R = values[0];
    receivedMessage.G = values[1];
    receivedMessage.B = values[2];
    receivedMessage.A = values[3];
    receivedMessage.IndexStart = values[4];
    receivedMessage.IndexEnd = values[5];
  }
  else
  {
    Serial.println("Неверное количество значений. Ожидались " + String(max) + " чисел.");
  }
}

void printMessage()
{
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
