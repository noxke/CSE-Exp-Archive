; ModuleID = 'test'
source_filename = "test"

declare i32 @putchar(i32)

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 72, i32* %a, align 4
  %a1 = load i32, i32* %a, align 4
  %callputchar = call i32 @putchar(i32 %a1)
  %callputchar2 = call i32 @putchar(i32 85)
  %callputchar3 = call i32 @putchar(i32 83)
  %callputchar4 = call i32 @putchar(i32 84)
  %callputchar5 = call i32 @putchar(i32 83)
  %callputchar6 = call i32 @putchar(i32 69)
  %callputchar7 = call i32 @putchar(i32 67)
  ret i32 0
}
