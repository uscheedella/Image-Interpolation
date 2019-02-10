single:
	gcc -o vector3d_single vectors.c -lm

divided:
	gcc -o vector3d_divided -I. vector3d.c vector_driver.c -lm

test:
	gcc -o vector3d_test -I. vector3d.c vector_test.c -lm

clean:
	rm -f vector3d_single
	rm -f vector3d_divided
	rm -f vector3d_test
