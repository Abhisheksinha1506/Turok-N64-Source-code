#!/usr/IRIXpro/bin/wishx -f
#
#  Create the callback.h, and actual callback functions
#
#  Rob Moore 2/17/95
#

#
#  list of prefixes.  Each of these has a corresponding
#  callback function.
#
set Prefixes { loadTex loadDetail loadTile loadBlock loadTlut \
		setTile setTileSize setConvert setTimg spTex setTother \
		ccKey ccPrim ccEnv ccCycle blFogColor blBlendColor blCycle \
		rspProj rspSciss rspCycleType rspGeom tileSync \
		loadSync rspPipe blBlendMask rspColorDither blPrim \
		blRgbDither blAlphaDither }

#
#  Remove redundant entries from a list
#
proc merge_list { unsort } {

  set mlist {}
  set sort [lsort $unsort]
  set tail [lindex $sort 0]
  lappend mlist $tail
  set v1 [lrange $sort 1 end]
  foreach f $v1 {
    if {$f != $tail } {
      lappend mlist $f
      set tail $f
    }
  }
  return $mlist
}

#
#  Main
#
source callDefs.h
source rspMain.tcl
source blMain.tcl
source ccMain.tcl
source texMain.tcl

#
#  Open files
#
set cc [open "callback.c" w]
set ch [open "callback.h" w]

#
#  Print comment
#
puts $ch "/*"
puts $ch " * callback.h - created by $argv0"
puts $ch " */"

#
#  Get lists of variables for each prefix
#
set varlist {}
foreach prefix $Prefixes {
  foreach var [merge_list [info vars $prefix*]] {
    lappend varlist $var
  }
}

#
#  Create UI structure
#
puts $ch "\n\ntypedef struct {"
foreach var [merge_list $varlist] {
    puts $ch "  int $var;"
}
puts $ch "} UIParams;"
puts $ch ""

#
#  Create Callback Functions
#
puts $cc "/*"
puts $cc " * callback.c - created by $argv0"
puts $cc " */"
puts $cc "#include <stdio.h>"
puts $cc "#include <string.h>"
puts $cc "#include <math.h>"
puts $cc "#include <tcl.h>"
puts $cc "#include \"callback.h\""
puts $cc ""
puts $cc "UIParams ui;"
puts $cc ""
puts $cc "extern void gen_fixedlength_dl\( UIParams \*ui \);"
puts $cc "extern void send_dl\( UIParams \*ui \);"

foreach prefix $Prefixes {
  puts $cc "extern void gen_dl_$prefix\( UIParams \*ui \);"
}
puts $cc "\n"

foreach prefix $Prefixes {
  puts $cc "int"
  puts $cc "  callback_$prefix\(ClientData data, Tcl_Interp \*interp, \
	int argc, char \*argv\[\]\)"
  puts $cc "\{"
  puts $cc "  char *value;"
  foreach var [merge_list [info vars $prefix*]] {
    puts $cc "  value = Tcl_GetVar\(interp, \"$var\", TCL_GLOBAL_ONLY | TCL_LEAVE_ERR_MSG\);"
    puts $cc "  if(value != NULL)"
    puts $cc "    Tcl_GetInt\(interp, value, &ui.$var\);"
    puts $cc "  else"
    puts $cc "    return TCL_ERROR;"
  }
  puts $cc "  gen_fixedlength_dl\(&ui\);"
  puts $cc "  gen_dl_$prefix\(&ui\);"
#  puts $cc "  send_dl\(&ui\);"
  puts $cc "  return TCL_OK;"
  puts $cc "\}\n\n"
}

#
#  Create Function to send display list
#
  puts $cc "int"
  puts $cc "  callback_send_dl\(ClientData data, Tcl_Interp \*interp, \
	int argc, char \*argv\[\]\)"
  puts $cc "\{"
  puts $cc "  send_dl\(&ui\);"
  puts $cc "  return TCL_OK;"
  puts $cc "\}\n\n"

#
#  Create Function to register callbacks
#
puts $cc ""
puts $cc "int"
puts $cc "  callback_init\(Tcl_Interp \*interp\)"
puts $cc "\{"
foreach prefix $Prefixes {
  puts $cc "  Tcl_CreateCommand\(interp, \"callback_$prefix\", callback_$prefix, NULL, NULL\);"
}
puts $cc "  Tcl_CreateCommand\(interp, \"callback_send_dl\", callback_send_dl, NULL, NULL\);"
puts $cc "  strcpy\(interp->result, \"callback_init passed\"\);"
puts $cc "  return TCL_OK;"
puts $cc "\}"

#
#  Done
#
close $ch
close $cc
exit
