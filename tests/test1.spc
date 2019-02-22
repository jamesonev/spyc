/*this is a sample function for my programming language spyc
working cases:
#1
8.952 + 32 * 2
2.1 + 1.952 + 4.2
2 + 1.952 + 0

a = 2
b = 2 + a

foo(1)

a = 4
while(a){
    a = 0
}

a = 2
b = 3
c = 4
x = a + b + c

struct foo{
    a = 2,
    b = 2
}
*/


a = 2
b = 3
c = 4
func foo(w, x, y, z ){
    x = 7 + w + y + z
}
a = foo(a, b, c, c)
