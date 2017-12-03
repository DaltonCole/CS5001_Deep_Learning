from sys import argv

"""
enum Direction {north=0, east=1, south=2, west=3};

enum Type {empty=0, tile=1, wall=2, donut=3};
"""

def color(t):
	if int(t) == 2:
		return "\\cellcolor{black}"
	elif int(t) == 0:
		return "\\cellcolor{green!25} "
	elif int(t) == 1:
		return "\\cellcolor{red!25} "
	elif int(t) == 3:
		return "\\cellcolor{blue!25} "

def direction_to_code(d, t):
	c = color(t)

	if int(t) == 2:
		return c + ""
	elif int(d) == 0:
		return c + "$\\bm{\\uparrow}$"
	elif int(d) == 1:
		return c + "$\\bm{\\rightarrow$}"
	elif int(d) == 2:
		return c + "$\\bm{\\downarrow}$"
	elif int(d) == 3:
		return c + "$\\bm{\\leftarrow}$"

	print("WHAAAATTTT???") 

if len(argv) != 2:
	print("Usage: Python3 table_generator <random_seed>")
	quit()

graph = ""

with open("../graph/" + str(argv[1]), 'r') as f:
	graph = f.readline()

graph = graph.split()

latex = "\\begin{table}\n\\centering\n\\caption{Resulting Grid}\n\\label{tab:grid}\n\\begin{tabular}{| "
for i in range(10):
	latex += "c |"
latex += "}\n\\hline\n"

d_v_t = []

for i in range(0, len(graph), 3):
	# Direction Value Type
	d_v_t.append([float(graph[i]), float(graph[i+1]), float(graph[i+2])])

for i in range(0, len(d_v_t), 10):
	for j in range(10):
		latex += direction_to_code(d_v_t[i+j][0], d_v_t[i+j][2])
		if j != 9:
			latex += " & "
	latex += "\\\\\n"
	for j in range(10):
		if direction_to_code(d_v_t[i+j][0], d_v_t[i+j][2]) != "":
			latex += color(d_v_t[i+j][2]) + str(d_v_t[i+j][1])
			if j != 9:
				latex += " & "
		else:
			latex += color(d_v_t[i+j][2])
			if j != 9:
				latex += " & "
	latex += "\\\\\n"
	latex += "\\hline\n"

latex += "\\end{tabular}\n\\end{table}\n"

with open("colored_table.tex", 'w') as f:
	f.write(latex)

print(latex)
