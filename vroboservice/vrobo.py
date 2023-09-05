#!/usr/bin/python
from flask import Flask
import subprocess
import usbcmd

vr = usbcmd.vRobo()
vr.robo_init()

app = Flask(__name__)

# general commands
@app.route("/ping")
def ping():
    print ("connection check")
    return "success:online\n"

# controller boad commands

@app.route("/shutdown")
def shutdown():
	subprocess.run("sudo shutdown -h now".split())
	return "Shutdown"

@app.route("/reboot")
def reboot():
	subprocess.run("sudo shutdown -r now".split())
	return "reboot"


# VRobot movement command

@app.route("/robo/movef")
def robo_moveforward():
    #vr.robo_speed()
    vr.robo_movef()
    return "move forward\n"

@app.route("/robo/moveb")
def robo_moveback():
    #vr.robo_speed()
    vr.robo_moveb()
    return "move back\n"

@app.route("/robo/movel")
def robo_moveleft():
    #vr.robo_speed()
    vr.robo_movel()
    return "move left\n"

@app.route("/robo/mover")
def robo_moveright():
    #vr.robo_speed()
    vr.robo_mover()
    return "move right\n"

@app.route("/robo/movefdl")
def robo_movefdl():
    vr.robo_movefdl()
    return "move fdl\n"

@app.route("/robo/movefdr")
def robo_movefdr():
    vr.robo_movefdr()
    return "move fdr\n"

@app.route("/robo/movebdl")
def robo_movebdl():
    vr.robo_movebdl()
    return "move bdl\n"

@app.route("/robo/movebdr")
def robo_movebdr():
    vr.robo_movebdr()
    return "move bdr\n"

@app.route("/robo/moverrl")
def robo_moverrl():
    vr.robo_moverrl()
    return "move rrl\n"

@app.route("/robo/moverrr")
def robo_moverrr():
    vr.robo_moverrr()
    return "move rrr\n"

@app.route("/robo/movercl")
def robo_movercl():
    vr.robo_movercl()
    return "move rcl\n"

@app.route("/robo/movercr")
def robo_movercr():
    vr.robo_movercr()
    return "move rcr\n"

#vRobot move command end

@app.route("/robo/start")
def robo_start():
    vr.robo_start()
    return "start\n"

@app.route("/robo/stop")
def robo_stop():
    vr.robo_stop()
    return "stop\n"

@app.route("/robo/vstop")
def robo_vstop():
    vr.robo_vstop()
    return "vstop\n"

@app.route("/robo/lowspeed")
def robo_lowspeed():
    vr.robo_vspeed(b's050')
    return "low-50\n"

@app.route("/robo/medspeed")
def robo_medspeed():
    vr.robo_vspeed(b's125')
    return "med-125\n"

@app.route("/robo/highspeed")
def robo_highspeed():
    vr.robo_vspeed(b's175')
    return "high-175\n"

@app.route("/robo/maxspeed")
def robo_maxspeed():
    vr.robo_vspeed(b's250')
    return "max-250\n"

#brush command
#
@app.route("/robo/cspeed")
def robo_cspeed():
    vr.robo_cspeed()
    return "cspeed\n"

@app.route("/robo/cstart")
def robo_cstart():
    vr.robo_cspeed()
    vr.robo_cstart()
    return "cstart\n"

@app.route("/robo/cstop")
def robo_cstop():
    vr.robo_cstop()
    return "cstop\n"

#extender command
#
@app.route("/robo/espeed")
def robo_espeed():
    vr.robo_espeed()
    return "espeed\n"

@app.route("/robo/estop")
def robo_estop():
    vr.robo_estop()
    return "estop\n"

@app.route("/robo/emovef")
def robo_emovef():
    vr.robo_espeed()
    vr.robo_emovef()
    return "emovef\n"

@app.route("/robo/emoveb")
def robo_emoveb():
    vr.robo_cspeed()
    vr.robo_emoveb()
    return "emoveb\n"

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=5000)

