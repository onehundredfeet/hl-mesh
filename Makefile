genhl:
	haxe -cp generator  -lib hl-idl --macro "hmesh.Generator.generateCpp()"
	
genjs:
	haxe -cp generator -lib hl-idl --macro "hmesh.Generator.generateJs()"
