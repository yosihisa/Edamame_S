#include <Edamame_S.h>

File myFile;

void setup() {

	Serial_PC.begin(9600);
	while (!Serial_PC) {
		;
	}

	Serial_PC.print("Initializing SD card...");

	if (!SD.begin(SD_CS)) {
		Serial_PC.println("initialization failed!");
		return;
	}
	Serial_PC.println("initialization done.");

	myFile = SD.open("test.txt", FILE_WRITE);
	if (myFile) {
		Serial_PC.print("Writing to test.txt...");
		myFile.println("Hello EDAMAME_S SDtest!");
		myFile.close();
		Serial_PC.println("done.");
	} else {
		Serial.println("error opening test.txt");
	}

	myFile = SD.open("test.txt");
	if (myFile) {
		Serial_PC.println("test.txt:");

		while (myFile.available()) {
			Serial_PC.write(myFile.read());
		}
		myFile.close();
	} else {
		Serial_PC.println("error opening test.txt");
	}
}

void loop() {
}