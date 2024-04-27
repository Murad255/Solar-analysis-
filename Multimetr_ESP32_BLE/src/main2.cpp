#include <Arduino.h>

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>

// #define SERVICE_UUID "3e3593cf-e5cb-46ee-8fa4-16c8b6a563d0"
// #define UUID_CHARACT "beb5483e-36e1-4688-b7f5-ea07361b26a8"
// #define UUID_SPEED "0c8e747d-b4f4-40b6-9288-bc500e47b856"

// BLEServer *pServer = NULL;
// BLECharacteristic *pCharacteristic = NULL;

// int SpeedMove = 10; //миллиметров в сек

// void startAdvertising()
// { //функция запуска видимсти
// 	// BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
// 	// pAdvertising->addServiceUUID(SERVICE_UUID);
// 	// pServer->getAdvertising()->start();
// 	 BLEAdvertising *pAdvertising = pServer->getAdvertising();
//      pAdvertising->start();
// }

// class CharactCallbacks : public BLECharacteristicCallbacks
// {
// 	void onWrite(BLECharacteristic *pCharacteristic)
// 	{ //Функция onWrite вызывается, когда в данную характеристику поступает информация.
// 		std::string value = pCharacteristic->getValue();
// 		Serial.println(value.c_str());
// 		pCharacteristic->setValue("aa");
// 	}
// };
// class SpeedCallbacks : public BLECharacteristicCallbacks
// {
// 	void onWrite(BLECharacteristic *pSpeed)
// 	{
// 		std::string value = pSpeed->getValue();
// 		SpeedMove = atoi(value.c_str());
// 		// Serial.println(SpeedMove);
// 	}
// };

// class ServerCallbacks : public BLEServerCallbacks
// {
// 	void onConnect(BLEServer *pServer)
// 	{
// 		Serial.println("Connected");
// 	};
// 	void onDisconnect(BLEServer *pServer)
// 	{
// 		Serial.println("Disconnected");
// 		startAdvertising();
// 	}
// };

// void setup()
// {
// 	Serial.begin(115200);
// 	BLEDevice::init("MyESP32");
// 	BLEServer *pServer = BLEDevice::createServer();
// 	BLEService *pService = pServer->createService(SERVICE_UUID);

// 	BLECharacteristic *pCharacteristic = pService->createCharacteristic( //запуск движения и прием данных
// 		UUID_CHARACT,
// 		BLECharacteristic::PROPERTY_READ |
// 			BLECharacteristic::PROPERTY_WRITE);
// 	BLECharacteristic *pSpeed = pService->createCharacteristic( //передача скорости движения
// 		UUID_SPEED,
// 		BLECharacteristic::PROPERTY_READ |
// 			BLECharacteristic::PROPERTY_WRITE);
// 	BLECharacteristic *nameCharacteristic = pService->createCharacteristic(
// 		BLEUUID((uint16_t)0x2A00), BLECharacteristic::PROPERTY_READ);

// 	pCharacteristic->setCallbacks(new CharactCallbacks()); //колбэк на входящие сообщения
// 	pSpeed->setCallbacks(new SpeedCallbacks());
// 	pServer->setCallbacks(new ServerCallbacks()); //колбэк на подключение

// 	pCharacteristic->setValue("Hello World");
// 	pService->start();
// 	startAdvertising();
// }

// void loop()
// {
// 	// put your main code here, to run repeatedly:
// 	Serial.println(SpeedMove);
// 	delay(2000);
// }
