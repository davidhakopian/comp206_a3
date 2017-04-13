#!/usr/bin/env python
import cgitb
import cgi
import csv

print "Content-type: text/html"
print

#cgitb.enable()
#form = cgi.FieldStorage()
spamreader = csv.reader(open('../resources.csv', 'rb'))
lines = [l for l in spamreader]
print lines
print lines[0][2]
lines[0][2] = "0"
print lines

spamwriter = csv.writer(open('../resources.csv', 'w'))
spamwriter.writerows(lines)



