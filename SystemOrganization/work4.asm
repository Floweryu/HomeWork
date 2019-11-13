; 选择排序算法。初始数据定义了一个buf空间进行存储，不需要从键盘输入，直接定义即可。最后也是把buf里面的数据排好序输出。
data segment
    buf db 9, 87, 255, 13, 123
    count equ $-buf      ; 得到数据个数
data ends

stack segment stack
    db 200 dup(0)
stack ends

code segment
    assume cs:code, ds:data, ss:stack

start:
    mov ax, data
    mov ds, ax              ; 15~16， 写后读相关

    mov si, offset buf      ; 把buf的初始地址存入si
    mov cx, count           ; 设置计数器，存入数据个数

loop1:
    ; 前面si存入buf初始值就相当于 for (i = 1),接着执行外层循环内的语句
    call loop2              ; 调用内层循环

    inc si                  ; 18,25；si 写后写相关
    dec cx                  ; 19,26；cx 写后写相关
    jnz loop1               ; cx 没到0继续循环，说明数没有遍历完
; (24 ~ 28)行相当于 for(; i <= length-1; i++),即执行完外部循环后的遍历

; 在内外层循环都完成后，显示数据
    mov si, offset buf      ; 设置显示初始地址
    mov cx, count           ; 设置显示数据的个数

show:
    call output             ; 调用输出函数
    ; 每次调用都显示一个数字
    inc si                  ; 31,37；si 写后写相关
    dec cx                  ; 32,38; cx 写后写相关
    jnz show

    mov ah, 4ch             ; 结束程序
    int 21h


; 子程序，内部循环
loop2 proc near

    push cx                 ; 19,48行是写后读相关

    ; di 为内部循环指针，si 为外部循环指针，ax 为已经排好序的数据个数(临时存储)
    mov di, si              
    mov ax, di              ; 51~52，对di是写后读相关

    sub ax, offset buf      ; 52, 54，对ax是写后写相关

    ; dx 作为内部循环的次数（临时存储）
    mov dx, count           
    sub dx, ax              ; 57~58，dx 写后写相关
    mov cx, dx              ; 58~59，dx 写后读相关。内部循环计数器cx，此时，ax 和 dx 已经空出

    mov bx, si              ; 存储最小值的地址
; (50 ~ 59) 行处理了内外部循环的执行次数以及指针的存储

; 排序函数————选择排序
sort:
    mov al, [bx]            ; 61,66，bx 写后读相关。把地址对应的数据存入
    mov dl, [di]            ; 51,67，对 di 是写后读相关。
    cmp al, dl              ; 66~68 对al,dl 是写后读相关
    ja min
    jmp continue            ; 否则， 指针遍历，不对 bx 操作   

; 把较小的值对应的地址存入 bx
min:
    mov bx, di
    jmp continue

; 指针遍历
continue:                   
    inc di                  ; 74,79;di 读后写相关
    dec cx                  ; 内部循环次数
    jnz sort                ; 还没遍历完，返回内部循环排序
    jmp swap                ; 每次内循环遍历完就确定一个最小值

; 交换函数
swap:                       
    mov al, [si]
    xchg al, [bx]           ; 86~87，al写后读相关
    mov [si], al            ; 86, 88，[si]读后写相关


    pop cx                  ; 出栈外层循环次数， 对应 push cx

    ret                     ; 内部循环遍历完,返回
loop2 endp

; 输出子程序
; 把数字除以10，分离每一位进栈，然后再出栈显示每一位数
output proc near
    push cx                 ; 保护现场

    mov dl, [si]            
    mov bl, 10              ; 设置除数
    mov cx, 0               ; 设置余数的个数计数器
; 求余数函数
let1:
    mov ah, 0               ; 存余数
    mov al, dl              ; 101,107，dl 写后读相关
    div bl                  ; 102,108, bl 写后读相关。余数放在 ah，商在 al
    push ax                 ; 余数进栈
    inc cx                  ; 余数个数加一
    cmp al, 0               ; 判断商是否为0
    jle let2                ; 小于 0 进入显示
    mov dl, al              ; 否则，把商存入dl，待下次循环作为被除数
    jnz let1
; 显示数字函数 
let2:
    pop ax                  ; 出栈余数
    add ah, 30h             ; 变为ASCII
    mov dl, ah              ; 显示余数
    mov ah, 2               ; 119~120，读后写相关
    int 21h

    dec cx                  ; 显示一个余数后计数器减一
    cmp cx, 0               ; 123,124，cx 写后读相关
    jnz let2                ; 有，就继续显示

    mov ah, 2               ; 没有，即输完一个数，显示一个空格
    mov dl, 20h            
    int 21h

    pop cx                  ; 恢复现场

    ret
output endp

code ends
    end start