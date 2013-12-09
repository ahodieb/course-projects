#!/usr/bin/env python


# . (dot) any char

import argparse,re

parser = argparse.ArgumentParser(prog='masm.py',description='Assembler for mano machine instruction set.')
parser.add_argument('asm_files',nargs='+', help='file name(s)')
args = parser.parse_args()

keywords = '(' + '|'.join([ i.split()[0] for i in open('instruction_set.txt').readlines() if i.split()]) + ')'
instructions = { i.split()[0]:i.split()[2] for i in open('instruction_set.txt').readlines() if len(i.split()) >1 }

# ex1 = r'^\s*(\w{0,3})\s*\,\s*(DEC|HEX)\s*([-+]?\w+)\s*\/?.*?'
# ex1 = r'^\s*(\w{0,3})\s*\,\s*' + keywords + '\s*([-+]?\w+)\s*\/?.*?'

ex = r'^\s*?(\w{0,3}?)\s*\,?\s*?' + keywords + '\s*?([-+]?\w+?)\s*?(I)?\s*\/?.*?'

asm = open(args.asm_files[0]).readlines()

for i in range(len(asm)):
	print i+1,
	m = re.match(ex,asm[i])
	if m:
		print m.span(),
		print m.groups(),
	else :
		print 'error',
	print ''



