
# AUTHOR: ADNAN BEGOVIC.

##########################################################
#     Import necessary packages:
##########################################################

import RPi.GPIO as GPIO
from RPLCD import CharLCD
import cv2
import numpy as np
import time
from picamera.array import PiRGBArray
from picamera import PiCamera

##########################################################
#     Define GPIO-pins on Raspberry Pi:3:
##########################################################

# CommunicationPins:      
right_out = 29
target_out = 31
left_out = 33
nodetection_out = 35
raspberry_in = 37

##########################################################
#       Setup GPIO-Pins on Raspberry Pi:3:
##########################################################

GPIO.setwarnings(False)     #Eliminate warnings for GPIO-pins.
GPIO.setmode(GPIO.BOARD)    #Initialize physical pinboard.

# Output-Pins:
GPIO.setup(right_out,GPIO.OUT)
GPIO.setup(target_out,GPIO.OUT)
GPIO.setup(left_out,GPIO.OUT)
GPIO.setup(nodetection_out,GPIO.OUT)

# Output -Pins for LCD:
lcd = CharLCD(cols=16, rows=2, pin_rs=5, pin_e=3, pins_data=[15, 13, 11, 7])

# Input-Pins:
GPIO.setup(raspberry_in, GPIO.IN)

############################################################
#       Setup Pi-camera V2:
############################################################

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 30
camera.hflip = True
rawCapture = PiRGBArray(camera, size=(640, 480)) #Reference to the raw camera capture.
time.sleep(0.1)                                  #Allow the camera to warmup.  


############################################################
#   Start digitalpin-communication, Raspberry <--> DUE:
############################################################

arduinoSignal = GPIO.input(raspberry_in) #Read input-pin.
while True: 
    if (arduinoSignal == True):
            print ("Start color detection")
            lcd.clear()
            lcd.write_string("Connected")
            break
    lcd.clear()
    lcd.write_string("Not Connected")
     
    # Start digitalpin- communication manually:
    try:
        HIGH = int(input("Enter 1 on the keyboard: "))
        arduinoSignal = HIGH
        
    except ValueError:
        print ("Wrong number! Please try again!")
        
