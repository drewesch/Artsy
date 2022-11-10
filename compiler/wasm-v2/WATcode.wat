(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	;; Artsy Program in WAT
	(global $aNumber i32)
	(global $array message size 50 i64)
	(global $justAverage f32)
	(export "float average" (func $float average)
	(func $float average
		(param $a f32)
		(param $b f32)
		(param $c f32)
		(local $avg f32)
	)
	(export "int displayMessage" (func $int displayMessage)
	(func $int displayMessage
		;; output message 
		(call $writeconsole
			(local.get $message)
		)
		;; Print New Line
		(call $newline)
		;; ---------
	)
	(export "float ambitiousFunction" (func $float ambitiousFunction)
	(func $float ambitiousFunction
		(param $a f32)
		(param $b f32)
		(param $c f32)
		(local $result f32)
	)
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
