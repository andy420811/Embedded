#define A_bit1 49
#define A_bit2 51
#define A_bit3 53
#define B_bit1 43
#define B_bit2 45
#define B_bit3 47

/* Use Arduino uno
#define LED1_PIN 3
#define LED2_PIN 5
#define LED3_PIN 6
#define LED4_PIN 9
#define LED5_PIN 10
*/

//Use Arduino Due
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 4
#define LED4_PIN 5
#define LED5_PIN 6

bool a[3];
bool b[3];
bool c[5];

void setup()
{
    
    pinMode(A_bit1 , INPUT);
    pinMode(A_bit2 , INPUT);
    pinMode(A_bit3 , INPUT);
    pinMode(B_bit1 , INPUT);
    pinMode(B_bit2 , INPUT);
    pinMode(B_bit3 , INPUT);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    
    memset(a , 0 , sizeof(a));
    memset(b , 0 , sizeof(b));
    memset(c , 0 , sizeof(c));
}

void loop()
{
    READ_NUM();
    Multiplier();
    update();
    delay(1000);
}

void Multiplier(){
    
  c[4] = a[2]^b[2];
  c[0] = a[0]&b[0];
  c[1] = (a[1]&b[0])^(a[0]&b[1]);
  c[2] = ((a[1]&b[0])&(a[0]&b[1]))^(a[1]&b[1]);
  c[3] = ((a[1]&b[0])&(a[0]&b[1]))&(a[1]&b[1]);
}
void READ_NUM(){
    a[0] = digitalRead(A_bit1);
    a[1] = digitalRead(A_bit2);
    a[2] = digitalRead(A_bit3);
    b[0] = digitalRead(B_bit1);
    b[1] = digitalRead(B_bit2);
    b[2] = digitalRead(B_bit3);
    //Serial.println("A: " + String(a[2]) + String(a[1]) + String(a[0]));
    //Serial.println("B: " + String(b[2]) + String(b[1]) + String(b[0]));
}
void update(){
    for (uint8_t i = 0; i < 5; i++)
    {
        led_state(i+1,c[i]);
    }
}

void led_state(uint8_t no,bool sw){
    switch (no)
    {
    case 1:
        digitalWrite(LED1_PIN , sw?HIGH:LOW);
        break;
    case 2:
        digitalWrite(LED2_PIN , sw?HIGH:LOW);
        break;
    case 3:
        digitalWrite(LED3_PIN , sw?HIGH:LOW);
        break;
    case 4:
        digitalWrite(LED4_PIN , sw?HIGH:LOW);
        break;
    case 5:
        digitalWrite(LED5_PIN , sw?HIGH:LOW);
        break;
    default:
        break;
    }
}
