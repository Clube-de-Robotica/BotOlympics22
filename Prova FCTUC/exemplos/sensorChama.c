// =============================================================
// = Exemplo Sensor de Chama
// =
// = Este código permite ler os valores devolvidos pelo sensor
// = de chama. As entradas analógicas da placa arduino usada têm
// = um ADC de 8 bits, logo o valor é entre 0 a 1023.
// = Para obteres os valor limiar da deteção de chama observa os
// = valores devolvidos pelo sensor quando o mesmo está apontado
// = a uma vela acessa e quando está apontado apenas a luz
// = ambiente.
// =
// = Para testares o teu valor ajusta o flameTreshold para o
// = valor obtido, e verifica se o sensor está realmente a
// = detetar a chama
// =
// =============================================================

#define flameSensor A0

const int flameTreshold = 800;

void setup()
{
    Serial.begin(9600);
    Serial.print("Teste sensor Chama");
}

void loop()
{
    int sensorValue = analogRead(flameSensor);

    Serial.print("Valor Sensor: " + String(sensorValue));
    Serial.println("\tChama detetada: " + ((sensorValue >= flameTreshold) ? "Sim!" : "Não!"));
    delay(100);
}