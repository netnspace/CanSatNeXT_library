/*
  This example shows more methods for manipulating files.
*/


#include <CanSatNeXT.h>

void setup() {
  Serial.begin(115200);
  CanSatInit();


  // Print all file names and directories on the SD-card.
  printFileSystem();

  // Create a new directory
  newDir("/testDir");
  
  // Write to a file. "Write" means overwriting any existing data. 
  // Usually you would use appendFile instead.
  writeFile("/testDir/testfile.txt", "This is some text\r\n");

  // append adds data to the end of the file, not overwriting the old data.
  appendFile("/testDir/testfile.txt", "This is more text\r\n");

  // Let's read all data from the file we just used.
  String str = readFile("/testDir/testfile.txt");
  Serial.println(str);
  // Note that using readFile might cause problems if the file is very large.


  // Check if the file exists
  if(fileExists("/testDir/testfile.txt")) Serial.println("testfile exists");

  // Read size of the file
  int length = fileSize("/testDir/testfile.txt");
  Serial.println(length);

  // Rename the file
  renameFile("/testDir/testfile.txt", "/testDir/testfile2.txt");

  // Check if a file exists with the old name
  if(!fileExists("/testDir/testfile.txt")) Serial.println("testfile doesn't exist");

  // Check if a file exists with the new name
  if(fileExists("/testDir/testfile2.txt")) Serial.println("testfile2 exists");

  // Delete the new file
  deleteFile("/testDir/testfile2.txt");

  // Check if the new file exists after deletion
  if(!fileExists("/testDir/testfile2.txt")) Serial.println("testfile2 doesn't exist");

  // Delete the whole directory we made
  deleteDir("/testDir/");

  // Check if the directory exists after deletion
  if(!fileExists("/testDir/")) Serial.println("testDir doesn't exist");

  // We can also read the mechanical switch from the SD-card connector, indicating if a card is present or not
  // Note that the polarity may vary, so on some boards the result may be flipped.
  bool cardPresent = SDCardPresent();
  if(cardPresent)
  {
    Serial.println("SD card is connected");
  }else{
    Serial.println("SD card is not connected");
  }
}


// Nothing to now, let's blink a LED to show the code is now.
void loop() {
  delay(500);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
}
