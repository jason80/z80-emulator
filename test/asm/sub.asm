
start:		ld	A, -127
			ld	(2354h), A
			ld	A, 127
			ld	HL, 2354h
			sub (HL)
			halt
			end
			
