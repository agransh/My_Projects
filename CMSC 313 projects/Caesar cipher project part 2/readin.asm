extern freeUp
extern readIn
extern printf

	section .data
msg     db      "This is the original message: ", 10 , 0
msg_len equ     $-msg

fmtmsg  db      "Enter a message to replace the original message", 10, 0

fmtmsg2 db      "Here is the new message", 10, 10, 0

fmtpf   db      "%s", 10, 0

	section .bss
temp 	resb	2
stringarr resq	1
	
	section .text
	global main


main:
	mov	qword[stringarr],msg
	
	mov	rdi, fmtpf
	mov	rsi , [stringarr]
	mov 	rax,0
	call 	printf

	mov	rdi, fmtmsg
	mov	rax,0
	call 	printf
;show:
	



readIn:
	mov 	rdi,msg
	call 	readIn
	mov	[stringarr],rax
	
	mov 	rdi,fmtmsg2
	mov	rdx, 0
	call 	printf
	
	mov 	rdi, fmtpf
	mov 	rsi, [stringarr]
	mov 	rax,0
	call	printf

exit:
	xor 	rsi, rsi
	mov 	rdi, [stringarr]
	call 	freeUp
	xor 	rax,rax
	ret
	
