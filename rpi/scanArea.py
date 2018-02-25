import cv2
import time
import io
import picamera.array
import numpy as np
from picamera import PiCamera
from picamera.array import PiRGBArray
import RPi.GPIO as GPIO

sigPin = 11
ctrlPin = 13

camera = PiCamera()
camera.resolution = (640,480)
camera.framerate = 30
camera.hflip = True
img_size = (640,480)
rawCapture = PiRGBArray(camera,size=img_size)
boundaries = [
    ([200,200,200],[255,255,255])]

spotsMax = 0

def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(sigPin, GPIO.OUT)
    GPIO.setup(ctrlPin, GPIO.IN)
    GPIO.output(sigPin, GPIO.LOW)
     
def previewCam(camera):
    global spotsMax
    for frame in camera.capture_continuous(rawCapture,format='bgr',use_video_port=True):
        img = frame.array
        img = img[:, 240:400]
        for (lower, upper) in boundaries:
            lower = np.array(lower,dtype="uint8")
            upper = np.array(upper,dtype="uint8") 
            mask = cv2.inRange(img,lower,upper)
            bw = cv2.bitwise_and(img,img,mask=mask)
            
        blur = cv2.GaussianBlur(bw,(5,5),0)
        gray = cv2.cvtColor(blur,cv2.COLOR_BGR2GRAY)
        edge = cv2.Canny(gray,40,80,L2gradient=True)
        
        output = bw.copy()
        _, contours, hierachy = cv2.findContours(edge,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
        max_area = 0
        max_perimeter = 0
        curr_contour = []
        #prev_contour = contours(1)
        for cnt in contours:
            area = cv2.contourArea(cnt)
            epsilon = 0.1*cv2.arcLength(cnt,True)
            approx = cv2.approxPolyDP(cnt,epsilon,True)
            perimeter = cv2.arcLength(cnt,True)
    
            if area < 500 or area > 8000:
                continue
            '''
            if perimeter < 30 or perimeter > 1000:
                continue
            '''
            if area > max_area:
                max_area = area
                max_perimeter = perimeter
                curr_contour = cnt
                if spotsMax < max_area:  # found a new max spots
                    GPIO.output(sigPin, GPIO.HIGH)
                    time.sleep(1)
                    GPIO.output(sigPin, GPIO.LOW)
                    spotsMax = max_area
                    print("Signal sent! Freshing spotsMax to : ", spotsMax)
           
            cv2.drawContours(output,curr_contour,-1,(0,255,0),3)

        cv2.imshow("Frame",output)
        cv2.imshow("Image",img)
        cv2.waitKey(100) 
        rawCapture.truncate(0)

def destroy():
    GPIO.output(sigPin, GPIO.LOW)
    GPIO.cleanup()
    spotsMax = 0

if __name__ == '__main__':
    setup()
    while True:
        # previewCam(camera)
        if GPIO.input(ctrlPin) == 0:
            print("Control signal from teensy received, opening camera...")
            previewCam(camera)
        # else:
        #     time.sleep(100)
