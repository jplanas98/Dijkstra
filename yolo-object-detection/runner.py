
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)

print "Make sure you have a button connected so that when pressed"
print "it will connect GPIO port 23 (pin 16) to GND (pin 6)\n"
raw_input("Press Enter when ready\n>")

print "Waiting for falling edge on port 23"
# now the program will do nothing until the signal on port 23
# starts to fall towards zero. This is why we used the pullup
# to keep the signal high and prevent a false interrupt
while true:
    GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    print "During this waiting time, your computer is not"
    print "wasting resources by polling for a button press.\n"
    print "Press your button when ready to initiate a falling edge interrupt."
    try:
        GPIO.wait_for_edge(23, GPIO.FALLING)
        print "\nFalling edge detected. Now your program can continue with"
        print "whatever was waiting for a button press."
        # subprocess.call("python yolo.py --image images/pic.jpg --yolo yolo-coco")
    except KeyboardInterrupt:
        GPIO.cleanup()       # clean up GPIO on CTRL+C exit
    GPIO.cleanup()