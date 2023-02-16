// 1.ОБЪЯВЛЕНИЕ ПОРТОВ

//пины лифта

#define in1 5
#define in2 6
#define in3 7
#define in4 8

//пины кнопок

#define B1 2 // нажатие 1 кнопки -> режим проверки барабана
#define B2 3 // нажатие 2 кнопки -> режим проверки лифта
#define B3 4 // нажатие 3 кнопки -> режим проверки цикла

//пины барабана

#define in5 9
#define in6 10
#define in7 11
#define in8 12


// 2. ОБЪЯВЛЕНИЕ РЕЖИМОВ ПОРТОВ

void setup()
{
//Serial.begin(9600);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);

pinMode(B1, INPUT_PULLUP);
pinMode(B2, INPUT_PULLUP);
pinMode(B3, INPUT_PULLUP);

pinMode(in5, OUTPUT);
pinMode(in6, OUTPUT);
pinMode(in7, OUTPUT);
pinMode(in8, OUTPUT);
}

// 3. ФУНКЦИИ ВРАЩЕНИЯ

//функция вращения барабана

void vr_bar(int t1,int t2)
{
int dl = 2;
for (int t = 0;t <= t1;t++) // ВРАЩЕНИЕ ПРОТИВ ЧАСОВОЙ
{
digitalWrite(in5, HIGH);
digitalWrite(in6, LOW);
digitalWrite(in7, LOW);
digitalWrite(in8, HIGH);
delay(dl);

digitalWrite(in5, HIGH);
digitalWrite(in6, HIGH);
digitalWrite(in7, LOW);
digitalWrite(in8, LOW);
delay(dl);

digitalWrite(in5, LOW);
digitalWrite(in6, HIGH);
digitalWrite(in7, HIGH);
digitalWrite(in8, LOW);
delay(dl);

digitalWrite(in5, LOW);
digitalWrite(in6, LOW);
digitalWrite(in7, HIGH);
digitalWrite(in8, HIGH);
delay(dl);
}

for (int t = 0;t <= t2;t++) // ВРАЩЕНИЕ ПО ЧАСОВОЙ
{
digitalWrite(in5, LOW);
digitalWrite(in6, LOW);
digitalWrite(in7, HIGH);
digitalWrite(in8, HIGH);
delay(dl);

digitalWrite(in5, LOW);
digitalWrite(in6, HIGH);
digitalWrite(in7, HIGH);
digitalWrite(in8, LOW);
delay(dl);

digitalWrite(in5, HIGH);
digitalWrite(in6, HIGH);
digitalWrite(in7, LOW);
digitalWrite(in8, LOW);
delay(dl);

digitalWrite(in5, HIGH);
digitalWrite(in6, LOW);
digitalWrite(in7, LOW);
digitalWrite(in8, HIGH);
delay(dl);
}
}

//функция вращения лифта

void vr_lift(int t1,int t2)
{
int dl = 2;
for (int t = 0;t <= t1;t++) // ВРАЩЕНИЕ ПО ЧАСОВОЙ
{
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, HIGH);
delay(dl);

digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
delay(dl);

digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
delay(dl);

digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
delay(dl);
}

for (int t = 0;t <= t2;t++) // ВРАЩЕНИЕ ПРОТИВ ЧАСОВОЙ
{
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
delay(dl);

digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
delay(dl);

digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
delay(dl);

digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, HIGH);
delay(dl);
}
}

//4. ОБЪЯВЛЕНИЕ ДЕЙСТВИЙ ПРИ НАЖАТИИ КНОПОК

void loop()
{

//нажатие 1 кнопки -> режим проверки барабана

if (!digitalRead(B1))
{
vr_bar(100,200);
}

//нажатие 2 кнопки -> режим проверки лифта

if (!digitalRead(B2))
{
vr_lift(200,100);
}

//нажатие 3 кнопки -> режим проверки цикла
if (!digitalRead(B3))
{
vr_bar(100,100);
vr_lift(200,100);
}

}

// 4 кнопка работает на прямую с портом RESET, не требует написания программного кода.
// 5 кнопка работает отдельно от модуля Arduino
