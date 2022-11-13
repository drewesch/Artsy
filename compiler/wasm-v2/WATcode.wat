(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	;; Artsy Program in WAT
	(global $aNumber i32)
	(global $justAverage f32)
	(export "average" (func $average))
	(func $average (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $avg f32)
		;; return avg
		(local.get $avg)
	)
	(export "displayMessage" (func $displayMessage))
	(func $displayMessage (result i32)
		;; output message 
		(call $writeconsole
			(local.get $message)
		)
		;; return 0
		(local.get $0)
	)
	(export "ambitiousFunction" (func $ambitiousFunction))
	(func $ambitiousFunction (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $result f32)
		;; return result
		(local.get $result)
	)
		;; output justAverage 
		(call $writeconsole
			(local.get $justAverage)
		)
		;; Print New Line
		(call $newline)
		;; Print New Line
		(call $newline)
		;; output aNumber 
		(call $writeconsole
			(local.get $aNumber)
		)
		;; Print New Line
		(call $newline)
		;; output justAverage 
		(call $writeconsole
			(local.get $justAverage)
		)
		;; Print New Line
		(call $newline)
)
