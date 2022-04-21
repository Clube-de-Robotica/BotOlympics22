// =============================================================
// = Exemplo Scope Variáveis                    BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// = Descrição:
// = Este código demonstra o scope de variáveis com o mesmo nome
// = em C.
// =
// =============================================================

#include <Arduino.h>

int minhaVar = 10;

void minhaFuncao();

void setup()
{
    Serial.begin(9600);
    Serial.println("\n[ 0 ] - Exemplo Scope Variaveis");
}

void loop()
{
    // Print antes de iniciar a variável
    Serial.println("[ 1 ] - minhaVar no main antes: " + String(minhaVar));

    Serial.println("[ 2 ] - Iniciar a Variavel");

    // Iniciar a Variável
    int minhaVar = 20;

    // Print depois de iniciar a variável
    Serial.println("[ 3 ] - minhaVar no main depois: " + String(minhaVar));

    for (int i = 0; i < 3; i++)
    {
        // Variável dentro de um Loop
        int minhaVar = 3;
        Serial.println("[ 4 ] - minhaVar dentro do For Loop: " + String(minhaVar));
    }

    // Print depois do Loop
    Serial.println("[ 5 ] - minhaVar depois do For Loop: " + String(minhaVar));

    minhaFuncao();

    Serial.println("[ 7 ] - minhaVar depois da funcao: " + String(minhaVar));

    while (true)
    {
        ;
    }
}

void minhaFuncao()
{
    // Variavel dentro de uma função
    int minhaVar = 30;
    Serial.println("[ 6 ] - minhaVar dentro da função: " + String(minhaVar));
}