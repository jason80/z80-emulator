
outbuf: equ	2000h

		ld b, 80		; Setup counter
		ld hl, inbuf	; Setup pointers
		ld de, outbuf
		
loop:	ld a, (hl)		; Get next byte from input buffer
		ld (de), a		; Store in output buffer
		cp 0Dh			; Is it a CR ?
		jr z, done		; Yes finished
		inc hl			; Increments pointers
		inc de
		djnz loop		; Loop back if 80 bytes have not been moved
		
done:
		
		halt
		
inbuf:	defm "Hello", 0Dh

		end

