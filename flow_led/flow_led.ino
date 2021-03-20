#define BTN_PIN 2
/*
#define LED1_PIN 3
#define LED2_PIN 5
#define LED3_PIN 6
#define LED4_PIN 9
#define LED5_PIN 10
#define LED6_PIN 11
*/
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 4
#define LED4_PIN 5
#define LED5_PIN 6
#define LED6_PIN 7

#define MAX_INTENSITY 255
#define FADE_AMONT 64
#define DELAYTIME 100

#define LEFT true
#define RIGHT false 

bool direc = true;
int8_t cur_led = 1;
bool pause = false;

void setup()
{
    pinMode(BTN_PIN, INPUT);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    pinMode(LED6_PIN, OUTPUT);
    Serial.begin(9600);
}
void loop()
{
    
    pause = digitalRead(BTN_PIN) ? !pause : pause;
    if (Serial.available())
    {
        pause = !(Serial.read() & '0') | 0;
    }
    
    
    if(!pause){
        direc ? cur_led++ : cur_led-- ;
        update();
        direc = cur_led == 8 || cur_led == -1 ? !direc : direc;
    }
    delay(DELAYTIME);
  //  Serial.println(cur_led);
}
void update(){
    if (direc == LEFT)
    {
        for (int8_t i = 1; i < 7; i++)
        {
            i > cur_led ? led_off(i) : led_on(i ,bound(MAX_INTENSITY - abs(cur_led - i) * FADE_AMONT));
        }
    }else{
        for (int8_t i = 1; i < 7; i++)
        {
            i < cur_led ? led_off(i) : led_on(i ,bound(MAX_INTENSITY - abs(i - cur_led) * FADE_AMONT));
        }
    }
    
}
int bound(int x){
    if (x > 255) x = 255;
    if (x < 0) x = 0;
    return x;
}
void led_off(uint8_t no){
    led_on(no ,0);
}
void led_on(uint8_t no,int16_t intensity){
    
    switch (no)
    {
    case 1:
        analogWrite(LED1_PIN , intensity);
        break;
    case 2:
        analogWrite(LED2_PIN , intensity);
        break;
    case 3:
        analogWrite(LED3_PIN , intensity);
        break;
    case 4:
        analogWrite(LED4_PIN , intensity);
        break;
    case 5:
        analogWrite(LED5_PIN , intensity);
        break;
    case 6:
        analogWrite(LED6_PIN , intensity);
        break;
    default:
        break;
    }
}