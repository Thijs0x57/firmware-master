Repository for the master firmware.
The firmware runs on a modified raspbian image. In this repository are all the files needed to setup a working environment.
use as follows:

```
Enable SSH and I2C using sudo raspi-config
Add the 30-blocker.conf to /etc/rsyslog.d and enable it in rsyslog.conf
compile all files using g++ (lockercall need lwiringPi.)
add the SSH key from the server
```
