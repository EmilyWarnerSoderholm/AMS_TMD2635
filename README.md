# Arduino Library for the ams TMD2635 proximity sensor

### Summary

-----

### Operation

-----

### Library Functions and Class Methods

#### bool begin(uint8_t tmd26721Address = 0x39)

Before using the IRSense object, begin() must be called once. 

-----

#### int readProximity()

The core function of the sensor.  This will read the proximity registers and return as an integer if a valid conversion is available.  If not, it waits up to 15ms for PVALID in the status register to be set.  If the sensor has had an error or isn't initialized, it will try to reinitialize the sensor.  

__Return values:__
* -1 = Sensor communications error
* 0-1023 = Value in the proximity register

-----

#### bool proximityReady()

Polls the status register (0x13) and gets the value of PVALID, indicating that a valid proximity reading.

__Return values:__
* true - reading is valid and available
* false - reading is not valid, or communications failed

-----

### Hardware

Used with the ESP6288 breakou tboard

### License

