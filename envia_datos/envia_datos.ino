
#include <ESP8266WiFi.h>

const char* ssid     = "************";
const char* password = "************";

const char* host = "192.168.0.5";
int httpPort = 81;

WiFiClient client;

void setup() {
	Serial.begin(115200);
	delay(10);

	// Nos conectamos a nuestro wifi

	Serial.println();
	Serial.println();
	Serial.print("Conectando a ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("Conectado a WIFI");  
	Serial.print("IP : ");
	Serial.println(WiFi.localIP());
}

void loop() {
	delay(2000);

	Serial.print("Conectando a ");
	Serial.println(ssid);

	if (!client.connect(host, httpPort)) {
		Serial.println("No conectado...");
		return;
	}

	// Creamos la dirección para luego usarla en el String del POST que tendremos que enviar
	String url = "http://192.168.0.5/IOT/ingreso.php";

	// creo un string con los datos que enviaré por POST lo creo de antemano para luego poder 
	// calcular el tamaño del string dato que necesitare para enviar por post
	String data = "serie=777&temp=33";

	//imprimo la url a donde enviaremos la solicitud, solo para debug
	Serial.print("Enviando datos a: ");
	Serial.println(url +"?"+ data);

	// Esta es la solicitud del tipoPOST que enviaremos al servidor
	client.print(String("POST ") + url + " HTTP/1.0\r\n" +
	"Host: " + host + "\r\n" +
	"Accept: *" + "/" + "*\r\n" +
	"Content-Length: " + data.length() + "\r\n" +
	"Content-Type: application/x-www-form-urlencoded\r\n" +
	"\r\n" + data);
	delay(10);

	// Leemos todas las lineas que nos responde el servidor y las imprimimos por pantalla, esto no es necesario  pero es fundamental ver què me responde el servidor para localizar fallas en la solicitud post que estoy enviando, 
	Serial.print("Respuesta del servidor:");
	while(client.available()){
		String line = client.readStringUntil('\r');
		Serial.print(line);
	}

	Serial.println();

	// se cierra la conexión
	Serial.println("Conexion cerrada.");

}
