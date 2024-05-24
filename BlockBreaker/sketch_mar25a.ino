#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 17 // Reset pini 4 olarak tanımlanıyor
#define LIGHT_SENSOR_PIN A1
#define POTENTIOMETER_PIN A0
#define BUTTON_UP_PIN 11
#define BUTTON_DOWN_PIN 10
#define BUTTON_SELECT_PIN 9
#define HEALTH3_PIN 14
#define HEALTH2_PIN 15
#define HEALTH1_PIN 16
#define PALETTE_WIDTH 20
#define PALETTE_HEIGHT 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BLOCK_WIDTH 20 // Blok genişliği
#define BLOCK_HEIGHT 5
#define BLOCK_GAP_X 3 // Bloklar arasındaki yatay boşluk
#define BLOCK_GAP_Y 3 // Bloklar arasındaki dikey boşluk

int activeBlockCount = 0;
bool isSunny;
int life = 2;
int score = 0;
int digitone;
int digittwo;
int lightvalue;
bool returnmenu=false;
// Topun konumu ve hızı
int ballX, ballY;
float ballSpeedX = 3;
float ballSpeedY = 3;
int ballSize = 2;

// Blok yapılandırması
struct Block {
  int x;
  int y;
  bool isActive;
};

struct PowerUp {
  int x;
  int y;
  bool isActive;
};
#define POWERUP_SIZE 5 // Kalp boyutu
PowerUp powerUp;
PowerUp powerUp1;
bool isPowerUpActive = false;


#define MAX_BLOCKS 24 // Maksimum blok sayısı
Block blocks[MAX_BLOCKS];


int a=53;
int b=52;
int c=51;
int d=50;
int e=49;
int f=48;
int g=47;

int h=46;
int j=45;
int k=44;
int l=43;
int m=42;
int n=41;
int o=40;

const char *menuItems[] = {"START", "EXIT"};

Adafruit_SSD1306 display(OLED_RESET);
int selectedMenuItem = 0; // Başlangıçta seçili seçenek 0 (yani hiçbiri)

void setup() {
  
  lightvalue=analogRead(LIGHT_SENSOR_PIN);

  int score=0;
  int digitone=0;
  int digittwo=0;
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);
  pinMode(j,OUTPUT);
  pinMode(k,OUTPUT);
  pinMode(l,OUTPUT);
  pinMode(m,OUTPUT);
  pinMode(n,OUTPUT);
  pinMode(o,OUTPUT);


  pinMode(HEALTH1_PIN,OUTPUT);
  pinMode(HEALTH2_PIN,OUTPUT);
  pinMode(HEALTH3_PIN,OUTPUT);
  pinMode(BUTTON_SELECT_PIN,INPUT_PULLUP);
  pinMode(BUTTON_UP_PIN,INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN,INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN,INPUT);
  pinMode(LIGHT_SENSOR_PIN,INPUT);

   Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(24,10);
  display.println("BLOCK BREAKER");
  display.display();
  delay(200);
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(36,30);
  display.println("LOADING...");
  display.display();
  delay(300);
    // Topun başlangıç konumu (ekranın ortasında)
  ballX = (SCREEN_WIDTH - ballSize) / 2;
  ballY = (SCREEN_HEIGHT - ballSize) / 2;
  randomSeed(analogRead(0));
}

void loop() {
  display.clearDisplay();
  lightvalue=analogRead(LIGHT_SENSOR_PIN);
  isSunny=uselightSensor(lightvalue);
  uselightSensor(lightvalue);
  handleButtons();
  displayMenu();
  delay(10);
}

