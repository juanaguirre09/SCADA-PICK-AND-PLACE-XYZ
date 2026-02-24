# SCADA-PICK-AND-PLACE-XYZ

<p align="left">
  <a href="https://youtu.be/0eFAJq77qtM" target="_blank">
    <img src="https://img.shields.io/badge/Watch%20Project%20Video-YouTube-red?style=for-the-badge&logo=youtube&logoColor=white" alt="Watch Project Video">
  </a>
</p>


Repository that documents the complete development of an **XYZ pick-and-place system** simulated in **Factory IO**, programmed in **Machine Expert Basic**, and supervised with **SCADA InduSoft Web Studio**. The project includes an **Arduino** to read an **analog joystick**, allowing real-time manual control of the manipulator.

---

## Overview

This project shows the typical workflow to integrate a 3D simulation environment, a virtual PLC, an industrial SCADA system, and external hardware:

* **Factory IO** provides the 3D scene with a pallet conveyor, parts carousel, and XYZ robot.
* **Machine Expert Basic** runs the PLC logic (automatic sequence and manual control).
* **InduSoft Web Studio** provides the HMI/SCADA interface for supervision, data logging, and manual control.
* **Arduino + Joystick** allows moving the robot in manual mode by sending analog variables to the SCADA through TX/RX.

## System Architecture

This project integrates the following components:

* **Factory IO** as the 3D simulation environment for the industrial cell.
* **Machine Expert Basic** as the PLC programming and execution platform.
* **InduSoft Web Studio** as the HMI/SCADA layer for monitoring and control.
* **Arduino + Joystick** as the manual input device for real-time manipulator movement.

The communication flow links the simulator, PLC, SCADA, and external joystick input into a single supervised control system.

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

Key scripts:

```vbscript
' Color change (requested example)
Sub ToggleColor()
    If COLOR_SCADA = 0 Then
        COLOR_SCADA = 1
    Else
        COLOR_SCADA = 0
    End If
End Sub

