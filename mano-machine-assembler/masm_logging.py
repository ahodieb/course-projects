#!/usr/bin/env python


# . (dot) any char

import argparse,re
import logging

logging.basicConfig(level='INFO')
logging.basicConfig(format='%(message)s',level='INFO')

parser = argparse.ArgumentParser(prog='masm.py',description='Assembler for mano machine instruction set.')
parser.add_argument('asm_files',nargs='+', help='file name(s)')
args = parser.parse_args()

keywords = '(' + '|'.join([ i.split()[0] for i in open('instruction_set.txt').readlines() if i.split()]) + ')'
instruction_set = { i.split()[0]:i.split()[2] for i in open('instruction_set.txt').readlines() if len(i.split()) >1 }

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
		#org found 
		logging.debug( 'ORG found')
		logging.debug( 'span:{0}'.format(m.span()) )
		logging.debug( 'line:{0}'.format(m.groups()) )
		#setting the symbole start adress
		address_start = l[0]
		address_offset = int(m.groups()[2])-1
		logging.info('Address offset changed: {0}'.format(address_offset))

	m = re.match(ex1,l[1])
	if m:
		logging.debug('span:{0}'.format(m.span()) )
		logging.debug( 'line:{0}'.format(m.groups()) )
		lable = m.groups()[0]

		if lable == '':
			logging.info('Error in line :{0}, lable expected "{1}".'.format(l[0]+1,lable))
			errors.append({'msg':'missing lable before , ','line':l[0]+1,'code':'MSLBL','extra':''})
			continue

		elif lable in symbol_table.keys():
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
		address_offset = int(m.groups()[2])-1
		logging.info('Address offset changed: {0}'.format(address_offset))
		continue

	adrr = l[0] + address_offset - address_start
	m = re.match(ex2,l[1])

	if m:
		logging.debug('span:{0}'.format(m.span()) )
		logging.info( 'line:{0}'.format(m.groups()) )
		instruction = m.groups()[1]
		n = 0

		if instruction in instruction_set.keys():

			n = int(instruction_set[instruction],16)

			if n >= 0 and n < 7 : #memory refrance instruction_set
				if m.groups()[3] == 'I':
					n+=7

				n = int(str(n*1000 + symbol_table[m.groups()[2]]),16)


			elif n >=int('7001',16) and n <= int('7800',16): #register instruction
				pass
			
			elif n >=int('F040',16) and n <= int('F800',16): #register instruction
				pass
			
			else:
				pass
			
		elif instruction in {'DEC','HEX','END'}:
			if instruction == 'DEC' : 
				n = int(m.groups()[2])
				if n < 0:
					n = 65536 + n +1
			elif instruction == 'HEX':
				n = int(m.groups()[2],16)

			print 'NNNNNNNNNNNNNNN'
			print n

		else:
			logging.info('Error in line :{0}, Unknown Instruction "{1}".'.format(l[0]+1,instruction))
			errors.append({'msg':'unknown instruction , ','line':l[0]+1,'code':'UKINS','extra':instruction})

		program[adrr] = {'instruction':instruction,'operand':m.groups()[2],'bin':bin(n)[2:],'hex':hex(n)[2:]}
	

	else:
		logging.info('Error in line :{0}, Unknown Instruction "{1}".'.format(l[0]+1,l[1]) )
		errors.append({'msg':'unknown instruction ','line':l[0]+1,'code':'UKINS','extra':l[1]})
		



print 'Symbol','\t','Address'
for k in sorted(symbol_table,key=lambda n:symbol_table[n]):
	print k,'\t',symbol_table[k]


print 'Address\t','Hex\t','Binary\t','\t','\t','Instruction\t','Operand\t'
for k in sorted(program):
	print k,'\t',	
	print program[k]['hex'].zfill(4).upper(),'\t',	
	print program[k]['bin'].zfill(16),'\t',
	print program[k]['instruction'],'\t'*2,
	print program[k]['operand'],'\t',
	print ''

print ''

print errors
