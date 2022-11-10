(module
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	(func $main
		(local $aNumber i32)
		(local $ng array message size 50 i32)
		(local $t justAverage i32)
		;; output message 
		(call $writeconsole
			(local.get $message)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output justAverage 
		(call $writeconsole
			(local.get $justAverage)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output nextline 
		(call $writeconsole
			(local.get $nextline)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output nextline 
		(call $writeconsole
			(local.get $nextline)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output aNumber 
		(call $writeconsole
			(local.get $aNumber)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output nextline 
		(call $writeconsole
			(local.get $nextline)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output justAverage 
		(call $writeconsole
			(local.get $justAverage)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output nextline 
		(call $writeconsole
			(local.get $nextline)
		)
		;; Print New Line
		(call $newline)
		;; ---------
	)
	(export "main" (func $main))
)