############################################################
#       Capture frames from the Pi-camera:
############################################################
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    image = frame.array

    ##########################################
    #  Prepare image for colorfiltering:
    ##########################################
    
    # Blur the BGR-image:
    blur = cv2.blur(image, (3,3))

    # Convert the Blured-BGR-image to HSV-image:
    hsv = cv2.cvtColor(blur,cv2.COLOR_BGR2HSV)
    
    # NEON-GREEN color in HSV:
    lower = np.array([29,86,6],dtype="uint8") 
    upper = np.array([64,255,255], dtype="uint8")
   
    ###########################################
    #     Define colorfilters:
    ###########################################

    #Trenshold the HSV-image to black and white-pixels:
    mask = cv2.inRange(hsv, lower, upper)
    
    #Trenshold the HSV-image to blured and colored-pixels:
    mask2 = cv2.bitwise_and(blur, blur, mask=mask) 

    ###########################################
    # Find contours in the defined colorfilter:
    ###########################################

    image, contours,hierarchy = cv2.findContours(mask,cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE)

    # Find contour with the biggest pixel- area and store in best_contour:
    biggest_area = 0
    best_contour = 1
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > biggest_area:
            biggest_area = area
            best_contour = cnt

    # Find centroids of best_contour 
    M = cv2.moments(best_contour)
    cx,cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
    # Draw an green circle in the best_contour
    cv2.circle(blur,(cx,cy),6,(0,255,0),-1)

    ############################################
    #   The frame-zones are defined:              
    ############################################

    RIGHT_ZONE = 370 < cx <= 615
    TARGET_ZONE = 270 < cx <= 370
    LEFT_ZONE = 25 < cx <= 295

    #Font and color: 
    font = cv2.FONT_HERSHEY_SIMPLEX
    green = (0,255,0)
    yellow = (63,250,255)
    red = (0,0,255)

    ############################################
    #   The frame-zones in action:              
    ############################################
    
    if TARGET_ZONE:
        
        #The specified communicationpin for this frame-zone is set to high:
        GPIO.output(target_out,1)
        #Set other communicationpins to low, just to make sure:
        GPIO.output(right_out,0)  
        GPIO.output(left_out,0)
        GPIO.output(nodetection_out,0)
        
        #The state of robot will be displayed on an external LCD for error-handling:
        lcd.clear()
        lcd.write_string("TARGET")
        
        #Draws an rectangle and displays the text of the specified frame-zone:
        cv2.rectangle(blur,(270,0),(370, 480), green ,2)
        cv2.putText(blur,"Target",(280,240), font, 0.8, green ,2, cv2.LINE_AA)
        
    elif RIGHT_ZONE:
        
        #The specified communicationpin of the frame-zone is set to high:
        GPIO.output(right_out,1)
        #Set other communicationpins to low, just to make sure:
        GPIO.output(target_out,0)
        GPIO.output(left_out,0)
        GPIO.output(nodetection_out,0)
        
        #The state of robot will be displayed on an external LCD for error-handling:
        lcd.clear()
        lcd.write_string("ROTATE LEFT")
        
        #Draws an rectangle and displays the text of the specified frame-zone:
        cv2.rectangle(blur,(370,0),(615,480), yellow ,2)
        cv2.putText(blur,"In Rightzone",(410,240), font, 0.8, yellow ,2, cv2.LINE_AA)
        
    elif LEFT_ZONE:
        
        #The specified communicationpin of the frame-zone is set to high:
        GPIO.output(left_out,1)
        #Set other communicationpins to low, just to make sure:
        GPIO.output(target_out,0)
        GPIO.output(right_out,0)
        GPIO.output(nodetection_out,0)
        
        #The state of robot will be displayed on an external LCD for error-handling:
        lcd.clear()
        lcd.write_string("ROTATE RIGHT")
        
        #Draws an rectangle and displays the text of the specified frame-zone:
        cv2.rectangle(blur,(25,0),(270,480), yellow,2)
        cv2.putText(blur,"In Leftzone",(80,240), font, 0.8, yellow ,2, cv2.LINE_AA)
        
        
    else: #NODETECTION_ZONE:

        #The specified communicationpin of the frame-zone is set to high:
        GPIO.output(nodetection_out,1)
        #Set other communicationpins to low, just to make sure:
        GPIO.output(target_out,0)
        GPIO.output(right_out,0)
        GPIO.output(left_out,0)
        
        #The state of robot will be displayed on an external LCD for error-handling:
        lcd.clear()
        lcd.write_string("SCAN AREA")
        
        #Draws rectangles and displays the text of the specified frame-zone:
        cv2.rectangle(blur,(0,0),(25,480), red ,2)
        cv2.rectangle(blur,(615,0),(640,480), red ,2)
        cv2.putText(blur,"No objects detected",(220,240), font, 0.8, red ,2, cv2.LINE_AA)
        
    ###############################
    #   Show frames:             
    ###############################
    cv2.imshow("Frame", blur)
    cv2.imshow("Trensh", mask)
    cv2.imshow("Thrensh2", mask2)

    # Clear the videostream in preparation for the next frame
    rawCapture.truncate(0)

    ################################
    #   Exit colordetection program:             
    ################################

    if cv2.waitKey(1) == ord('e'): #press e-key to exit
        lcd.clear()
        lcd.write_string("Disconnected")
        break
GPIO.cleanup()  



##########################################################
#    Other HSV-colors that can be selected manually      #
#####                                              #######

    # VIOLET color in HSV:
    #lower = np.array([141,39,64],dtype="uint8")
    #upper = np.array([160,255,255], dtype="uint8")
    
    # BLUE color in HSV:
    #lower = np.array([29,86,6],dtype="uint8")
    #upper = np.array([64,255,255], dtype="uint8")
    
    # RED color in HSV:
    #lower = np.array([17,15,100],dtype="uint8")
    #upper = np.array([50,56,200], dtype="uint8")

    # NEON-GREEN color in HSV:
    #lower = np.array([29,86,6],dtype="uint8")
    #upper = np.array([64,255,255], dtype="uint8")

###########################################################
