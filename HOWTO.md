# How To

## Notes

This projects use stepper motors because I had a bunch of them lying around.
However, DC motors with H-bridge for drivers would be more appropriate.

## BOM

* Raspberry Pi Model 3
* 4x NEMA 14 stepper motors
* 4x A4988 Stepper Motor Driver Carrier by Pololu
* DC-DC buck converter (TSR 1-2450 by Traco Electronic AG)
* Capacitor: 330 uF, 35V, electrolytic, radial
* on/off switch (any kind > 2A will do)
* screw terminal
* micro USB cable
* a bunch of (fe)male headers, wires, screws, ...
* board (to hold things together, any kind of scrap wood will do)

## Prerequisites

### Tools

* 3D printer
* CNC mill with 0.8, 1, and 3mm bits
* soldering iron
* screwdrivers
* drill
* hot glue gun
* precision knife
* tweezers
* ...

### Software

* [KiCad](http://kicad-pcb.org/)
* [OpenSCAD](http://www.openscad.org/)
* nmap, ssh cilent (to find and connect to the Raspberry Pi)
* Slicer for your 3D printer, e.g., [Slic3r](http://slic3r.org/)
* [FlatCAM](http://flatcam.org/)

## Raspberry Pi setup

* Headless setup for the Raspberry Pi 3:
  - http://blog.self.li/post/63281257339/raspberry-pi-part-1-basic-setup-without-cables for the basic setup, finding the rpi over the network, and sshing into it.
  - On recent images, you need to enable SSH: https://caffinc.github.io/2016/12/raspberry-pi-3-headless/
* To find your rpi I recommend using `sudo nmap -sP -n XXX.YYY.ZZZ.0/24` where XXX, YYY, ZZZ is the ip of subnetwork. This should also show the MAC address (useful if there are multiple rpi on your network).
* Install [Wiring Pi](http://wiringpi.com/download-and-install/)

## Building the robot

ToDo ...
