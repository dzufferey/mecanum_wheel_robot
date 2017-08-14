# Mecanum wheels robot

A small omnidirectional wheeled robot.

The robot is designed as part of a series of tutorials covering: CAD, prototyping, and programming.

The project is split among the following directories:
- `body`
- `code`
- `pcb`

Not everything is in this repository.
You will also need:
- a model for the [mecanum wheels](https://github.com/dzufferey/scadla/blob/master/src/main/scala/scadla/examples/MecanumWheel.scala)
- a case for Raspberry Pi (look on [Tingiverse](http://www.thingiverse.com/))
- motor bracket for NEMA 14 stepper motors (look on [Tingiverse](http://www.thingiverse.com/))

The [HOWTO.md](HOWTO.md) file describe how to put things together.

## Attributions

- [Bosch Blue 10.8 volt battery container](https://www.thingiverse.com/thing:1246842) by topias5 is licensed under the CC-BY-NC license.
- references and model for [A4988 Stepper Motor Driver Carrier, Black Edition](https://www.pololu.com/product/2128), license unclear ...
- [KiCAD module for the stepper dirvers](https://github.com/jharvey/Cinch_enclosure_template/tree/master/KICAD_Project/PCB-modules/pololu) by Jared Harvey, license unclear ...

## License

The content of this project itself is licensed under the [Creative Commons Attribution 3.0 license](http://creativecommons.org/licenses/by/3.0/us/deed.en_US), and the source code in the `code` folder is licensed under the [MIT license](http://opensource.org/licenses/mit-license.php).
