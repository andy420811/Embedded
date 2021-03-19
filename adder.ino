#define A_bit1 49
#define A_bit2 51
#define A_bit3 53
#define B_bit1 43
#define B_bit2 45
#define B_bit3 47

#define LED_C1_PIN 3
#define LED_C2_PIN 5
#define LED_C3_PIN 6
#define LED_C4_PIN 9
#define LED_C5_PIN 10

bool a1,a2,a3;
bool b1,b2,b3;
bool c1,c2,c3,c4,c5;

void setup()
{
    pinMode(A_bit1 , INPUT);
    pinMode(A_bit2 , INPUT);
    pinMode(A_bit3 , INPUT);
    pinMode(B_bit1 , INPUT);
    pinMode(B_bit2 , INPUT);
    pinMode(B_bit3 , INPUT);
}

void loop()
{

}
void Multiplier(){
  c1 = a1^b1;
  c5 = a3^b3;
  c4 = (a2&b3)^(a3&b2);
  c3 = ((a2&b3)&(a3&b2))^(a2&b2);
  c2 = ((a2&b3)&(a3&b2))&(a2&b2);
}
void bit3_adder(){
    bool negative_a = a3 & 0b001;
    bool negative_b = b3 & 0b001;
    

    int cout;
    cout = adder( &c1, a1 , b1 , 0);
}

bool adder(bool *s,bool a,bool b,bool cin){
    *s = a | b | cin;
    bool cout = (a&b) | (cin&(a|b));
    return cout;
}

void READ_NUM(){
    a1 = digitalRead(A_bit1);
    a2 = digitalRead(A_bit2);
    a3 = digitalRead(A_bit3);
    b1 = digitalRead(B_bit1);
    b2 = digitalRead(B_bit2);
    b3 = digitalRead(B_bit3);
}


void print(){

}
