# Consigna:

Este trabajo tiene como consigna diseñar un sistema planteado desde una máquina de estados (FSM).

El mismo será diagramado por entregas con fechas sugeridas, con el fin de concluirlo durante la cursada.

## Proyecto seleccionado:

### *Sistema de soldado SMD:*

Esta idea se basa en el concepto de simular una placa de   calentamiento para soldar componentes electrónicos SMD.

El control sigue un perfil o curva de reflow compuesto por distintas fases de temperatura y tiempo, con el objetivo de asegurar la soldadura correcta y evitar daños a los componentes. Estas curvas generalmente cuentan con distintas fases:

#### Precalentamiento o Preheat:
Se encarga de volatilizar el solvente de bajo punto de fusión en la pasta, los cuales incluyen resina, potenciador de viscosidad entre otros.

#### Soaking o remojo:
Esta fase tiene como objetivo lograr un temperatura uniforme sobre el PCB lo cual ayuda a reducir el impacto de la tensión térmica en la zona de reflujo y limita el levantamiento de grandes componentes. Además en esta etapa el fundente en la pasta comienza a reaccionar de manera activa garantizando que la soldadura fundida humedezca bien la superficie de soldadura.

#### Rampa de pico y Reflow (o reflujo):

En esta etapa se produce la fusión completa y la reacción de humectación para que la capa de compuesto intermetálico comience a formarse. El tiempo en alta temperatura (aprox llegando a los 217°C, sabiendo que los PCBs de aluminio soportan estables +240°C) debe ser lo mas corto posible siendo un ideal entre 30 y 60 segundos.

#### Cooling:
Un buen proceso de enfriamiento es fundamental para el resultado final de la soldadura. Es importante que la curva de de enfríado no sea pronunciada, ni muy rápida ni lenta. Un plazo de 30 a 50 segundos suele ser lo ideal. 


![Curva_reflow_1](https://github.com/fraansalo/informatica_2/blob/main/images/800px-RSS_Components_of_a_Profile1.svg.png?raw=true)
![Curva_reflow_1](https://github.com/fraansalo/informatica_2/blob/main/images/kester1.jpg?raw=true)


---
En las imagenes podemos ver algunos ejemplos de curvas de reflow que se utilizarán como guía para modelar la idea.


[Intro.pdf](https://github.com/fraansalo/informatica_2/blob/5d98e0c3dc995769c6904ed7fd2d0cfd7a1fc2f3/tp2/state%20Machine%20TP2_250828_113235_250828_114103.pdf)







