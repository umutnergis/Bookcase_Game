// Stepper - 8-9-10-11
#include <Arduino.h>
#include <Stepper.h>
#include DEBUG
#define book1 2
#define book2 3
#define book3 4
#define book4 5
#define book5 6
#define buzzer 7
#define relay 8

const int steps = 100;
int order[5] = {};
int correctOrder[5] = {1, 2, 3, 4, 5};

void stepper();
void addOrder(int value);
bool checkOrder();

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    Stepper lib_stepper(stepsPerRevolution, 8, 9, 10, 11);
    lib_stepper.setSpeed(300);
    for (int i = 2; i <= 6; i++)
    {
        pinMode(i, INPUT);
    }
    pinMode(buzzer, OUTPUT);
    pinMode(relay,OUTPUT);
}
void loop()
{
    stepper();
    if (digitalRead(book1) == 0 || digitalRead(book2) == 0 || digitalRead(book3) == 0 || digitalRead(book4) == 0 || digitalRead(book5) == 0)
    {
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        if (digitalRead(book1) == 0)
        {
            addOrder(1);
#ifdef DEBUG
            Serial.println("Book 1 is added");
#endif
        }
        if (digitalRead(book2) == 0)
        {
            addOrder(2);
#ifdef DEBUG
            Serial.println("Book 2 is added");
#endif
        }
        if (digitalRead(book3) == 0)
        {
            addOrder(3);
#ifdef DEBUG
            Serial.println("Book 3 is added");
#endif
        }
        if (digitalRead(book4) == 0)
        {
            addOrder(4);
#ifdef DEBUG
            Serial.println("Book 4 is added");
#endif
        }
        if (digitalRead(book5) == 0)
        {
            addOrder(5);
#ifdef DEBUG
            Serial.println("Book 5 is added");
#endif
        }
        if(checkOrder() == true)
        {
            digitalWrite(relay, HIGH);
            delay(1000);
            digitalWrite(relay, LOW);
        }
        delay(200);
    }
}

void stepper()
{
    while (game_start == 0)
    {
        lib_stepper.step(steps);
        delay(100);
#ifdef DEBUG
        Serial.println("Stepper is going up");
#endif
    }
}

void addOrder(int value)
{
    for (int i = 0; i < 5; i++)
    {
        order[i] = order[i + 1];
    }
    order[5] = value;
}

bool checkOrder()
{
    for (int i = 0; i < 5; i++)
    {
        if (order[i] != correctOrder[i])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}