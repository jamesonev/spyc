
func pow(x, n){
    if(n > 0){
        x * pow(x, n - 1)
    }
}
b = pow(2, 3)
