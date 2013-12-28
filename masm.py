#!/usr/bin/env python


# . (dot) any char

import argparse,re
import logging

logging.basicConfig(level='INFO')

parser = argparse.ArgumentParser(prog='masm.py',description='Assembler for mano machine instruction set.')
parser.add_argument('asm_files',nargs='+', help='file name(s)')
args = parser.parse_args()

keywords = '(' + '|'.join([ i.split()[0] for i in open('instruction_set.txt').readlines() if i.split()]) + ')'
instruction_set = { i.split()[0]:i.split()[2] for i in open('instruction_set.txt').readlines() if len(i.split()) >1 }

# ex1 = r'^\s*(\w{0,3})\s*\,\s*(DEC|HEX)\s*([-+]?\w+)\s*\/?.*?'
# ex1 = r'^\s*(\w{0,3})\s*\,\s*' + keywords + '\s*([-+]?\w+)\s*\/?.*?'

#symbols
ex0 = r'^\s*(\w{0,3}?)\s*\,?\s*(ORG)\s*(\d+)\s*(\/?.*)'
ex1 = r'^\s*(\w{0,3})\s*\,\s*' + keywords + '\s*([-+]?\w*)\s*(I)?\s*(\/?.*)'
ex2 = r'^\s*(\w{0,3})\s*\,?\s*' + keywords + '\s*([-+]?\w*)\s*(I)?\s*(\/?.*)'
# ex1 = r'^\s*(\w{0,3})\s*\,\s*' + keywords + '\s*([-+]?\w+)\s*(I)?\s*(\/?.*)'

asm = open(args.asm_files[0]).readlines()

symbol_table = {}
errors = [] #{'msg':'error message','line':3}


##pass one
address_offset = 0
address_start  = 0
#getting threshhold
for l in enumerate(asm):
	m = re.match(ex0,l[1])
	if m :
		logging.debug( 'ORG found')
		logging.debug( 'span:{0}'.format(m.span()) )
		logging.debug( 'line:{0}'.format(m.groups()) )

		address_start = l[0]
		address_offset = int(m.groups()[2])
		logging.info('Address offset changed: {0}'.format(address_offset))

	m = re.match(ex1,l[1])
	if m:
		logging.debug('span:{0}'.format(m.span()) )
		logging.debug( 'line:{0}'.format(m.groups()) )
		lable = m.groups()[0]

		if lable in symbol_table.keys():
			logging.info('Error in line :{0}, the same lable "{1}" was used before.'.format(l[0]+1,lable))
			errors.append({'msg':'same lable used bfore','line':l[0]+1,'code':'SMLBL','extra':lable})
			continue
		logging.info('{0} was added to symbol table.'.format(lable) )

		symbol_table[lable] = l[0] + address_offset - address_start


program = {}
address_offset = 0
address_start  = 0

#Pass two
for l in enumerate(asm):
	m = re.match(ex0,l[1])
	if m :
		logging.debug( 'ORG found')
		logging.debug( 'span:{0}'.format(m.span()) )
		logging.debug( 'line:{0}'.format(m.groups()) )

		address_start = l[0]
		address_offset = int(m.groups()[2])
		logging.info('Address offset changed: {0}'.format(address_offset))
		continue

	adrr = l[0] + address_offset - address_start
	m = re.match(ex2,l[1])

	if m:
		logging.debug('span:{0}'.format(m.span()) )
		logging.info( 'line:{0}'.format(m.groups()) )
		instruction = m.groups()[1]
		if instruction in instruction_set.keys():
			program[adrr] = {'instruction':instruction,'operand':m.groups()[2]}
		else:
			logging.info('line error at line {0}'.format(l[0]))

	else:
		logging.info('line error at line {0}'.format(l[0]))


# print address_offset

# #pass 1 
# for l in enumerate(asm):
# 	print l[0]+1,
# 	m = re.match(ex1,l[1])
# 	if m:
# 		print m.span(),
# 		print m.groups(),
# 	else :
# 		print 'error',
# 	print ''



print 'Symbol','\t','Address'
for k in sorted(symbol_table,key=lambda n:symbol_table[n]):
	print k,'\t',symbol_table[k]


print 'Address\t','Instruction\t','Operand\t'
for k in sorted(program):
	print k,'\t',
	print program[k]['instruction'],'\t'*2,
	print program[k]['operand'],'\t',
	print


print errors
print keywords
