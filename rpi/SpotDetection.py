import cv2
import time
import io
import picamera.array
import numpy as np
from picamera import PiCamera
from picamera.array import PiRGBArray
#from matplotlib import pyplot as plt

def previewCam(camera):
    for frame in camera.capture_continuous(rawCapture,format='bgr',use_video_port=True):
        img = frame.array

        for (lower, upper) in boundaries:
            lower = np.array(lower,dtype="uint8")
            upper = np.array(upper,dtype="uint8")
            mask = cv2.inRange(img,lower,upper)
            bw = cv2.bitwise_and(img,img,mask=mask)
            
        
        blur = cv2.GaussianBlur(bw,(5,5),0)
        gray = cv2.cvtColor(blur,cv2.COLOR_BGR2GRAY)
        edge = cv2.Canny(gray,40,80,L2gradient=True)
        #ret, thresh = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
        
        #kernel = np.ones((5,5))
        #opening = cv2.morphologyEx(edge,cv2.MORPH_OPEN, kernel)
        #closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, kernel)
        
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
            '''
            if area < 30 or area > 1500:
                continue
            if perimeter < 30 or perimeter > 1000:
                continue
            '''
            if area > max_area:
                max_area = area
                max_perimeter = perimeter
                curr_contour = cnt

            #ellipse = cv2.fitEllipse(cnt)
            #cv2.ellipse(output,ellipse,(0,255,0),2)
           
            cv2.drawContours(output,curr_contour,-1,(0,255,0),3)

        cv2.imshow("Frame",output)
        cv2.imshow("Image",img)
        cv2.waitKey(100) 
        rawCapture.truncate(0)

        
    #    if cv2.contourArea(prev_contour) <= cv2.contourArea(curr_contour):
    #       # cv2.drawContours(output,curr_contour,-1,(0,255,0),3)
    #        prev_contour = curr_contour
    #        return True
    #    else:
    #        return False
            
           # ellipse = cv2.fitEllipse(cnt)
           # cv2.ellipse(output,ellipse,(0,255,0),2)
           
            

camera = PiCamera()
camera.resolution = (640,480)
camera.framerate = 30
#camera.vflip = True
camera.hflip = True
img_size = (640,480)
rawCapture = PiRGBArray(camera,size=img_size)

boundaries = [
    ([200,200,200],[255,255,255])]

def runMain():
    time.sleep(1)
    val = 0
    for spot in range(10):
        if previewCam(camera) == True:
            val = val + 1
    if val >= 8:
          print('good')
    else:
        print('bad')

if __name__=="__main__":
    while True:
        #runMain()
        previewCam(camera)

    
