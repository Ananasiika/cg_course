input_file = "output.obj"
output_file = "flamingo.obj"

with open(input_file, "r") as file:
    lines = file.readlines()

output_lines = []

for line in lines:
    if line.startswith("v"):
        values = line.split()[1:]
        modified_values = [str(float(values[0])), str(float(values[1]) + 40), str(float(values[2]))]
        modified_line = "v " + " ".join(modified_values) + "\n"
        output_lines.append(modified_line)
    else:
        output_lines.append(line)

with open(output_file, "w") as file:
    file.writelines(output_lines)