void handleButtons() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    selectedMenuItem--;
    if (selectedMenuItem < 0) {
      selectedMenuItem = 1; // Number of menu items - 1
    }
    while (digitalRead(BUTTON_UP_PIN) == LOW) {} // Wait for button release
    delay(10); // Debounce delay
  }

  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    selectedMenuItem++;
    if (selectedMenuItem > 1) {
      selectedMenuItem = 0;
    }
    while (digitalRead(BUTTON_DOWN_PIN) == LOW) {} // Wait for button release
    delay(10); // Debounce delay
  }

  if (digitalRead(BUTTON_SELECT_PIN) == LOW) {
    // Perform action based on selected menu item
    switch (selectedMenuItem) {
      case 0:
display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(36,30);
  display.println("LOADING...");
  display.display();
  returnmenu=false;
  score=0;
  
while(true){
showScore(score);
changeLeds();
        display.clearDisplay();
        lightvalue=analogRead(LIGHT_SENSOR_PIN);
  isSunny=uselightSensor(lightvalue);
        if(!isSunny){
      display.fillScreen(SSD1306_WHITE);
  }else{
    if(isSunny){
      display.fillScreen(SSD1306_BLACK);
    }
  }
        // Potansiyometrenin değerini oku ve paleti hareket ettir
  int potValue = analogRead(POTENTIOMETER_PIN);
  int paletteX = map(potValue, 0, 1023, 0, SCREEN_WIDTH - PALETTE_WIDTH);
  if(isSunny){
  display.fillRect(paletteX, SCREEN_HEIGHT - PALETTE_HEIGHT, PALETTE_WIDTH, PALETTE_HEIGHT, WHITE);

  }else{
  display.fillRect(paletteX, SCREEN_HEIGHT - PALETTE_HEIGHT, PALETTE_WIDTH, PALETTE_HEIGHT, BLACK);
  }

  // Topu hareket ettir
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Topun ekranın kenarlarına çarpmasını kontrol et ve ters yönde hareket ettir
  if (ballX - ballSize / 2 <= 0 || ballX + ballSize / 2 >= SCREEN_WIDTH) {
    ballSpeedX = -ballSpeedX;
  }
  if (ballY + ballSize / 2 >= SCREEN_HEIGHT) {
    if (life > 0) {
      life -= 1;
      //ballX = random(ballSize / 2, SCREEN_WIDTH - ballSize / 2);
      //ballY = random((BLOCK_HEIGHT + BLOCK_GAP_Y) * 4+2, SCREEN_HEIGHT - ballSize-2-PALETTE_HEIGHT);
      ballX = paletteX + PALETTE_WIDTH /2;
      ballY = SCREEN_HEIGHT - PALETTE_HEIGHT -2;
      delay(2000);
    } 
    if(life==0) {
      returnmenu=true;
      changeLeds();  
      display.clearDisplay();
      delay(1000);
      display.setTextSize(2);            
      display.setTextColor(SSD1306_WHITE); 
      display.setCursor(SCREEN_WIDTH/2-55, SCREEN_HEIGHT/2-5);       
      display.print("GAME OVER");         
      display.display(); 
      delay(3000);
      display.clearDisplay();
      display.setCursor(SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2-10);       
      display.print("Score: "+String(score)); 
      display.display(); 
      delay(3000);
      score=0;
      ballSpeedX = 3;
      ballSpeedY = 3;
      activeBlockCount = 0;
      for (int i = 0; i < MAX_BLOCKS; i++) {
    if (blocks[i].isActive) {
        blocks[i].isActive = false;
    }
    }
      showScore(score);
  life=3;

  
  }
  }
  if(ballY - ballSize / 2 <= 0){
    ballSpeedY = -ballSpeedY;
  }

  // Topun paletle çarpışmasını kontrol et
  if (ballY + ballSize + 2 / 2 >= SCREEN_HEIGHT - PALETTE_HEIGHT && ballX + ballSize / 2 >= paletteX && ballX - ballSize / 2 <= paletteX + PALETTE_WIDTH) {
    ballSpeedY = -ballSpeedY; // Top paletle çarpıştığında yönünü tersine çevir
  }
    checkCollisionWithPalette(paletteX); 


  // Blokların çarpışmasını kontrol et
 // Blokların çarpışmasını kontrol et
 // Aktif blok sayısını takip etmek için bir değişken
  for (int i = 0; i < MAX_BLOCKS; i++) {
    if (blocks[i].isActive) {
      activeBlockCount++; // Her aktif blok için sayacı artır
      if (ballX + ballSize + 2 / 2 >= blocks[i].x && ballX - ballSize / 2 <= blocks[i].x + BLOCK_WIDTH &&
          ballY + ballSize / 2 >= blocks[i].y && ballY - ballSize / 2 <= blocks[i].y + BLOCK_HEIGHT) {
        // Top bloğa çarptıysa, bloğu etkisiz hale getir
        blocks[i].isActive = false;
        ballSpeedY = -ballSpeedY; // Topun yönünü tersine çevir
        score+=1;
        if (random(0,10) == 0 ) { // Yüzde 10 şansla
    if (!powerUp.isActive) { // Eğer ilk power-up aktif değilse
        powerUp.x = blocks[i].x + BLOCK_WIDTH / 2; // Bloğun ortasına yerleştir
        powerUp.y = blocks[i].y + BLOCK_HEIGHT / 2; // Bloğun ortasına yerleştir
        powerUp.isActive = true; // Power-up'u aktif et
    } else if (!powerUp1.isActive) { // Eğer ilk power-up aktif değilse
        powerUp1.x = blocks[i].x + BLOCK_WIDTH / 2; // Bloğun ortasına yerleştir
        powerUp1.y = blocks[i].y + BLOCK_HEIGHT / 2; // Bloğun ortasına yerleştir
        powerUp1.isActive = true; // Power-up'u aktif et
    }
}
      /*display.setTextSize(1);            
      display.setTextColor(SSD1306_WHITE); 
      display.setCursor(SCREEN_WIDTH-4, 4);           
      display.print(score);          
      display.display();*/ 
      showScore(score);
      }
    }
  }
  // Renk değişkenini tanımla
uint16_t ballColor;

// isSunny değişkenine göre renk belirle
if (!isSunny) {
    ballColor = BLACK; // Güneşli olmayan durumda beyaz renk
} else {
    ballColor = WHITE; // Güneşli olduğunda siyah renk
}
  drawPowerUp(ballColor);
    movePowerUp();

  // Eğer tüm bloklar yok edilmişse, yeni bloklar oluştur
  if (activeBlockCount == 0) {
    delay(5000);
    ballSpeedX *= 1.20;
    ballSpeedY *= 1.20;
    ballX = paletteX + PALETTE_WIDTH /2;
    ballY = SCREEN_HEIGHT - PALETTE_HEIGHT -2;
    powerUp1.isActive = false;
    powerUp.isActive = false;
    drawBlocks(); // Yeni blokları oluştur
  }

  // Blokları çiz
  for (int i = 0; i < MAX_BLOCKS; i++) {
    if (blocks[i].isActive) {

      if(isSunny){
                display.fillRect(blocks[i].x, blocks[i].y, BLOCK_WIDTH, BLOCK_HEIGHT, WHITE);
      }else{
                display.fillRect(blocks[i].x, blocks[i].y, BLOCK_WIDTH, BLOCK_HEIGHT, BLACK);
      }
    }
  }
  movePowerUp();

// Topu çiz
display.fillCircle(ballX, ballY, ballSize, ballColor);


  // Ekrana çizilenleri göster
  display.display();
  // Biraz bekle
  //delay(10);
  if(returnmenu){
    break;
  }
}
      break;
      case 1:
        display.clearDisplay();
      
        
        display.setCursor(10,30);
        display.println("Thank you for your interest.");
        display.display();
        delay(2000);
        
        while(true){}
        break;
      
    }
    while (digitalRead(BUTTON_SELECT_PIN) == LOW) {} // Wait for button release
    delay(20); // Debounce delay
  }
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
 

  for (int i = 0; i < 2; i++) { // Number of menu items
    // Define button dimensions
    int buttonWidth = 60;
    int buttonHeight = 10;
    int buttonX = 34; // X position of the button
    int buttonY = 24 + i * 12; // Y position of the button

    // Draw the button outline
    display.drawRect(buttonX, buttonY, buttonWidth, buttonHeight, SSD1306_WHITE);

    // Set the text position inside the button
    int textX = buttonX + (buttonWidth - strlen(menuItems[i]) * 6) / 2; // Center text horizontally
    int textY = buttonY + (buttonHeight - 8) / 2; // Center text vertically

    // Display the menu item text
    display.setCursor(textX, textY);
    if (selectedMenuItem == i) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Invert colors for selected item
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.println(menuItems[i]);
  }

  display.display();
}


