#These programs should produce errors

#p2b1
start
main
  print [ 1 ] .
stop

#p2b2
start
let x : 1
main {
  scanf  x  .
  printf [ 1 ] .
} stop

#p2b3
start
main {
  if [ 1 = 0 ] then
  {  printf [ 1 ] .
  }
} stop

#p2b4
start
main {
  if [ 1 => 0 ] then
    printf [ 1 ] .
} stop

#p2b5
start
let x : 1
let y : 2
main {
  let x : 3 .
  scanf [ x ] .
  printf [ 1 + 1 ] .
} stop