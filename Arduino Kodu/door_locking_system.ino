#include <LiquidCrystal.h> //kristal osilatör kullanmak için kütüphanesini dahil ediyoruz 
#include <Servo.h> //servo kütüphanesini dahil ediyoruz 
#include <Keypad.h> // keypad kütüphanesini dahil ediyoruz 
Servo myservo; //servomuzu tanımlıyoruz
int pos=0;
int sayac=0;// position of servo motor servomuzu ilk konumunu belirliyoruz 
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0); //kristal osilatörün arduinonun hangi pinlere başlanacağını seçiyoruz 
const byte rows=4; //satırlar için hafıza belirliyoruz 
const byte cols=3;//sütunlar için hafıza belirliyoruz 
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
}; //keypad butonlarının yerleşimini tanımıyoruz 
byte rowPins[rows]={0,1,2,3};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="1"; //parola için değişken oluşturuyoruz 
int currentposition=0;//ilk pozisyon bilgisini oluşturuyoruz 
 

 
void setup()
{
 
displayscreen();
//Serial.begin(9600); // seri haberleşme bandı değeri 
myservo.attach(9); //Servo motor bağlantısı 
 
lcd.begin(16,2);
 
}
 
void loop()
{
if(sayac<3 && currentposition==0)
{  
displayscreen();

int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SİFRE:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
 
lcd.print("*");
//keypress();
}
 
if (code==password[currentposition])
{
++currentposition;
sayac = sayac+1;
if(currentposition==4)
{
 
unlockdoor();
currentposition=0;
 
}
 
}
//keypad için açılma durumlarını belirliyoruz 
 
else
{
incorrect();
currentposition=0;
 
}//istenilen şartlar sağlanamadığı takdirde gitmesi gerken pozisyonu tanımlıyoruz
}
}
delay(500);
lcd.print("İCERİSİ BOS");
sayac = sayac++;
if (sayac >3){
lcd.print("İCERİSİ DOLU");
}
}
 
//------------------ Function 1- OPEN THE DOOR--------------//
 //kapı açma fonksiyonu 
void unlockdoor()
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Giris Onaylandi");
lcd.setCursor(4,1);
lcd.println("HOSGELDIN!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");

for(pos = 180; pos>=0; pos-=5) // open the door
{
myservo.write(pos); 
delay(5); 
}
delay(2000);
 
 
 
delay(1000);
counterbeep();
 
delay(1000);
 
for(pos = 0; pos <= 180; pos +=5) // close the door
{ // in steps of 1 degree
myservo.write(pos); 
delay(15);
 
 
currentposition=0;
 
lcd.clear();
displayscreen();
 
}
}//parola doğru girildiği taktirde kapıyı açmak için servo kodu 
 
//--------------------Function 2- Wrong code--------------//
 //parola yanlış olduğu taktirde 
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("yanlıs kod");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("GIREMEZSINIZ!!!");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("YANLIS KOD, GİRMEYE YETKİNİZ YOK");
delay(3000);
lcd.clear();
displayscreen();
}//parola yanlış girildiğinde ekranda yazacak bilgileri tanımlıyoruz
//-------Function 3 - CLEAR THE SCREEN--------------------/
// ekrandaki bilgileri temizleme fonksiyonu 
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}
//ekranda ki bilgileri temizlemek istediği zaman çalışacak fonksiyon
//------------Function 4 - DISPLAY FUNCTION--------------------//
//ekranın çalışma fonksiyonu 
void displayscreen()
{
 
lcd.setCursor(0,0);
lcd.println("KAPIYI ACMAK ICIN");
lcd.setCursor(1 ,1);
 
lcd.println("KODU GIRINIZ!!");
}

// ekranda açılırken yazacak bilgileri belirtiyoruz
 
//--------------Function 5 - Count down------------------//
// geriye doğru sayıcı fonksiyonu 
void counterbeep()
{
delay(1200);
 
 
lcd.clear();
 
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("GET IN WITHIN:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");

delay(1000);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("TEKRAR KITLENIYOR");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("KILITLI!");
delay(440);
}



//zamanla azalacak şekilde kilitleme için ekranda yazalıcak bilgiler belirtiliyor
