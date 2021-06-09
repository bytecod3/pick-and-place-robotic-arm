from scipy.spatial.distance import euclidean
from imutils import perspective
from imutils import perspective
import numpy as np
import cv2

def display_image_array(images_array):
    '''  Function to show array of images '''
    for i, img in enumerate(images_array):
        cv2.imshow("image_" + str(i), img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

image_path = "statics/img.png"

image = cv2.imread(image_path) # read image and process
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBLur(gray, (9, 9), 0)

edged = cv2.Canny(blur, 50, 100)
edged = cv2.dilate(edged, None, iterations=1)
edged = cv2.erode(edged, None, iterations=1)

# find contours
cnts = cv2.findCountours(edged.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)

# sort contours from left to right. left most contour in reference 
# object
(cnts, _) = contours.sort_contours(cnts)

# remove contours which are not large enough
cnts = [x for x in cnts if cv2.contourArea(x) > 100]

# for debug 
print(len(cnts))

# reference object dimensions
# I have used 2cm by 2cm square here
ref_object = cnts[0]
box = cv2.minAreaRect(ref_object)
box = cv2.boxPoints(box)
box = np.array(box, dtype="int")
box = perspective.order_points(box)
(tl, tr, br, bl) = box
dist_in_pixel = euclidean(tl, tr)
dist_in_cm = 2
pixel_per_cm = dist_in_pixel/dist_in_cm


# draw remaining contours
for cnt in cnts:
    box = cv2.minAreaRect(cnt)
    box = cv2.boxPoints(box)
    box = np.array(box, dtype="int")
    box = perspective.order_points(box)
    (tl, tr, br, bl) = box
    cv2.
