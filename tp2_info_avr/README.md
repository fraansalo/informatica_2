
# Sistema de soldado SMD:


## 📌 Descripción:

Esta idea se basa en el concepto de simular una placa de calentamiento para soldar componentes electrónicos SMD.

El control sigue un perfil o curva de reflow compuesto por distintas fases de temperatura y tiempo, con el objetivo de asegurar la soldadura correcta y evitar daños a los componentes.

###  Características principales:
```c
🧩 Máquinas de estado independientes para Manual y Reflow.
🌡️ Lectura de temperatura(LM35).
🔥 Control ON/OFF con histeresis (relay).
⏱️ Implementación de timers por software vía interrupción.
🎛️ Menú controlado por botones fisicos.
🖥️ Telemetría completa vía UART (tiempos, temperatura).
🧪 Simulación completa en Proteus.
```

## Etapas definidas del proceso:

#### `Precalentamiento o Preheat`:
Se encarga de volatilizar el solvente de bajo punto de fusión en la pasta, los cuales incluyen resina, potenciador de viscosidad entre otros.

#### `Soaking o remojo`:
Esta fase tiene como objetivo lograr un temperatura uniforme sobre el PCB lo cual ayuda a reducir el impacto de la tensión térmica en la zona de reflujo y limita el levantamiento de grandes componentes. Además en esta etapa el fundente en la pasta comienza a reaccionar de manera activa garantizando que la soldadura fundida humedezca bien la superficie de soldadura.

#### `Rampa de pico y Reflow (o reflujo)`:

En esta etapa se produce la fusión completa y la reacción de humectación para que la capa de compuesto intermetálico comience a formarse. El tiempo en alta temperatura (aprox llegando a los 217°C, sabiendo que los PCBs de aluminio soportan estables +240°C).
Debe ser lo mas corto posible siendo un ideal entre 30 y 60 segundos.

#### `Cooling`:
Un buen proceso de enfriamiento es fundamental para el resultado final de la soldadura. Es importante que la curva de de enfríado no sea pronunciada, ni muy rápida ni lenta. Un plazo de 30 a 50 segundos suele ser lo ideal. 

---

## Ilustraciones de referencia.

    Se observa el paso a paso de la temperatura entre las etapas del soldado recomendado por marcas del mercado de estaño en pasta.

>![Curva_reflow_1](https://github.com/fraansalo/informatica_2/blob/main/images/800px-RSS_Components_of_a_Profile1.svg.png?raw=true)
>![Curva_reflow_2](https://github.com/fraansalo/informatica_2/blob/main/images/kester1.jpg?raw=true)

---


## Funcionamiento Básico:

Para establecer una idea funcional, y versatil se decidió que dentro del funcionamiento base, que sería seguir una curva de reflow genérica que funcione para la mayoría de pastas para soldar, se agregara un modo adicional:

**`1️⃣ Modo Manual`**: Se establecerá un SetPoint por el usuario, el cual indicará una temperatura a la que se deberá alcanzar. Se mantendrá en esa temperatura por un tiempo determinado y luego se procede a enfríar. El modo de setear este SetPoint será por medio de los botones fisicos `Up` y `down`que aumentarán o bajarán la temperatura con pasos de **`10°C`**.

```c
1. Usuario selecciona objetivo de temperatura (±10 °C por pulsación).
2. Presiona ENTER para comenzar.
3. El sistema calienta hasta alcanzar el setpoint.
4. Mantiene la temperatura por TIM_MANUAL_HOLD segundos.
5. Enfría hasta TEMP_COOLED.
6. Finaliza y vuelve a MENU_IDLE
```

<div align="center"><b>Máquina de estados – Manual</b></div>

```
                                        SETPOINT → HOLD → COOLING → EXIT
```
**`2️⃣ Modo Reflow (Curva)`**: En este modo la temperatura seguirá el ciclo de la curva de reflujo o reflow para el uso específico de pastas de soldar.

```c
//Etapas controladas:

1. PREHEAT → Calentamiento suave hasta ~150 °C
2. SOAK → Estabilización térmica (90 s)
3. RAMP → PEAK → Subida hasta ~220–230 °C y permanencia controlada
4. COOLING → Enfriado moderado hasta temperatura segura
```

<div align="center"><b>Máquina de estados – Reflow</b></div>

```
                                    PREHEAT → SOAK → RAMP → PEAK → COOLING → EXIT
```

### Botones: 

Nuestra máquina de estados incluye el ingreso y selección del modo por medio del usuario usando botones definidos:

- **`Enter`** Ingreso a la función definida del modo correspondiente.

- **`Select`** Selección del modo de funcionamiento. (Manual ; Reflow)

- **`DOWN`** Útil en el modo Manual. Disminuye el valor del setpoint en -10°C.

- **`UP`** Útil en el modo Manual. Aumenta el valor del setpoint en +10°C.

---
## Diagramas de estado:

Para poder visualizar de manera más clara y técnica del funcionamiento, se esbozó un diagrama de máquinas de estado preliminar como boceto:
[**Boceto Maquina de estados.pdf**](https://github.com/fraansalo/informatica_2/blob/5d98e0c3dc995769c6904ed7fd2d0cfd7a1fc2f3/tp2/state%20Machine%20TP2_250828_113235_250828_114103.pdf)


En ese boceto se podrá ver de manera general como es la idea del funcionamiento del proyecto en sí con sus distintas fases. Se irá evaluando los nombres de las variables definitivos a medida que el código se valla desarrollando. 
Tras retoque de detalles este sería el resultado final del diagrama de la máquina de estados:

>![diagrama_maquinaestados](https://github.com/fraansalo/informatica_2/blob/b4c3982caba6b040ab1e8da4ddf514fa8bb27a62/images/diagrama_terminado.png)


### Material Consultado:

    Canal: GreatScott!

<div align="center">
  <a href="https://www.youtube.com/watch?v=QarizoUnRfk" target="_blank">
    <img src="https://img.youtube.com/vi/QarizoUnRfk/hqdefault.jpg" 
         alt="The Best way to Solder? Hot Plate to the rescue!"
         style="width:70%; border-radius:10px; border:1px solid #555;">
  </a>
  <br><br>
  <b style="font-size:20px;">The Best way to Solder? Hot Plate to the rescue!</b>
  <br>
</div>


---

    Canal: Electronoobs

<div align="center">
  <a href="https://www.youtube.com/watch?v=QarizoUnRfk" target="_blank">
    <img src="https://img.youtube.com/vi/C7blZigaaaA/hqdefault.jpg" 
         alt="The Best way to Solder? Hot Plate to the rescue!"
         style="width:70%; border-radius:10px; border:1px solid #555;">
  </a>
  <br><br>
  <b style="font-size:20px;">Homemade Reflow Hot Plate for SMD Soldering</b>
  <br>
</div>

---




