; 向量计算程序; 注释前面的数字是行号 
; 长度64的向量，数据直接定义在内存中，设置x向量和y向量，为了方便设向量各个方向值相等,计算结果各方向值为48。
data segment
    x db 64 dup(5)
    y db 64 dup(3)
    a db 64 dup(0)      ; 存放 x+y
    b db 64 dup(0)      ; 存放 x-y
    c db 64 dup(0)      ; 存放最后结果
    count equ 64
data ends

stack segment stack
    db 200 dup(0)
stack ends

code segment
    assume cs: code, ds: data, ss: stack

start:
    mov ax, data
    mov ds, ax

    mov si, 0
    mov bx, 0

; x + y 运算
_add:
    mov dl, 0
    mov bx, offset x
    mov dl, [bx + si]        ; 23,30；si 写后读相关。 28,30; dl 写后写相关
    mov bx, offset y         ; 29,31；bx 写后写相关
    add dl, [bx + si]        ; 30,32; 写后写相关
    mov bx, offset a         ; 31,33；bx 写后写相关 
    mov [bx + si], dl        ; 32,34； dl 写后读相关。相加结果存到 a 中

    inc si                   ; 34,36；读后写相关
    cmp si, count
    jle _add

    mov si, 0
    mov bx, 0

; x - y 运算
_sub:
    mov dl, 0
    mov bx, offset x         ; 41,46; bx写后写相关
    mov dl, [bx + si]        ; 40,47; si 写后读相关。45,47; dl 写后写相关
    mov bx, offset y         ; 46,48; bx写后写相关
    sub dl, [bx + si]        ; 47,49; dl 写后写相关
    mov bx, offset b         ; 48,50; bx写后写相关
    mov [bx + si], dl        ; 49,51; dl 写后读相关。相减结果存到 b 中

    inc si                   ; 51,53; si 读后写相关
    cmp si, count
    jle _sub

    mov si, 0
    mov cl, 2
; 移位运算
_sal:
    mov al, [bx + si]       ; 这里 bx 继承了前面的 b 的地址
    sal al, cl              ; 61,62; al 写后写相关
    mov [bx + si], al       ; 62~63; al 写后读相关
    inc si
    cmp si, count           ; 64,65; si 写后读相关
    jle _sal

    mov si, 0
_addxy:
    mov dl, 0
    mov bx, offset b        
    mov dl, [bx + si]       ; 70,72; dl 写后写相关
    mov bx, offset a        ; 71,73; bx 写后写相关
    add dl, [bx + si]       ; 72,74; dl 写后写相关
    mov [bx + si], dl       ; 把相加结果存到 a 中
    inc si
    cmp si, count           ; 76,77; si 写后读相关
    jle _addxy

    mov si, 0
    mov cl, 3
; 最后乘以3，结果放到 c 中
_mul3:
    mov al, 0
    mov bx, offset a
    mov al, [bx + si]       ; 84,86; al 写后写相关
    mul cl                  ; 81,87; cl 写后读相关
    mov bx, offset c        ; 85,88; bx 写后写相关
    mov [bx + si], al       
    inc si                  
    cmp si, count           ; 90,91; si 写后读相关
    jle _mul3

    mov bx, offset c
    mov si, 0
show:
    call output
    inc si                  ; 95,98; si 写后写相关
    cmp si, count           ; 98,99; si 写后读相关
    jl show

    mov ah, 4ch
    int 21h

; 输出子程序
; 把数字除以10，分离每一位进栈，然后再出栈显示每一位数
output proc near
    mov dl, [bx + si]      
    push bx      
    mov bl, 10              ; 设置除数
    mov cx, 0               ; 设置余数的个数计数器
; 求余数函数
let1:
    mov ah, 0               ; 存余数
    mov al, dl              ; al作为被除数，便于下面存储结果
    div bl                  ; 110,116; bl 写后读相关。余数放在 ah，商在 al
    push ax                 ; 余数进栈
    inc cx                  ; 余数个数加一
    cmp al, 0               ; 116,119; al 写后读相关。判断商是否为0
    jle let2                ; 小于 0 进入显示
    mov dl, al              ; 115,121；dl 读后写相关。否则，把商存入dl，待下次循环作为被除数
    jnz let1
; 显示数字函数 
let2:
    pop ax                  ; 出栈余数
    add ah, 30h             ; 变为ASCII
    mov dl, ah              ; 126,127; ah 写后读相关。显示余数
    mov ah, 2
    int 21h

    dec cx                  ; 显示一个余数后计数器减一
    cmp cx, 0               ; 131,132; cx 写后读相关。判断是否还有余数
    jnz let2                ; 有，就继续显示

    mov ah, 2               ; 没有，即输完一个数，显示一个空格
    mov dl, 20h            
    int 21h

    pop bx
    ret
output endp

code ends
    end start





