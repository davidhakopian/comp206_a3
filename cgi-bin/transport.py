#!/usr/bin/env python
import cgitb
import cgi
import csv

print "Content-type: text/html"
print

cgitb.enable()
form = cgi.FieldStorage()
#inventory = form["inventory"].value
inventory="0,0"
#backUrl = form["url"].value
backUrl = "http://www.cs.mcgill.ca/~dhakop/cgi-bin/transport.py"
occupied = 0;
with open('../resources.csv', 'rb') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in spamreader:
                occupied = int(row[2])
print inventory
print backUrl
if occupied == 1:
        with open('../waiting.html', 'r') as myfile:
                data=myfile.read()
        data = data.replace("value=\"inventory\"", "value=\"" + inventory + "\"")
        data = data.replace("value=\"url\"", "value=\"" + backUrl + "\"")
        data = data.replace("action=\"url\"", "action=\"" + backUrl + "\"")
        print data
else:
        with open('../index.html', 'r') as myfile:
                data=myfile.read().replace('\n', '')
        print data