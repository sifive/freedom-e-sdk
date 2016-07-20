BEGIN {
	RS = ORS = "\r\n"
	addr = 0
	buf = ""
	limit = (WIDTH > 0 ? WIDTH / 4 : 16)
	print "@00000000"
}

# Portable strtonum() replacement
function atoi(str,	x, n, i, b, c) {
	if (str ~ /^0[0-7]*$/) {
		i = 2
		b = 8
	} else if (str ~ /^0[xX][[:xdigit:]]+$/) {
		i = 3
		b = 16
	} else {
		return str
	}

	x = 0
	n = length(str)
	for (; i <= n; i++) {
		c = tolower(substr(str, i , 1))
		c = index("123456789abcdef", c)
		x = (x * b) + c
	}
	return x
}

function out(x) {
	addr++
	buf = (REVERSE ? buf x : x buf)
	if (length(buf) >= limit) {
		print buf
		buf = ""
	}
}

function pad(n) {
	while (addr < n) {
		out("00")
	}
}

match($1, /^@[[:xdigit:]]+/) {
	pad(atoi("0x" substr($1, RSTART+1, RLENGTH-1)))
	next
}

{
	for (i = 1; i <= NF; i++) {
		out($i)
	}
}

END {
	align = limit / 2
	pad(int((addr + align - 1) / align) * align)
	if (length(buf) > 0) {
		print buf;
	}
}
