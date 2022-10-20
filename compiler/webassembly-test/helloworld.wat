;; helloworld.wat

(module

  ;; Import our myprint function 
  (import "env" "jsprint" (func $jsprint (param i32)))
  (import "env" "newline" (func $newline))
  (import "env" "writeconsole" (func $writeconsole (param i32)))

  ;; Define a single page memory of 64KB.
  (memory $0 1)

  ;; Store the Hello World (null terminated) string at byte offset 0 
  ;; (data (i32.const 0) "Hello world\ntest\00")
  ;; (data (i32.const 32) "\ntestagain\00")
  ;; (data (i32.const 64) "2\00")
  ;; (data (i32.const 96) "3\00")


  ;; Export the memory so it can be access in the host environment.
  (export "pagememory" (memory $0))

  ;; Define a function to be called from our host
  (func $helloworld
    (local $x i32)(local $y i32)(local $z i32) 
    (local.set $x
      (i32.const 1)
    )
    (local.set $y
      (i32.const 2)
    )
    (local.set $z
      (i32.add 
        (local.get $x)
        (local.get $y)
      )
    )
    (call $writeconsole
      (local.get $z)
    )
    ;; (call $newline)
    ;; (call $jsprint (i32.const 32))
    ;; (call $jsprint (i32.const 64))
    ;; (call $jsprint (i32.add (i32.const 64) (i32.const 96)))
  )

  ;; Export the wasmprint function for the host to call.
  (export "helloworld" (func $helloworld))
)