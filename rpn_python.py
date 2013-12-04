

op_order    = { '+':0,'-':0, # operator Precedence
				'*':1,'/':1,'%':1,
				'^':2,
				'(':3,')':3
			  }

def infix(expr):
	infix_ = []
	s = ''
	for i in range(len(expr)):
		if expr[i] in '1234567890':
			s+=expr[i]

	 	elif expr[i] in '+-/*^%()':
	 		if(s != ''):
				infix_.append(int(s))
			s = ''
			infix_.append(expr[i])
	if s != '':
		infix_.append(int(s))


	return infix_



def postfix (infix):
	postfix_  = []
	op_stack = []

	for i in infix:
		print i
		if type(i) is int:
			postfix_.append(i)

		elif i == ')':
			while len(op_stack) > 0 and (op_stack[-1] != '('):
				postfix_.append(op_stack.pop())
			op_stack.pop()

		else :

			while len(op_stack) > 0 and not ( op_order[ op_stack[-1] ] < op_order[i]):
				postfix_.append(op_stack.pop())


			op_stack.append(i)
	while(op_stack):
		postfix_.append(op_stack.pop())


	return postfix_



def main():
	expr  =	raw_input('Enter Expresion : ')
	i = infix(expr)
	p = postfix(i)

	print 'Infix',i
	print 'Postfix',p


if __name__ == '__main__':
	main()

