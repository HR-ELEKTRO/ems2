import time
from collections import defaultdict

import matplotlib.pyplot as plt
import serial

# Het poortnummer van micropython
PORT = "COM19"            
BAUDRATE = 115_200

def receive_curves(ser, aantal=1):
    curves = defaultdict(lambda: {"voltage": [], "current": [], "temperature": 0})
    active_control_voltage = None
    temperature = None

    while True:
        raw_line = ser.readline()

        if not raw_line:
            continue

        try:
            line = raw_line.decode("ascii").strip()
        except UnicodeDecodeError:
            continue

        print("RX:", line)

        if line.startswith("BEGIN,"):
            try:
                active_control_voltage = int(line.split(",", 2)[1])
                temperature = float(line.split(",", 2)[2])
            except ValueError:
                active_control_voltage = None

        elif line == "END":
            active_control_voltage = None

            # pas dit aan naar het aantal curves wat je wilt hebben
            if len(curves) >= aantal:
                return curves

        elif active_control_voltage is not None:
            try:
                voltage_text, current_text = line.split(",")
                voltage = float(voltage_text)
                current = float(current_text)
            except ValueError:
                continue

            curve = curves[active_control_voltage]
            curve["voltage"].append(voltage)
            curve["current"].append(current)
            curve["temperature"]=temperature


def plot_curves(curves):
    for control_voltage in sorted(curves):
        curve = curves[control_voltage]
        temp = curve["temperature"]
        plt.plot(
            curve["voltage"],
            curve["current"],
            marker=".",
            label=f"V_DD = {control_voltage} mV, {temp:.1f} C",
        )

    #plt.xlabel("Drain-source voltage VDS [mV]")
    plt.xlabel("Gate-source spanning VGS [mV]")
    plt.ylabel("Drain stroom ID [mA]")
    plt.title(f"MOSFET curves")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()


def main():
    with serial.Serial(
        port=PORT,
        baudrate=BAUDRATE,
        timeout=1,
    ) as ser:
        curves = receive_curves(ser, 1) #aantal curves om te ontvangen

    plot_curves(curves)


if __name__ == "__main__":
    main()
