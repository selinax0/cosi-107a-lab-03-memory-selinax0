test: test-print-addresses test-print-low test-print-byte1 test-list-addresses \
	test-print-sizes

test-print-addresses: print-addresses
	./print-addresses 1524541 6134050524 4332846660 105553154375680 6134050512 \
	4332863488 4332863496 4332863492  4332863500 | diff - test-data/print-addresses-test.txt

test-print-low: print-low
	./print-low 10 255 8192 613439241 432 0xFF00 0x01FF01 | diff - test-data/print-low-test.txt

test-print-byte1: print-byte1
	./print-byte1 10 255 8192 613439241 432 0xFF00 0x01FF01 | diff - test-data/print-byte1-test.txt

test-list-addresses: list-addresses
	# For list-addresses: only test for simple output because results are not
	# predictable. Output should be submitted on Gradescope.
	./list-addresses | grep function

test-print-sizes: print-sizes
	./print-sizes | diff - test-data/print-sizes-test.txt

clean:
	rm -f print-addresses print-low print-byte1 list-addresses print-sizes

# Remove C source files that students are expected to create

distclean:
	rm -f print-addresses.c print-low.c print-byte1.c list-addresses.c \
		print-sizes.c
