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

#symbols
ex0 = r'^\s*(\w{0,3}?)\s*\,?\s*(ORG)\s*(\d+)\s*\/?.*?'
ex1 = r'^\s*(\w{0,3})\s*\,\s*' + keywords + '\s*([-+]?\w+)\s*(I)?\s*\/?.*?'

asm = open(args.asm_files[0]).readlines()

symbol_table = {}
errors = [] #{'msg':'error message','line':3}


address_thresh = 0
#getting threshhold
for l in enumerate(asm):
	m = re.match(ex0,l[1])
	if m :
		print m.span(),
		print m.groups()
		addres_thresh = int(m.groups()[2])

print addres_thresh

#pass 1 
for l in enumerate(asm):
	print l[0]+1,
	m = re.match(ex1,l[1])
	if m:
		print m.span(),
		print m.groups(),
	else :
		print 'error',
	print ''