void changeLeds(){
  if(life==0){
  digitalWrite(HEALTH1_PIN, LOW);
  digitalWrite(HEALTH2_PIN, LOW);
  digitalWrite(HEALTH3_PIN, LOW);
  }else if(life==1){
  digitalWrite(HEALTH1_PIN, HIGH);
  digitalWrite(HEALTH2_PIN, LOW);
  digitalWrite(HEALTH3_PIN, LOW);
  }else if(life==2){  
  digitalWrite(HEALTH1_PIN, HIGH);
  digitalWrite(HEALTH2_PIN, HIGH);
  digitalWrite(HEALTH3_PIN, LOW);
  }else if(life==3){
    digitalWrite(HEALTH1_PIN, HIGH);
  digitalWrite(HEALTH2_PIN, HIGH);
  digitalWrite(HEALTH3_PIN, HIGH);
  }
}

void zeroforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,1);
  digitalWrite (f,1);
  digitalWrite (g,0);
  delay (5);
}
void oneforsecond(){
  digitalWrite (a,0);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,0);
  digitalWrite (e,0);
  digitalWrite (f,0);
  digitalWrite (g,0);
  delay (5);
}
void twoforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,0);
  digitalWrite (d,1);
  digitalWrite (e,1);
  digitalWrite (f,0);
  digitalWrite (g,1);
  delay (5);
}
void threeforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,0);
  digitalWrite (f,0);
  digitalWrite (g,1);
  delay (5);
}
void fourforsecond(){
  digitalWrite (a,0);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,0);
  digitalWrite (e,0);
  digitalWrite (f,1);
  digitalWrite (g,1);
  delay (5);
}

void fiveforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,0);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,0);
  digitalWrite (f,1);
  digitalWrite (g,1);
  delay (5);
}
void sixforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,0);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,1);
  digitalWrite (f,1);
  digitalWrite (g,1);
  delay (5);
}
void sevenforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,0);
  digitalWrite (e,0);
  digitalWrite (f,0);
  digitalWrite (g,0);
  delay (5);
}

void eightforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,1);
  digitalWrite (f,1);
  digitalWrite (g,1);
  delay (5);
}

void nineforsecond(){
  digitalWrite (a,1);
  digitalWrite (b,1);
  digitalWrite (c,1);
  digitalWrite (d,1);
  digitalWrite (e,0);
  digitalWrite (f,1);
  digitalWrite (g,1);
  delay (5);
}

void zero() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 1);
  digitalWrite(n, 1);
  digitalWrite(o, 0);
  delay(5);
}

void one() {
  digitalWrite(h, 0);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 0);
  digitalWrite(m, 0);
  digitalWrite(n, 0);
  digitalWrite(o, 0);
  delay(5);
}

void two() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 0);
  digitalWrite(l, 1);
  digitalWrite(m, 1);
  digitalWrite(n, 0);
  digitalWrite(o, 1);
  delay(5);
}

void three() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 0);
  digitalWrite(n, 0);
  digitalWrite(o, 1);
  delay(5);
}

void four() {
  digitalWrite(h, 0);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 0);
  digitalWrite(m, 0);
  digitalWrite(n, 1);
  digitalWrite(o, 1);
  delay(5);
}

void five() {
  digitalWrite(h, 1);
  digitalWrite(j, 0);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 0);
  digitalWrite(n, 1);
  digitalWrite(o, 1);
  delay(5);
}

void six() {
  digitalWrite(h, 1);
  digitalWrite(j, 0);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 1);
  digitalWrite(n, 1);
  digitalWrite(o, 1);
  delay(5);
}

void seven() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 0);
  digitalWrite(m, 0);
  digitalWrite(n, 0);
  digitalWrite(o, 0);
  delay(5);
}

void eight() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 1);
  digitalWrite(n, 1);
  digitalWrite(o, 1);
  delay(5);
}

void nine() {
  digitalWrite(h, 1);
  digitalWrite(j, 1);
  digitalWrite(k, 1);
  digitalWrite(l, 1);
  digitalWrite(m, 0);
  digitalWrite(n, 1);
  digitalWrite(o, 1);
  delay(5);
}

void showScore(int score) {
digitone=score / 10;
digittwo=score % 10;
    // 7 segment ekranına skoru göster
    switch (digitone) {
      case 0:
        zero();
        break;
      case 1:
        one();
        break;
      case 2:
        two();
        break;
      case 3:
        three();
        break;
      case 4:
        four();
        break;
      case 5:
        five();
        break;
      case 6:
        six();
        break;
      case 7:
        seven();
        break;
      case 8:
        eight();
        break;
      case 9:
        nine();
        break;
    }

    switch (digittwo) {
       case 0:
        zeroforsecond();
        break;
      case 1:
        oneforsecond();
        break;
      case 2:
        twoforsecond();
        break;
      case 3:
        threeforsecond();
        break;
      case 4:
        fourforsecond();
        break;
      case 5:
        fiveforsecond();
        break;
      case 6:
        sixforsecond();
        break;
      case 7:
        sevenforsecond();
        break;
      case 8:
        eightforsecond();
        break;
      case 9:
        nineforsecond();
        break;
    }
}

