#!/usr/bin/env python3

USB_PORT = "/dev/ttyACM0"

import serial
import time

class vRobo:

    initsuccess = False
    usb =  None

    def robo_init(self):
        try:
            self.usb = serial.Serial(USB_PORT, 9600, timeout=2)
            print ( self.usb.readline())
            initsuccess = True
        except:
            print ("error - could not open port..exiting")

#robo commands
    def robo_speed(self):
        self.usb.write(b's050')

    def robo_vspeed(self,s):
        self.usb.write(s)

    def robo_start(self):
        self.usb.write(b'r000')

    def robo_stop(self):
        self.usb.write(b'h000')

    def robo_movef(self):
        self.usb.write(b'vf00')
        self.robo_start()

    def robo_moveb(self):
        self.usb.write(b'vb00')
        self.robo_start()

    def robo_mover(self):
        self.usb.write(b'vr00')
        self.robo_start()

    def robo_movel(self):
        self.usb.write(b'vl00')
        self.robo_start()

    def robo_vstop(self):
        self.usb.write(b'vh00')

    def robo_movefdl(self):
        self.usb.write(b'vfdl')
        self.robo_start()

    def robo_movefdr(self):
        self.usb.write(b'vfdr')
        self.robo_start()

    def robo_movebdl(self):
        self.usb.write(b'vbdl')
        self.robo_start()

    def robo_movebdr(self):
        self.usb.write(b'vbdr')
        self.robo_start()

    def robo_moverrl(self):
        self.usb.write(b'vrrl')
        self.robo_start()

    def robo_moverrr(self):
        self.usb.write(b'vrrr')
        self.robo_start()

    def robo_movercl(self):
        self.usb.write(b'vrcl')
        self.robo_start()

    def robo_movercr(self):
        self.usb.write(b'vrcr')
        self.robo_start()


#brush command

    def robo_cspeed(self):
        self.usb.write(b'cs00')

    def robo_cstart(self):
        self.usb.write(b'cr00')

    def robo_cstop(self):
        self.usb.write(b'ch00')

#extender commands

    def robo_espeed(self):
        self.usb.write(b'es00')

    def robo_emovef(self):
        self.usb.write(b'ef00')

    def robo_emoveb(self):
        self.usb.write(b'eb00')

    def robo_estop(self):
        self.usb.write(b'eh00')

#initialization

    def __init__(self):
        print ("calling init function of vRobo" )

    def robo_test(self):

        print ("setting robo speed")
        self.robo_speed()

        print ("moving forward.... ")
        self.robo_movef()
        time.sleep(5)
        self.robo_stop()

        print ("moving back.... ")
        self.robo_moveb()
        time.sleep(5)
        self.robo_stop()

        print ("moving right.... ")
        self.robo_mover()
        time.sleep(5)
        self.robo_stop()

        print ("moving left.... ")
        self.robo_movel()
        time.sleep(5)
        self.robo_stop()

        print ( "testing speed...." )
        self.robo_movef()
        self.robo_vspeed(b's120')
        time.sleep(5)
        self.robo_speed()
        time.sleep(5)
        self.robo_vspeed(b's020')
        time.sleep(5)
        self.robo_stop()


#vr = vRobo()
#vr.robo_init()
#vr.robo_test()


