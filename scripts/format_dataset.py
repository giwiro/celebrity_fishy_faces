#!/usr/bin/env python3
import argparse
import os
import csv
import pprint

# Parsing arguments
parser = argparse.ArgumentParser()
parser.add_argument("--path", "-p", help="The path of the root folder containing the images", required=True)
parser.add_argument("--out", "-o", help="The path for the output", required=True)

args = parser.parse_args()


# Read subdirs
subfolders = [(idx, s) for idx, s in enumerate(os.listdir(args.path))]

# Check if our path exsist
if not os.path.exists(args.out):
	os.makedirs(args.out)

# Generate id/name csv map
with open(os.path.join(args.out, "map.csv"), "w", newline="") as csvmap:
	mapwriter = csv.writer(csvmap, delimiter=";", quotechar=" ", quoting=csv.QUOTE_MINIMAL)
	for s in subfolders:
		mapwriter.writerow(list(s))

# Generate training dataset
with open(os.path.join(args.out, "dataset.csv", "w", newline="")) as csvdataset:
	mapwriter = csv.writer(csvmap, delimiter=";", quotechar=" ", quoting=csv.QUOTE_MINIMAL)
	# for s in subfolders:
