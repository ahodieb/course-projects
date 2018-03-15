#!/usr/bin/env python


op_order    = { '+':0,'-':0, # operator Precedence
				'*':1,'/':1,'%':1,
				'^':2,
				'(':-1,')':-1
			  }

def infix(expr):
	infix_ = []
	s = ''
	for e in expr:
		if e in '1234567890.':
			s+=e

	 	elif e in '+-/*^%()':
	 		if(s != ''):
				infix_.append(float(s))
			s = ''
			infix_.append(e)
	if s != '':
		infix_.append(float(s))

	return infix_



def postfix (infix):
	postfix_  = []
	op_stack = []

	for i in infix:
		if type(i) is float:
			postfix_.append(i)

		elif i == '(':
			op_stack.append(i)

		elif i == ')':
			while op_stack and (op_stack[-1] != '('):
				postfix_.append(op_stack.pop())
			op_stack.pop()

		else :
			while op_stack and op_order[ op_stack[-1] ] > op_order[i]:
				postfix_.append(op_stack.pop())
			op_stack.append(i)

	while(op_stack):
		postfix_.append(op_stack.pop())
	if '(' in postfix_ : print 'Expression error'
	return postfix_


def solve(p):

	result_stack = []
	for v in p:
		if v not in op_order :
			result_stack.append(v)
		else:
			op1 = ''
			op2 = ''
			if result_stack : 
				op2 = result_stack.pop()
			else :
				print 'Expression Error'
			
			if result_stack : 
				op1 = result_stack.pop()
			else :
				print 'Expression Error'
			if v == '^':
				v = "**"
				op1 = int(op1)
				op2 = int(op2)
			r = eval(str(op1) + v + str(op2))
			result_stack.append(r)

	return result_stack[0]



def main():

	expr  =	raw_input('Enter Expresion : ')
	# expr = "((7.5*2.3)/3 + 3 * (5/2.0)"
	i = infix(expr)
	p = postfix(i)
	s = solve(p)

	print 'Infix',i
	print 'Postfix',p
	print 'Solution',s

	
	# print 'correct' ,eval(expr)
	# if s == eval(expr) : print 'correct evaluation.'


if __name__ == '__main__':
	main()

