#!/usr/bin/env python3
import argparse
import os
import csv
import cv2
import time
import pprint

# Parsing arguments
parser = argparse.ArgumentParser()
parser.add_argument("--path", "-p", help="The path of the root folder containing the images", required=True)
parser.add_argument("--out", "-o", help="The path for the output", required=True)
parser.add_argument("--file", "-f", help="The path of the file to haarcascade trained file")

args = parser.parse_args()

# Statistics dic
stats = {}
start_time = time.time()

base_folder = args.path
out_folder = os.path.join(args.out, "extracted_faces")

# Initialize cascade
face_cascade = cv2.CascadeClassifier(args.file)

# Read subdirs
subfolders = [(idx, s) for idx, s in enumerate(os.listdir(base_folder))]

if len(subfolders) < 1:
	raise Exception("Folder must contain 1 or more folders")

# Check if our path exsist
if not os.path.exists(out_folder):
	os.makedirs(out_folder)

def process_folder(folder):
	#  Validate if it's a file and with an image extension
	files = [(idx, f) for idx, f in enumerate(os.listdir(os.path.join(base_folder, folder))) 
			if os.path.isfile(os.path.join(base_folder, folder, f)) and f.lower().endswith(('.png', '.jpg', '.jpeg'))]

	print(f"Processing:\t{folder}")

	for file in files:
		# Total | Asserts | Fails
		if folder not in stats:
			stats[folder] = [0, 0, 0]
		else:
			stats[folder][0] += 1

		# With dot included, that's why 4
		extension = file[1][len(file[1]) - 4:]
		img = cv2.imread(os.path.join(base_folder, folder, file[1]))
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		faces = face_cascade.detectMultiScale(gray, 1.3, 5)

		if len(faces) > 0:
			# Asuming there's one face per file and it's the first found
			face = faces[0]

			x = face[0]
			y = face[1]
			w = face[2]
			h = face[3]
			roi_color = img[y:y+h, x:x+w]
			if not os.path.exists(os.path.join(out_folder, folder)):
				os.makedirs(os.path.join(out_folder, folder))

			cv2.imwrite(os.path.join(out_folder, folder, f"{file[0]}{extension}"), roi_color)
			# Mark it as an assert
			stats[folder][1] += 1
		else:
			# Mark it as an failure
			stats[folder][2] += 1

for sub in subfolders:
	process_folder(sub[1])

print("-------------------------------- FINISHED EXECUTION --------------------------------")
end_time = time.time()
acum_total = 0
acum_assert = 0
acum_failure = 0
print(f"\nElapsed time: {end_time - start_time}")
print("Results:\n")

for s in stats:
	acum_total += stats[s][0]
	acum_assert += stats[s][1]
	acum_failure += stats[s][2]
	success = 0
	if stats[s][0]:
		success = stats[s][1] / stats[s][0]
	print(f"{s} ({'{0:.2f}'.format(success * 100)}%):\t\t\t\tTotal: {stats[s][0]}\tSuccess: {stats[s][1]}\tFails: {stats[s][2]}")


acum_success = 0
if acum_total:
		acum_success = acum_assert / acum_total
print(f"\n\nAcum Stats ({'{0:.2f}'.format(acum_success * 100)}%)\t\t\t\tTotal: {acum_total}\tSuccess: {acum_assert}\tFails: {acum_failure}")