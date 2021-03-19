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
bool selectA;

void setup()
{
    Serial.begin(9600);
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
    bit3_adder();
    update();
    delay(1000);
    //Serial.println("C: " + String(c[4]) + String(c[3]) + String(c[2]) + String(c[1]) + String(c[0]));
}
void Multiplier(){
  c[0] = a[0]^b[0];
  c[4] = a[2]^b[2];
  c[3] = (a[1]&b[2])^(a[2]&b[1]);
  c[2] = ((a[1]&b[2])&(a[2]&b[1]))^(a[1]&b[1]);
  c[1] = ((a[1]&b[2])&(a[2]&b[1]))&(a[1]&b[1]);
}
/**
 * the 3 bit signed adder without using if else statement.
 * ## By using multiplexer, full adder and full substractor.
 * 1. rearrange the two number by a is larger number.
 * 2. check a , b is negative or not.
 * 3. if one of a or b is negative use full substractor else use the full adder to get 3bits value.
 * 4. MSB is negative if a(the larger number) is negative or a,b both negative.
 */
void bit3_adder(){
    BigToA();
    bool negative_a = a[2] & 0b001;
    bool negative_b = b[2] & 0b001;
    /*
    Serial.println("selectA A :" + String(selectA) + " selectA B :" + String(!selectA));
    Serial.println("A: " + String(a[2]) + String(a[1]) + String(a[0]));
    Serial.println("B: " + String(b[2]) + String(b[1]) + String(b[0]));
    */
    int tmp;
    tmp = (substractor(&c[0] , a[0] , b[0] , 0) & (negative_a ^ negative_b)) | (adder(&c[0] , a[0] , b[0] , 0) & !(negative_a ^ negative_b));
    c[2] = (substractor(&c[1] , a[1] , b[1] , tmp) & (negative_a ^ negative_b)) | (adder(&c[1] , a[1] , b[1] , tmp) & !(negative_a ^ negative_b));

    c[3] = (selectA & negative_a) | (negative_a & negative_b);
}
/**
 * The function to make sure the magnitude a is larger than b.
 * 1. check a,b's bits from MSB to LSB to select larger one.
 * 2. if a's 2nd bit > b's 2nd bit then tmp = a else tmp = b.
 */
void BigToA(){
    bool tmp[3] = {0,0,0};
    bool bit2 = (a[1] & !b[1]);                     //a,b's 2nd bit is 1 and 0 then a > b
    bool bit1 = (!(a[1] ^ b[1]) & (a[0] & !b[0]));  //a,b's 2nd bit is same ,and a,b's 1st bit is 1 and 0 then a > b

    tmp[2] = (a[2]  & selectA | b[2]  & !selectA);
    tmp[1] = (a[1]  & selectA | b[1]  & !selectA);
    tmp[0] = (a[0]  & selectA | b[0]  & !selectA);
    
    b[2] = (a[2]  & !selectA | b[2]  & selectA);
    b[1] = (a[1]  & !selectA | b[1]  & selectA);
    b[0] = (a[0]  & !selectA | b[0]  & selectA);

    a[2] = tmp[2];
    a[1] = tmp[1];
    a[0] = tmp[0];
    
}


bool adder(bool *s,bool a,bool b,bool cin){
    *s = a ^ b ^ cin;
    bool cout = (a&b) | (cin&(a^b));
    return cout;
}
bool substractor(bool *s,bool a,bool b,bool bin){
    *s = a ^ b ^ bin;
    bool bout = (!a & bin) | (!a & b) | (b & bin);
    return bout;
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
