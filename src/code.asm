_printString PROTO
_getString PROTO

extrn ExitProcess : proc; defining the exit process

.data

msg1 byte "e",0

.code
_asmMain PROC

	push rbp
	sub rsp, 20h
	lea rbp, [rsp + 20h]		; align stack pointer

	lea rcx, msg1
	call _hashChar


	lea rsp, [rbp];				stack eplilogue code
	pop rbp
	ret
	xor rcx,rcx
	call ExitProcess; starting the exit process


_asmMain ENDP; ending main


_hashChar PROC
	push rbp
	push rbx

	xor rdx, rdx
	mov rax, [rcx]
	mov rcx, 8
	div rcx

	pop rbx
	pop rbp
	ret
_hashChar ENDP; ending hashing function


END; ending the program