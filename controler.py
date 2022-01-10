import sys
import subprocess
import argparse

parser=argparse.ArgumentParser(
    description='''This is a controller for Cheeky Kitten, to run preprogramed operations :-). ''',
    epilog="""Beta Version 0.3 Josjuar Lister 2021-2022""")
parser.add_argument('file', metavar='file', nargs='+')
parser.add_argument('-d', '--double', action="store_true", help='double shift')
parser.add_argument('-e', '--scramble', action="store_true", help='double encrypt and rotate once')
parser.add_argument('-k', '--key', help='key used for encryption')
parser.add_argument('-x', '--hex-output', action="store_true", help='output readable hex')
args=parser.parse_args()

c = "cheeky"
b = "-b"
r = "-r"
k = "-k"

if args is None:
	print('run btphone -h')
	exit()

#if sys.argv[1] is not None:
#	o = sys.argv[1]
#if sys.argv[0] is not None:
#	f = sys.argv[0]
#else:
#	print("no input file supplied...\n")
#	i = input()#read from stdin

if args.file:
	f = args.file

def yesno(message):
	yesno_possitives = ('y', 'yes', 'yep', 'yea', 'oui', 'si', 'yar', 'uha', 'please', 'ye', 'why', 'make', 'certainly', 'Y', 'Yes', 'Yep', 'Yea', 'Oui', 'Si', 'Yar', 'Uha', 'Please', 'Ye', 'Why', 'Make', 'Certainly')
	reply = input(message)
	reply = list(reply.split(" "))
	for word in reply:
		if word in possitives:
			return True
if args.double:
	if args.key is None:
		s1 = subprocess.Popen([c, b, f], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		s2 = s1.communicate([c, b])
		print(s2)
	else:
		print("I will produce a cheeky %s", file)
		if yesno('continue?\n'):
			p = args.key
			double = subprocess.Popen([c, b, f, k, p, "|", c, b, "|", c, b], stdout=PIPE, stderr=PIPE)
			stdout, stderr = subprocess.communicate()
			print(stdout)