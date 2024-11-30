; ModuleID = 'test'
source_filename = "test"

declare i32 @putchar(i32)

declare i32 @getchar()

define i32 @main() {
entry:
  %callgetchar = call i32 @getchar()
  %cond = icmp eq i32 %callgetchar, 97
  br i1 %cond, label %then, label %else

then:                                             ; preds = %entry
  %callputchar = call i32 @putchar(i32 89)
  br label %ifcont

else:                                             ; preds = %entry
  %callputchar1 = call i32 @putchar(i32 78)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret i32 0
}
