#!/usr/bin/python3

# QOTD Servers
# djxmmx.net
# cygnus-x.net

import argparse
import socket

def stringonly(astr):
    """ Check if hostname argument is a string """
    try:
        int(astr)
    except ValueError:
        return astr
    raise argparse.ArgumentTypeError('only a string type accepted')

parser = argparse.ArgumentParser(description='Retrieve QOTD from user chosen server')
parser.add_argument('-H', '--hostname', type=stringonly, metavar='', default='djxmmx.net', help='Hostname of QOTD server; Default djxmmx.net')
parser.add_argument('-P', '--port', type=int, metavar='', default=17, help='Port for QOTD server; Default 17')
args = parser.parse_args()

maxBytes = 1024

print("Pulling quote of the day from {}".format(args.hostname))

# Create the socket
sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the socket
try:
    sockfd.connect((args.hostname, args.port))
except socket.error as err:
    print("Caught exception socket.error : {}".format(err))

# Recieve and print the message
qotd_message = sockfd.recv(maxBytes)
print("{}".format(qotd_message))

# Close the socket
sockfd.close()