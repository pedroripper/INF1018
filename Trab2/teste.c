
int mult(int x) {
  return x * 2;
}

int main(){
	DescParam params[1];
  	func_ptr f_mult;
 	int i=3;

	params[0].tipo_val = INT_PAR;
 	params[0].orig_val = IND;
 	params[0].valor.v_ptr = &i;
	
	f_mult = (func_ptr) cria_func (mult, params, 1);

	printf("%d\n", f_mult());

printf("aaaaaaa\n");
	libera_func(f_mult);
	return 0;
}
