#!/usr/bin/env python


# . (dot) any char

import argparse

parser = argparse.ArgumentParser(prog='masm.py',description='Assembler for mano machine instruction set.')
parser.add_argument('asm_files',nargs='+', help='file name(s)')
args = parser.parse_args()


ex1 = r'^\s*(\w{0,3})\s*\,\s*(DEC|HEX)\s*([-+]?\w+)\s*\/(.*)'

