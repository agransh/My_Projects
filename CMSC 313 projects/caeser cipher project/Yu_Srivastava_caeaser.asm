;Name: Agransh Srivastava, Matthew Yu
;Class: CMSC 313
;Professor: Ivan Sekyonda
;Date: 6/30/2022
;Desciption: this program takes in user input and uses caeaser cipher
;	     and uses user input to  encrypt any given text


	section .data
shiftVal:		db "Enter shift value: ", 25
shiftValLen:	 	equ $-shiftVal

orgMsg:			db "Enter original message: ", 80
orgMsgLen:		equ $-orgMsg

currMsg:		db "Current message: ", 80
currMsgLen:		equ $-currMsg

enc:			db "Encryption: ", 80
encLen:			equ $-enc

new_line		db 10


	section .bss

string_buff:		resb 160
num_buff:		resb 8
char_buff:		resb 160
en_buff:		resb 160
string_length1:		resb 8


	section .text

	global main 

main:
	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, orgMsg
	mov 	rdx, orgMsgLen
	syscall
	
	mov 	rax, 0
	mov	rdi, 0
	mov 	rsi, string_buff
	mov	rdx, 80
	syscall

	mov 	rax, 1
	mov 	rdi, 1
	mov	rsi, shiftVal
	mov	rdx, shiftValLen
	syscall
	
	mov 	rax, 0
	mov 	rax, 0
	mov 	rsi, num_buff
	mov 	rdx, 8
	syscall
	

;logic goes here
	mov 	rbx, string_buff ;this takes in unencrypted string and gets sentence length
      	call 	str_len
       	mov     r10, 0 ;counter for the  for_loop
	mov 	r8 , 0 ;counter for the for_loop_shift
	mov     r9, num_buff   ;this moves in the key to rdx
        mov     string_buff, rax
	call 	for_loops
str_len:	
	push 	rbx
	push 	rcx

	xor 	rcx, rcx

do_strlen:
	cmp byte [rbx],0
	jz stop_strlen

	inc	rcx
	inc	rbx
	jmp 	do_strlen

stop_strlen:
	mov	rax, rcx
	pop 	rcx
	pop 	rbx
	ret
	
	push 	rax
	mov 	rcx, rax
	dec 	rcx 
	ret
	
 
;FOR LOOP
for_loop:  ;for loop to run until the strings length to shift
        CMP     rcx, r10
        JBE     for_logic

	ret
for_logic:                      ;shifter for our code for(int i = 0; i < str_length; i++){
	call 	is_space
	call 	for_loop_shift
        inc     rcx
        call 	for_loop

is_space:
        jg      byte[rax],'A';checks for space, note if not string_buff make it orgMsg
        inc 	rcx ;if true go to next letter e
	call	for_loop; calls for loop if the function is true 

	call 	for_loop_shift;calls this is funciton is false

;SHIFTER FOR LOOP (NESTED FOR LOOP)
for_loop_shift: ;for(int i = 0; i < shift; i++)
        CMP     r9,r8
        inc     r8
        call    is_wrap


	inc 	rcx; after the first letter is done incrementing it increases the main loops counter by 1 to move to the next letter

	call 	for_loop ;goes back to the for loop after its done incrementing a single character

is_wrap:
        je      byte[rax], 'Z'
        sub     byte[rax], 26   ;turns it to an A

        je      byte[rax], 'z'
        sub     byte[rax], 26   ;turns it to a B

        add     byte[rax], 1    ;shifts up a letter by 1

        call    for_loop_shift

	
;output
	mov 	rax, 1
	mov	rdi, 1
	mov	rsi, string_buff
	mov	rdx, 1
	syscall
	
	mov	rax,1
	mov	rdi,1
	mov 	rsi,new_line
	mov 	rdx,1
	syscall
	 
	mov     rax, 1
        mov     rdi, 1
        mov     rsi, en_buff
        mov     rdx, 1
        syscall

        mov     rax,1
        mov     rdi,1
        mov     rsi,new_line
        mov     rdx,1
        syscall

exit:
	mov rax, 60
	xor rdi,rdi
	syscall
