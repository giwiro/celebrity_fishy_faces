#!/usr/bin/env python3
import argparse
import os
import csv
import pprint

# Parsing arguments
parser = argparse.ArgumentParser()
parser.add_argument("--full-path", "-p", help="The full path of the root folder containing the images", required=True)
parser.add_argument("--out", "-o", help="The path for the output", required=True)

args = parser.parse_args()
full_path = args.full_path
out_path = args.out

# Read subdirs
subfolders = [(idx, s) for idx, s in enumerate(os.listdir(full_path)) if os.path.isdir(os.path.join(full_path, s))]

# Check if our path exsist
if not os.path.exists(out_path):
	os.makedirs(out_path)


def process_folder(id, folder, writer):
	#  Validate if it's a file and with an image extension
	files = [(idx, f) for idx, f in enumerate(os.listdir(os.path.join(full_path, folder))) 
			if os.path.isfile(os.path.join(full_path, folder, f)) and f.lower().endswith(('.png', '.jpg', '.jpeg'))]

	print(f"Adding:\t{folder}")

	for file in files:
		writer.writerow([os.path.join(full_path, folder, file[1]), id])


# Generate id/name csv map
with open(os.path.join(out_path, "map.csv"), "w", newline="") as csvmap:
	mapwriter = csv.writer(csvmap, delimiter=";", quotechar=" ", quoting=csv.QUOTE_MINIMAL)
	# Generate training dataset
	# This must be in order so, using threads might not be a good option
	with open(os.path.join(out_path, "dataset.csv"), "w", newline="") as csvdataset:
		datasetwriter = csv.writer(csvdataset, delimiter=";", quotechar=" ", quoting=csv.QUOTE_MINIMAL)
		for s in subfolders:
			# Write (id, name) in map csv
			mapwriter.writerow(list(s))
			process_folder(s[0], s[1], datasetwriter)
