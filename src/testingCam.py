from tensorflow.keras.models import load_model
import imutils
import numpy as np
import cv2
import os

from DataCollection import WebcamModule as WM

print("[INFO] loading network toy")
modelToy = load_model("ToyNoToy.model")
print("[INFO] loading network box")
modelBox = load_model("ToyBoxNoToyBox.model")

while True:
    img, orig = WM.getImg()
    img = img.astype("float") / 255.0
    img = np.expand_dims(img, axis=0)
    (NoToy, Toy) = modelToy.predict(img)[0]
    (NoBox, Box) = modelBox.predict(img)[0]
    label = ""
    
    if Toy > Box:
        label = "Toy" if Toy > NoToy else "No Toy"
        probability = max(Toy, NoToy)
        label = "{}: {:.2f}%".format(label, probability * 100)
    else:
        label = "Box" if Box > NoBox else "No Box"
        probability = max(Box, NoBox)
        label = "{}: {:.2f}%".format(label, probability * 100)
    
    orig = imutils.resize(orig, width = 400)
    cv2.putText(orig, label, (200,25), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (200, 2255, 40), 2)
    cv2.imshow('Image', orig)
    
    key = cv2.waitKey(1)
    if key==27:
        break

cv2.destroyAllWindows()
    