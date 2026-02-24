# SCADA-PICK-AND-PLACE-XYZ

<p align="left">
  <a href="YOUR_YOUTUBE_VIDEO_LINK_HERE" target="_blank">
    <button>Watch Project Video</button>
  </a>
</p>

![Overview](doc/assets/factory_io_scene.png)

Repository that documents the complete development of an **XYZ pick-and-place system** simulated in **Factory IO**, programmed in **Machine Expert Basic**, and supervised with **SCADA InduSoft Web Studio**. The project includes an **Arduino** to read an **analog joystick**, allowing real-time manual control of the manipulator.

---

## Table of Contents

1. [Overview](#overview)
2. [System Architecture](#system-architecture)
3. [Requirements](#requirements)
4. [Repository Structure](#repository-structure)
5. [Startup](#startup)
6. [SCADA InduSoft](#scada-indusoft)
7. [Operating Modes](#operating-modes)
8. [Variable Mapping](#variable-mapping)
9. [Contributions](#contributions)
10. [License](#license)

---

## Overview

This project shows the typical workflow to integrate a 3D simulation environment, a virtual PLC, an industrial SCADA system, and external hardware:

* **Factory IO** provides the 3D scene with a pallet conveyor, parts carousel, and XYZ robot.
* **Machine Expert Basic** runs the PLC logic (automatic sequence and manual control).
* **InduSoft Web Studio** provides the HMI/SCADA interface for supervision, data logging, and manual control.
* **Arduino + Joystick** allows moving the robot in manual mode by sending analog variables to the SCADA through TX/RX.

![Architecture Diagram](doc/assets/architecture_diagram.png)

## Requirements

| Software / Hardware  |
| -------------------- |
| Factory IO           |
| Machine Expert Basic |
| InduSoft Web Studio  |
| Arduino IDE          |
| Arduino UNO / Nano   |
| XY Joystick          |

> **Note:** Tested on Windows 10 x64. Adjust paths and COM ports according to your environment.

## Repository Structure

```text
factory_io/
   └─ PickAndPlaceXYZ.scene       # 3D scene
plc_project/
   └─ PickAndPlaceXYZ.stu         # MEB project
scada/
   ├─ App/                        # Screens, tags, scripts
   └─ README_SCADA.md
arduino/
   └─ joystick_control.ino        # Arduino firmware
doc/
   └─ assets/                     # Images and diagrams
README.md                         # (this file)

## Startup

1. In **Factory IO**: Open `factory_io/PickAndPlaceXYZ.scene` and configure OPC DA communication.
2. In **Machine Expert Basic**: Import `plc_project/PickAndPlaceXYZ.stu`, compile it, and download it to the virtual PLC.
3. In **InduSoft**: Compile and run the application in `scada/`.
4. In **Arduino IDE**: Upload `arduino/joystick_control.ino` and select the correct port.

### 1. Configure communications

* **OPC Server**: Use the Factory IO OPC server or the MEB OPC server and register the tags.
* **InduSoft**: Link the tags to the OPC driver (DA/UA) and verify `Good` quality.
* **Arduino**: Sends variables to InduSoft through Modbus-RTU or MQTT (see firmware).

### 2. Run

1. Start the scene in Factory IO.
2. Run the PLC from Machine Expert Basic (Run).
3. Start the SCADA application (`Viewer.exe`).
4. Move the joystick: the analog values will change the `JOY_X` and `JOY_Y` variables, converted into speed values for the corresponding axis.

## SCADA InduSoft

The interface includes:

* **Navigation screen** with `AUTO` and `MANUAL` modes.
* **Cell view** with conveyors, photoelectric sensors, and robot status.
* **Virtual joystick panel** that mirrors the analog readings.
* **Alarm history** and **production trends**.

## Operating Modes

| Mode              | Description                                               | Activation                               |
| ----------------- | --------------------------------------------------------- | ---------------------------------------- |
| Automatic         | PLC fully controls the pallet and robot sequence.         | `AUTO_MODE = TRUE`                       |
| Manual (Joystick) | Operator moves XYZ axes proportionally with the joystick. | `AUTO_MODE = FALSE` & Joystick connected |

## Variable Mapping

| SCADA Tag     | PLC (%MW) | Arduino | Description       |
| ------------- | --------- | ------- | ----------------- |
| `JOY_X`       | `%MW0`    | `A0`    | Joystick X axis   |
| `JOY_Y`       | `%MW1`    | `A1`    | Joystick Y axis   |
| `COLOR_SCADA` | `%M100.0` | `N/A`   | Color selection   |
| `CNT_PIEZAS`  | `%MW10`   | `N/A`   | Parts counter     |

## Contributions

Add your contribution guidelines here.

## License

Add your license information here.

## Author

Juan Carlos Aguirre

