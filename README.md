# SCADA-PICK-AND-PLACE-XYZ

![Vista general](doc/assets/factory_io_scene.png)

Repositorio que documenta el desarrollo completo de un sistema **pick and place XYZ** simulado en **Factory IO**, programado en **Machine Expert Basic** y supervisado mediante **SCADA InduSoft Web Studio**. El proyecto incorpora un **Arduino** para lectura de un **joystick analógico**, permitiendo el control manual del manipulador en tiempo real.

---

## Índice

1. [Descripción general](#descripción-general)
2. [Arquitectura del sistema](#arquitectura-del-sistema)
3. [Requisitos](#requisitos)
4. [Estructura del repositorio](#estructura-del-repositorio)
5. [Puesta en marcha](#puesta-en-marcha)
6. [SCADA InduSoft](#scada-indusoft)
7. [Modos de operación](#modos-de-operación)
8. [Mapeo de variables](#mapeo-de-variables)
9. [Contribuciones](#contribuciones)
10. [Licencia](#licencia)

---

## Descripción general

Este proyecto demuestra el flujo de trabajo típico para integrar un entorno de simulación 3D, un PLC virtual, un SCADA industrial y hardware externo:

* **Factory IO** proporciona la escena 3D con transportador de estibas, carrusel de piezas y robot XYZ.
* **Machine Expert Basic** ejecuta la lógica PLC (secuenciación automática y control manual).
* **InduSoft Web Studio** presenta la interfaz HMI/SCADA para supervisión, registro de datos y control manual.
* **Arduino + Joystick** permite mover el robot en modo manual enviando variables analógicas al SCADA a través de TX/RX.

![Diagrama de arquitectura](doc/assets/architecture_diagram.png)

## Requisitos

| Software / Hardware  | 
| -------------------- |
| Factory IO           | 
| Machine Expert Basic | 
| InduSoft Web Studio  | 
| Arduino IDE          | 
| Arduino UNO / Nano   | 
| Joystick XY          | 

> **Nota:** se probó en Windows 10 x64. Ajuste rutas y puertos COM según su entorno.

## Estructura del repositorio

```
📁 factory_io/
   └─ PickAndPlaceXYZ.scene       # Escena 3D
📁 plc_project/
   └─ PickAndPlaceXYZ.stu         # Proyecto MEB
📁 scada/
   ├─ App/                        # Screens, tags, scripts
   └─ README_SCADA.md
📁 arduino/
   └─ joystick_control.ino        # Firmware Arduino
📁 doc/
   └─ assets/                     # Imágenes y diagramas
└─ README.md                      # (este archivo)
```

## Puesta en marcha

### 1. Clonar y abrir los proyectos

```bash
git clone https://github.com/usuario/PickAndPlaceXYZ.git
cd PickAndPlaceXYZ
```

1. En **Factory IO**: Abra `factory_io/PickAndPlaceXYZ.scene` y configure la comunicación OPC DA.
2. En **Machine Expert Basic**: Importe `plc_project/PickAndPlaceXYZ.stu`, compile y descargue al PLC virtual.
3. En **InduSoft**: Compile y ejecute la aplicación contenida en `scada/`.
4. En **Arduino IDE**: Cargue `arduino/joystick_control.ino` y seleccione el puerto adecuado.

### 2. Configurar comunicaciones

* **OPC Server**: Use el servidor OPC de Factory IO o el de MEB y registre los tags.
* **InduSoft**: Vincule los tags al driver OPC (DA/UA) y verifique calidad “Good”.
* **Arduino**: Envía variables a InduSoft vía Modbus-RTU o MQTT (ver firmware).

### 3. Ejecutar

1. Inicie la escena en Factory IO.
2. Ejecute el PLC desde Machine Expert Basic (Run).
3. Levante la aplicación SCADA (Viewer.exe).
4. Mueva el joystick: los valores analógicos cambiarán las variables `JOY_X` y `JOY_Y`, traducidas a velocidades del eje correspondiente.

## SCADA InduSoft

La interfaz incluye:

* **Pantalla de navegación** con modos `AUTO` y `MANUAL`.
* **Vista de la célula** con bandas, sensores fotoeléctricos y estado del robot.
* **Panel de joystick virtual** que replica las lecturas analógicas.
* **Historial de alarmas** y **tendencias** de producción.

Scripts clave:

```vbscript
' Cambio de color (ejemplo solicitado)
Sub ToggleColor()
    If COLOR_SCADA = 0 Then
        COLOR_SCADA = 1
    Else
        COLOR_SCADA = 0
    End If
End Sub
```

## Modos de operación

| Modo              | Descripción                                                 | Activación                               |
| ----------------- | ----------------------------------------------------------- | ---------------------------------------- |
| Automático        | PLC controla completamente la secuencia de estibas y robot. | `AUTO_MODE = TRUE`                       |
| Manual (Joystick) | Operador mueve ejes XYZ proporcionalmente al joystick.      | `AUTO_MODE = FALSE` & Joystick conectado |

## Mapeo de variables

| Tag SCADA    | PLC (%MW) | Arduino | Descripción        |
| ------------ | --------- | ------- | ------------------ |
| JOY\_X       | %MW0      | A0      | Eje X joystick     |
| JOY\_Y       | %MW1      | A1      | Eje Y joystick     |
| COLOR\_SCADA | %M100.0   | N/A     | Selección de color |
| CNT\_PIEZAS  | %MW10     | N/A     | Contador de piezas |

## Contribuciones

¡Las contribuciones son bienvenidas! Por favor realice un *fork* del repositorio y envíe un *pull request* siguiendo la guía de estilo incluida en `CONTRIBUTING.md`.

## Autor

Juan Carlos Aguirre 