bool uselightSensor(int lightvalue){
  if(lightvalue>500){
    return true;
  }else{
    return false;
  }
}

// Blokları çizen fonksiyon
void drawBlocks() {
  randomSeed(analogRead(0));

  int totalRows = min(4, SCREEN_HEIGHT / (BLOCK_HEIGHT + BLOCK_GAP_Y)); // Maksimum 4 satır olacak şekilde satır sayısını belirle
  int totalColumns = SCREEN_WIDTH / (BLOCK_WIDTH + BLOCK_GAP_X); // Toplam sütun sayısı
  int columnWidth = SCREEN_WIDTH / totalColumns; // Her sütunun genişliği

  int blockCountPerRow = SCREEN_WIDTH / (BLOCK_WIDTH + BLOCK_GAP_X); // Bir satırdaki blok sayısı

  int blockIndex = 0;
  // Her satır için blokları oluştur
  for (int y = 0; y < totalRows; y++) {
    // Her satırda maksimum blok sayısını belirle
    int blockRowCount = random(1, blockCountPerRow+1);

    // Blokları çiz
    for (int x = 0; x < blockRowCount; x++) {
      int blockX = x * (BLOCK_WIDTH + BLOCK_GAP_X);
      int blockY = y * (BLOCK_HEIGHT + BLOCK_GAP_Y);
      blocks[blockIndex].x = blockX;
      blocks[blockIndex].y = blockY;
      blocks[blockIndex].isActive = true;
      blockIndex++;
    }
    // Blok indeksi maksimuma ulaştığında döngüyü sonlandır
    if (blockIndex >= MAX_BLOCKS) {
      break;
    }
  }
}


void movePowerUp() {
  if (powerUp.isActive){
  powerUp.y += 1; // Powerup'u aşağıya doğru hareket ettir
  if(powerUp.y >= SCREEN_HEIGHT){
    powerUp.isActive = false;
  }
  }
  if (powerUp1.isActive){
  powerUp1.y += 1; // Powerup'u aşağıya doğru hareket ettir
  }
  if(powerUp1.y >= SCREEN_HEIGHT){
    powerUp1.isActive = false;
  }
}





void checkCollisionWithPalette(int paletteX) {
  if (powerUp.isActive && powerUp.y + POWERUP_SIZE - 2 >= SCREEN_HEIGHT - PALETTE_HEIGHT && powerUp.x + POWERUP_SIZE >= paletteX && powerUp.x <= paletteX + PALETTE_WIDTH) {
        if(life >= 3){
          life=3;
        }
    else{
      life+=1;
    }
        powerUp.isActive = false; // Disable the powerup
  }
    if (powerUp1.isActive && powerUp1.y + POWERUP_SIZE - 2 >= SCREEN_HEIGHT - PALETTE_HEIGHT && powerUp1.x + POWERUP_SIZE >= paletteX && powerUp1.x <= paletteX + PALETTE_WIDTH) {
        if(life >= 3){
          life=3;
        }
    else{
      life+=1;
    }
          powerUp1.isActive = false; // Disable the powerup
    }
    /*display.setTextSize(1);            
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(SCREEN_WIDTH - 4, 4);           
    display.print(life);          
    display.display(); */
}


void drawHeart(int x0, int y0, int size, uint16_t color) {
  int y, x;
  for (y = size / 2; y >= -size / 4; --y) {
    float x_val = size / 2 - abs(y);
    for (x = -x_val; x <= x_val; ++x) {
      display.drawPixel(x0 + x, y0 + y, color);
      float dx = x - 0.2 * x_val * (abs(y) / (size / 2));
      if ((abs(y) > 0.6 * size / 2 && abs(dx) < 0.4 * x_val) ||
          (abs(y) > 0.1 * size / 2 && abs(dx) < 0.8 * x_val))
        display.drawPixel(x0 + x, y0 + y, BLACK);
    }
  }
}

void drawPowerUp(uint16_t color) {
  if (powerUp.isActive) {
    drawHeart(powerUp.x, powerUp.y,POWERUP_SIZE, color);
  }
  if (powerUp1.isActive) {
    drawHeart(powerUp1.x, powerUp1.y,POWERUP_SIZE, color);
  }
}