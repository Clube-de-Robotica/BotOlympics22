# Prova FCTUC

## Hardware Robô

### Pin Mapping

| Pino Arduino |        Hardware       |            Notas           |
|:------------:|:---------------------:|:--------------------------:|
|       0      |           RX          |     Comunicação Serial     |
|       1      |           TX          |     Comunicação Serial     |
|       2      |       ----------      |         ----------         |
|       3      |       ----------      |         ----------         |
|       4      |     Motor 1 - Dir     |         ----------         |
|       5      |     Motor 1 - PWM     |         ----------         |
|       6      |     Motor 2 - PWM     |         ----------         |
|       7      |      LED NeoPixel     |         ----------         |
|       8      |     Motor 2 - Dir     |         ----------         |
|       9      |         Buzzer        |         ----------         |
|      10      |  XSHUT LiDAR Direita  |         ----------         |
|      11      |   XSHUT LiDAR Frente  |         ----------         |
|      12      |  XSHUT LiDAR Esquerda |         ----------         |
|      13      |      LED Arduino      |       LED Incorporado      |
|      A0      | Sensor infravermelhos |         ----------         |
|      A1      |         Botão         | Utilizar como pino digital |
|      A2      |       Ventoinha       | Utilizar como pino digital |
|      A3      |       ----------      |         ----------         |
|      A4      |      SDA Sensores     |     Sensor Cor / LiDAR     |
|      A5      |      SCL Sensores     |     Sensor Cor / LiDAR     |

### Motores

O Robô está equipado com 2 motores, controlados atráves de uma *H-Bridge* DRV8833.

#### Truth Table DRV8833

| INx-1 | INx-2 | Mx-1 | Mx-2 |        Função        |
|:-----:|:-----:|:----:|:----:|:--------------------:|
|   0   |   0   |   Z  |   Z  |    Abrandar Lento    |
|   0   |   1   |   L  |   H  |    Sentido Horário   |
|   1   |   0   |   H  |   L  | Sentido Anti-Horário |
|   1   |   1   |   L  |   L  |        Travar        |

L -> Ligado a GND <br/>
H -> Ligado a VCC <br/>
Z -> Alta Impedância <br/>


Tendo em conta a tabela anterior é possível controlar a velocidade dos motores da seguinte forma

| Dir |   PWM   |        Função        |
|:---:|:-------:|:--------------------:|
|  0  |    0    |    Abrandar Lento    |
|  0  |   PWM   |    Sentido Horário   |
|  1  | 1 - PWM | Sentido Anti-Horário |
|  1  |    1    |        Travar        |

Considerando o 0 < PWM < 1, adptando para o valor usado pelo arduino (0 < PWM < 255) -> 255 - PWM.

Tratando-se de um robô com condução diferencial, é possível fazer o robô mudar de direção ao aumentar (ou diminuir) a velocidade de uma roda em relação à outra.

**INSERIR IMAGEM CONDUÇÃO DIFERENCIAL**

### Sensores

#### Sensor de Chama

Para detetar a vela o robô dispõe de um sensor de infravermelhos. 
O sensor é capaz de     