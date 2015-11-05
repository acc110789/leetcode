#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import getopt
import multiprocessing
import threading
import urllib.request

class MyThread(threading.Thread):
    def __init__(self, arg):
        threading.Thread.__init__(self)
        threading.stack_size(32768)
        self.arg = arg

    def run(self):
        req = urllib.request.urlopen(self.arg).read()
        print("HTTP GET", self.arg, req)

def useage():
    print("--number 1024 --url http://www.baidu.com")

try:
    opts, args = getopt.getopt(sys.argv[1:], "hnu:v", ["help", "number=", "url="])
except getopt.GetoptError as err:
    print(str(err))
    useage()
    sys.exit(2)

number = 1024
threads = 64
url = "http://www.baidu.com"
verbose = False

for o, a in opts:
    if o == "-v":
        verbose = True
    elif o in ("-h", "--help"):
        useage()
        sys.exit()
    elif o in ("-n", "--number"):
        number = a
    elif o in ("-u", "--url"):
        url = a
    else:
        assert False, "unhandled option"

def worker(url):
    for i in range(threads):
        MyThread(url).start()

for i in range(int(int(number) / threads)):
    multiprocessing.Process(target=worker, args=(url,)).start()
