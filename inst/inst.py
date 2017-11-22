#!/usr/bin/python

# Note -
#  Install pip by:
#    wget https://bootstrap.pypa.io/get-pip.py
#    chmod a+x get-pip.py
#    sudo ./get-pip.py
#  Install Python-VISA stuff:  
#    pip install -U pyvisa
#    pip install pyvisa-py
#    pip install pyusb
#  Check install:
#    python -m visa info
#  Update privs
#    sudo emacs /etc/udev/rules.d/99-openocd.rules
#      SUBSYSTEM=="usb", ATTR{idVendor}=="05e6",
#      ATTR{idProduct}=="2230", MODE="664", GROUP="plugdev"
#      SUBSYSTEM=="usbtmc", ATTR{idVendor}=="05e6",
#      ATTR{idProduct}=="2230", MODE="664", GROUP="plugdev"

#
# NOTE - had to pull pyvisa-py/usb.py directly from github to get it
#  to work right for reads.

import visa
import pyvisa
import time
import os

rm = visa.ResourceManager('@py')
for myinst in rm.list_resources():
  inst = rm.open_resource(myinst)
  print (myinst)

  hifive = os.open("/dev/ttyUSB1",os.O_RDWR)
  if ( not hifive ):
    print ("Problem opening hifive1")

# flush buffer if needed.
  os.write(hifive, "F")
  os.read(hifive,999)

  inst.read_termination="\n"
  inst.write_termination="\n"
  inst.send_end=True
#  inst.query_delay=1

  # Code to get this Keithley 2230 to work at all with this setup
  inst.timeout = 3000
  inst.write('SYST:REM')
  inst.write('*CLS')
  inst.write('*ESE 0')
  
    
  print inst.query('*IDN?')
  inst.write("APPLY CH1,1.62V,400mA ")
  inst.write("APPLY CH2,2.98V,400mA ")
  inst.write("APPLY CH3,1.62V,400mA ")

  inst.write("OUTPUT ON ")

  for pfreq in range(25,325,25):
      for psup in range(-10,11):
        os.write(hifive, "0")
        time.sleep(0.2)
        os.write(hifive, str(pfreq)+"000000\n")
        time.sleep(0.2)        
        os.read(hifive,999)
        time.sleep(0.2)        
        os.write(hifive, "F")
        rfreq=os.read(hifive,999).strip()
        vsup=1.8*(1.0+(psup/100.0))
        inst.write("APPLY CH1,"+str(vsup)+"V,400mA ")
        inst.write("APPLY CH2,"+str(vsup*3.3/1.8)+"V,400mA ")
        inst.write("APPLY CH3,"+str(vsup)+"V,400mA ")
        print(str(rfreq)+inst.query('MEAS:VOLT? ALL')+", "+inst.query('MEAS:CURR? ALL'))
  
  
#  inst.write("OUTPUT OFF ")
