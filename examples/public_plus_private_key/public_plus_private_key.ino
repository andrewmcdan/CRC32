/*

CRC32 example

This program uses a private key and public key to generate a CRC32 hash. The private
key is stored in an array and is appended to the public key. The public key is 25
bytes obtained from the serial port. Once the 25 bytes have been received, the CRC 
is calculated and sent back down the serial port.

*/


#include <CRC32.h>

static char privateKey[11] = {'m','y',' ','p','a','s','s','w','o','r','d'};
char publicKey[25];
char seed[36];  // this array holds the concatenated seed (publicKey + privateKey)
int charCount = 0;

CRC32 CRC;  // initiate the crc library

void setup()
{
  
  Serial.begin(9600);
  
}

void loop()
{
  if(Serial.available()>0){
    Serial.write(Serial.peek());
    publicKey[charCount]=Serial.read();
    charCount++;
    if(charCount>24){  //  once we received 25 bytes, process them
      for(int i=0;i<37;i++){ 
        if(i<25){
          seed[i]=publicKey[i];  // add the 25 bytes to seed.
        }else{
          seed[i]=privateKey[i-25];  //  once all 25 are added, add in the privateKey
        }
      }
      Serial.println(CRC.crc_string(seed), HEX);  // calculate the crc and send it as ASCII encoded hexidecimal
      charCount=0;
    } 
  } 
}