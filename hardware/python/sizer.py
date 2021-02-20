from scipy.spatial import distance as dist
from imutils import perspective
from imutils import contours
import numpy as np
import argparse
import imutils
import cv2

# construct the argument and parse command line input
aparse = argparse.ArgumentParser()
aparse.add_argument("--image", required=True, help="image path")
aparse.add_argument("--width", type=float, required=True, help="width of far left object (cm)")
args = vars(aparse.parse_args())

# load the image, convert it to grayscale and blur it a bit
image = cv2.imread(args["image"])
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
gray = cv2.GaussianBlur(gray, (7,7), 0)

# perform edge detection + dilation + erosion to close gaps bt edges
edge_detect = cv2.Canny(gray, 15, 100)

# play with min and max values to fine tune the edges
edge_detect  = cv2.dilate(edge_detect, None, iterations=1)
edge_detect = cv2.erode(edge_detect, None, iterations=1)

cntours = cv2.findContours(edge_detect.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cntours =imutils.grab_contours(cntours)

# sort contours left-to-right
(cntours, _) = contours.sort_contours(cntours)
pixel_to_size = None


# function for finding the midpoint
def midpoint(A, B):
    return ((A[0] + B[0]) * 0.5, (A[1] + B[1]) * 0.5)


# loop over the contours individually
for c in cntours:
    if cv2.contourArea(c) < 100:
        # ignore contours that are not big enough
        print(cv2.contourArea(c)) # for debug
        continue

    # compute the rotated bounding box of the container
    orig = image.copy()
    bbox = cv2.minAreaRect(c)
    bbox = cv2.cv.boxPoints(bbox) if imutils.is_cv2() else cv2.boxPoints(bbox)

    bbox = np.array(bbox, dtype="int")

    # order the contours and draw the bounding box
    bbox = perspective.order_points(bbox)
    cv2.drawContours(orig, [bbox.astype("int")], -1, (0, 255, 0), 2)

    # loop over the original points in bbox and draw them 5px red dots
    for(x, y) in bbox:
        cv2.circle(orig, (int(x), int(y)), 5, (0, 0, 255), -1)

        # unpack the ordered bounding bbox and find midpoints
        (tl, tr, br, bl) = bbox
        (tltrX, tltrY) = midpoint(tl, tr)
        (blbrX, blbrY) = midpoint(bl, br)
        (tlblX, tlblY) = midpoint(tl, bl)
        (trbrX, trbrY) = midpoint(tl, br)

    # draw the midpoints on the image (blue), lines between the midpoints (yellow)
    cv2.circle(orig, (int(tltrX), int(tltrY)), 5, (255, 0, 0), -1)
    cv2.circle(orig, (int(blbrX), int(blbrY)), 5, (255, 0, 0), -1)
    cv2.circle(orig, (int(tlblX), int(tlblY)), 5, (255, 0, 0), -1)
    cv2.circle(orig, (int(trbrX), int(trbrY)), 5, (255, 0, 0), -1)
    cv2.line(orig, (int(tltrX), int(tltrY)), (int(blbrX), int(blbrY)), (255, 0, 0), 2)
    cv2.line(orig, (int(tlblX), int(tlblY)), (int(trbrX), int(trbrY)), (255, 0, 0), 2)

    # complete the Euclidean distances between the midpoints
    dA = dist.euclidean((tltrX, tltrY), (blbrX, blbrY))
    dB = dist.euclidean((tlblX, tlblY), (trbrX, trbrY))

    # use pixel_to_size ration to compute object size
    if pixel_to_size is None:
        pixel_to_size = dB / args["width"]
        distA = dA / pixel_to_size
        distB = dB / pixel_to_size

        # draw the object sizes on the image
        cv2.putText(orig, "{:.2f}cm".format(distA), (int(tltrX - 10), int(tltrY - 10)), cv2.FONT_HERSHEY_DUPLEX, 0.55,
                    (255, 255, 255), 2)
        cv2.putText(orig, "{:.2f}cm".format(distB), (int(trbrX + 10), int(trbrY)), cv2.FONT_HERSHEY_DUPLEX, 0.55,
                    (255, 255, 255), 2)

        # set output window size
        cv2.namedWindow("image", cv2.WINDOW_NORMAL)

        # show the output image
        cv2.imshow("image", orig)
        cv2.waitKey(0)







