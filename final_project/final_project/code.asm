_printString PROTO
_getString PROTO
_writeFile PROTO
_clearFile PROTO
_readFile PROTO

extrn CreateFileA : proc	; A = ANSI
extrn ReadFile : proc
extrn CloseHandle : proc

extrn ExitProcess : proc; defining the exit process

.data

msg1 byte "e",0; testing
msg2 byte "gumping it",0
charBuffer byte 64 DUP (0)


num QWORD 63
sourceFile BYTE "input.txt",0			;name of source file
FD QWORD ?
read QWORD ?
charsRead QWORD 0
closed QWORD ?

.code
_asmMain PROC

	sub rsp, 10h				; reserve for return and rbp
	sub rsp, 20h
	lea rbp, [rsp + 20h]		; align stack pointer

	lea rsi, msg2
	lea rdi, charBuffer
	mov rcx, 10
	cld
	rep movsb


	lea rcx, charBuffer
	mov rdx, 0
	call _readFile

	;call _iterateBuffer

	xor rax,rax
	lea rsp, [rbp];				stack eplilogue code
	pop rbp
	xor rcx,rcx
	call ExitProcess; starting the exit process

_asmMain ENDP; ending main


_hashChar PROC;		this function takes a char and converts it to an index of an array of 8 elements

	xor rdx, rdx;		clearing remainder register
	mov rax, [rcx];		moving the divitend to the rax register
	mov rcx, 1;			moving the divisor to the rcx register
	div rcx;			dividing char by 8

	ret
_hashChar ENDP; ending hashing function

_iterateBuffer PROC;	by Abbi G: iterate through charBuffer will be adapted for later use. Currently just shifts up the bits

	mov rbx, 10
	lea rsi, offset charBuffer
	xor rdi,rdi

	butterItr:
		mov cl, [rsi+rdi*1]
		inc cl
		mov [rsi+rdi*1], cl
		inc rdi
		cmp rdi, rbx
		jne butterItr

	ret
_iterateBuffer ENDP;

END; ending the program