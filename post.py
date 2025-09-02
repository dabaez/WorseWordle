with open("output.txt") as f:
    lines = f.read().splitlines()


groups = []
for line in lines:
    if line.startswith("For answer: "):
        current_answer = line[len("For answer: ") :]
        groups.append([current_answer])
    elif line:
        groups[-1].append(line)

c = 0
for group in groups:
    if len(group) < 7:
        # print(f"Answer {group[0]} menos de 6 aburrido")
        pass
    elif len(group) == 7:
        c += 1
        print(f"Answer {group[0]} justo 6: {', '.join(group[1:])}")
    else:
        c += 1
        print(f"WTF imposibru {group[0]}: {', '.join(group[1:])}")

print(c)
